use colored::Colorize;
use json;
use std::io::Write;
use tungstenite::Connector::NativeTls;
use tungstenite::Message;
use std::time::Duration;

use crate::pong;
use crate::user::User;

pub fn create_tournament(user: User) {
	let req = user.get_client().get("https://{server}/api/tournament/create/{user_id}".replace("{user_id}", &user.get_id().as_str())
		.replace("{server}", user.get_server().as_str()));
	let req = req.build();
	let res = user.get_client().execute(req.expect("ERROR WHILE BUILDING THE REQUEST"));
	let tournament_id = match res {
		Ok(res) => {
			if res.status().is_success() {
				let body = res.text().expect("ERROR WHILE READING THE RESPONSE");
				let json = json::parse(body.as_str()).unwrap();
				let tournament_id = json["tournamentid"].as_i32().unwrap();

				tournament_id.to_string()
			} else {
				eprintln!("{}", format!("Error while creating the tournament").red());
				return;
			}
		},
		Err(err) => {
			eprintln!("{}", format!("{:#?}", err).red());
			return;
		}
	};

	println!("{}", format!("Tournament created with ID: {}", format!("{}", tournament_id).bold()).green());

	let mut socket = match connect_ws_tournament(user.clone(), tournament_id) {
		Ok(socket) => socket,
		Err(err) => {
			eprintln!("{}", format!("{:#?}", err).red());
			return;
		}
	};

	println!("{}", format!("Waiting for players to join the tournament"));

	handle_tournament(user.clone(), &mut socket, String::from("1"));
}

/**
 * Join a tournament.
 * Will ask the user for the tournament ID and then join the tournament.
 * 
 * Args:
 * 		user: User - The user object
 */
pub fn join_tournament(user: User) {

	// Get the tournament ID
	let mut tournament_id = String::new();
	let mut player_nb = String::from("default");

	loop {
		tournament_id.clear();
		print!("Enter the tournament ID (q to quit): ");
		_ = std::io::stdout().flush();

		std::io::stdin()
			.read_line(&mut tournament_id)
			.expect(&format!("Erreur lors de la lecture de l'entrée").red());
		tournament_id = (*tournament_id.trim()).to_string();

		if tournament_id.len() <= 0 {
			eprintln!("{}", format!("Tournament ID can't be empty").red());
			continue;
		} else if tournament_id.as_str() == "q" {
			return;
		}

		let csrf_token = match user.get_csrf() {
			Some(csrf) => csrf,
			None => {
				eprintln!("{}", format!("Error while getting the CSRF token").red());
				continue;
			}
		};
		let req = user.get_client()
			.post("https://{server}/api/tournament/join/{tournament_id}/{user_id}".replace("{server}", user.get_server().as_str()).replace("{tournament_id}", &tournament_id).replace("{user_id}", user.get_id().as_str()))
			.header("User-Agent", "cli_rust")
			.header("Accept", "application/json")
			.header("X-CSRFToken", csrf_token)
			.header("Referer", "https://{server}/".replace("{server}", &user.get_server()))
			.timeout(Duration::from_secs(3));

		let res = req.build();
		let res = user.get_client().execute(res.expect("ERROR WHILE BUILDING THE REQUEST"));
		match res {
			Ok(res) => {
				if res.status().is_success() {
					// Retrieve the player nb
					let body = res.text().expect("ERROR WHILE READING THE RESPONSE");
					let json = json::parse(body.as_str()).unwrap();
					match &json["playernb"] {
						json::JsonValue::Number(playernb) => {
							player_nb = playernb.to_string();
						},
						_ => {
							eprintln!("{}", format!("Error while joining the tournament").red());
							continue;
						}
					}
					break;
				} else if res.status().is_client_error(){
					eprintln!("{}", format!("Tournament not found or ID invalid").red().bold());
					continue;
				}
			},
			Err(_) => {
				eprint!("{}", format!("Tournament not found or ID invalid").red().bold());
				continue;
			}
		}
		break;
	}

	// Join the tournament
	let mut socket = match connect_ws_tournament(user.clone(), tournament_id) {
		Ok(socket) => socket,
		Err(err) => {
			eprintln!("{}", format!("{:#?}", err).yellow());
			return;
		}
	};
	println!("{}", format!("Connected to the tournament, waiting for more player...").green());
	handle_tournament(user.clone(), &mut socket, player_nb);
}

/**
 * Connect to the tournament websocket
 
 *	Args:
 *		user: User - The user object
 *		tournament_id: String - The tournament ID
 */
fn connect_ws_tournament(user: User, tournament_id: String) -> Result<tungstenite::WebSocket<tungstenite::stream::MaybeTlsStream<std::net::TcpStream>>, Box<dyn std::error::Error>> {

	// Create a TLS connector (and TCP stream) to dodge the self-signed certificate
	let mut connector = native_tls::TlsConnector::builder();
	let connector = connector.danger_accept_invalid_certs(true);
	let connector = match connector.build() {
		Ok(connector) => connector,
		Err(err) => {
			eprintln!("{}", format!("{}", err).red().bold());
			return Err(Box::new(err));
		}
	};
	let stream = match std::net::TcpStream::connect(format!("{server}:443", server=user.get_server())) {
		Ok(stream) => stream,
		Err(err) => {
			eprintln!("{}", format!("{}", err).red().bold());
			return Err(Box::new(err));
		}
	};

	// Open the websocket connection
	match tungstenite::client_tls_with_config("wss://{server}/ws/tournament/{id}/"
		.replace("{server}", &user.get_server()).replace("{id}", tournament_id.as_str()),
		stream,
		None,
		Some(NativeTls(connector))) {
			Ok((ws, _)) => return Ok(ws),
			Err(err) => {
				eprintln!("{}", format!("{}", err).red().bold());
				return Err(Box::new(err));
			}
	};
}

/**
 * Handle tournament (connect to the game, tell to the server the result, etc...)
 * 
 * Args:
 * 		user: User - The user object
 * 		socket: &mut tungstenite::WebSocket<tungstenite::stream::MaybeTlsStream<std::net::TcpStream>> - The websocket connection to the server
 */
fn handle_tournament(user: User, socket: &mut tungstenite::WebSocket<tungstenite::stream::MaybeTlsStream<std::net::TcpStream>>, player_nb: String) {
	let mut _game_id = -1;

	'selection: loop {
		match socket.read() {
			Ok(msg) => {
				match msg {
					Message::Text(msg) => {
						let msg = msg.as_str();
						let json = json::parse(msg).unwrap();

						match json["action"].as_str() {
							Some(action) => match action {
								"startTournament" => {
									// Ask for the gameId
									if player_nb == "default" {
										eprintln!("{}", format!("Error: player_nb not set").red());
										return;
									}
									_ = socket.send(Message::Text(r#"{"message":"getGameId", "playernb":"{pid}"}"#.to_string()
										.replace("{pid}", player_nb.as_str())));

									// Get the gameId and start the game
									loop {
										match socket.read() {
											Ok(msg) => {
												match msg {
													Message::Text(msg) => {
														let msg = msg.as_str();
														let json = json::parse(msg).unwrap();
														match json["action"].as_str().unwrap() {
															"gameid" => {
																_game_id = json["gameid"].as_i32().unwrap();
																break 'selection;
															},
															_ => {}
														}
													},
													_ => {}
												}
											},
											Err(err) => {
												eprintln!("{}", format!("{:#?}", err).red());
												return;
											}
										}
									}
								},
								"gameid" => {
									_game_id = json["gameid"].as_i32().unwrap();
									continue;
								},
								"connect" => {
									print!("\rThere are actually {} player(s) in the tournament", json["connected"]);
									_ = std::io::stdout().flush();
								},
								_ => {}
							},
							None => {}
						}
					},
					_ => {}
				}
			},
			Err(err) => {
				eprintln!("{}", format!("{:#?}", err).red().bold().italic());
				eprintln!("gameid: {}\tpid: {}", _game_id, player_nb);
				return;
			}
		};
	}
	println!("");


	match pong::connect_game(user.clone(), _game_id.to_string(), true) {
		Some(res) => {
			if res {
				println!("{}", format!("You won the game").green().bold());
				_ = socket.send(Message::Text(r#"{"message":"winner", "finalid":-1}"#.to_string()));
			} else {
				println!("{}", format!("You lost the game").red().bold());
				_ = socket.send(Message::Text(r#"{"message":"looser"}"#.to_string()));
				return;
			}
		},
		None => {
			eprintln!("{}", format!("Error while connecting to the game").red());
			return;
		}
	};
	loop {
		match socket.read() {
			Ok(msg) => {
				match msg {
					Message::Text(msg) => {
						let msg = msg.as_str();
						let json = json::parse(msg).unwrap();
						match json["action"].as_str().unwrap() {
							"finalid" => {
								_game_id = json["finalid"].as_i32().unwrap();
								match pong::connect_game(user.clone(), _game_id.to_string(), false) {
									Some(res) => {
										if res {
											println!("{}", format!("You won the tournament").green().bold());
										} else {
											println!("{}", format!("You lost the tournament").red().bold());
										}
										return;
									},
									None => {
										println!("{}", format!("Error during the game").red());
										return;
									}
								}
							},
							_ => {}
						};
					},
					_ => {}
				}
			},
			Err(err) => {
				eprintln!("{}", format!("{:#?}", err).yellow().bold());
				return;
			}
		}
	}
}
