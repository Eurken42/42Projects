use ncurses::*;
use colored::Colorize;
use tungstenite::Message;
use tungstenite::Connector::NativeTls;
use std::io::Write;
use crate::user::User;

struct Console {
	width: f64,
	height: f64
}

const PADDLE_HEIGHT: f64 = 3.1;
struct Paddle {
	x: f64,
	y: f64,
	old_y: f64
}

struct Ball {
	x: f64,
	y: f64,
	old_x: f64,
	old_y: f64
}

struct Score {
	score1: i32,
	score2: i32,
}

struct Player {
	p1id: i32,
	p1_username: String,

	p2id: i32,
	p2_username: String,
}
/**
 * Add the user to the matchmaking queue by searching a game
 * Will automatically connect to the game when it starts
 * 
 * Args:
 * 		user: User - The user
 * 
 * Returns:
 * 		Option<bool> - The result of the game (true if the user won, false otherwise)
 * 		None - If an error occured
 */
pub fn matchmaking(user: User) -> Option<bool> {
	
	// Ask the server for the waiting room
	let req = user.get_client().get("https://{server}/api/game/search/".replace("{server}", user.get_server().as_str()));
	let req = req.build();
	let res = user.get_client().execute(req.expect("ERROR WHILE EXECUTING THE REQUEST"));
	let room_id = match res {
		Ok(res) => {
			if res.status().is_success() {
				let body = res.text().expect("ERROR WHILE READING THE BODY");
				let json = json::parse(body.as_str()).unwrap();
				let room_id = &json["id"];
				room_id.to_string()
			} else {
				eprintln!("{}", format!("Error while searching for a game").red().bold());
				return None;
			}
		},
		Err(err) => {
			eprintln!("{}", format!("{}", err).red().bold());
			return None;
		}
	};

	return connect_game(user.clone(), room_id, false);
}

/**
 * Create a game by creating a room and waiting for a player to join
 * 
 * Args:
 * 		user: User - The user
 * 
 * Returns:
 * 		Option<bool> - The result of the game (true if the user won, false otherwise)
 * 		None - If an error occured
 */
pub fn create_game(user: User) -> Option<bool> {

	// Ask the server for a room
	let req = user.get_client().get("https://{server}/api/game/create/".replace("{server}", user.get_server().as_str()));
	let req = req.build();
	let res = user.get_client().execute(req.expect("ERROR WHILE EXECUTING THE REQUEST"));
	let room_id = match res {
		Ok(res) => {
			if res.status().is_success() {
				let body = res.text().expect("ERROR WHILE READING THE BODY");
				let json = json::parse(body.as_str()).unwrap();
				let room_id = &json["id"];
				room_id.to_string()
			} else {
				eprintln!("{}", format!("Error while creating a game").red().bold());
				return None;
			}
		},
		Err(err) => {
			eprintln!("{}", format!("{}", err).red());
			return None;
		}
	};
	println!("Your room ID is: {}", room_id);

	return connect_game(user.clone(), room_id, true);
}

/**
 * Join a game by entering the room ID
 * 
 * Args:
 * 		user: User - The user
 * 
 * Returns:
 * 		Option<bool> - The result of the game (true if the user won, false otherwise)
 * 		None - If an error occured
 */
pub fn join_game(user: User) -> Option<bool> {
	
	// Ask for the room ID
	let mut room: String = String::new();
	loop {
		room.clear();
		print!("Room ID (q to quit): ");
		let _ = std::io::stdout().flush();
	
		std::io::stdin()
			.read_line(&mut room)
			.expect(&format!("Erreur lors de la lecture de l'utilisateur").red());
		room = (*room.trim()).to_string();
	
		if room.len() <= 0 {
			eprintln!("{}", format!("Room ID is empty, please try again").red());
			continue;
		}

		room = match room.as_str() {
			"q" => {
				return None;
			},
			id => id.to_string()
		};

		// Check if the room exists
		let req = user.get_client().get("https://{server}/api/game/{room_id}".replace("{server}", user.get_server().as_str()).replace("{room_id}", room.as_str()));
		let res = req.build();
		let res = user.get_client().execute(res.expect("ERROR WHILE BUILDING THE REQUEST"));
		match res {
			Ok(res) => {
				if res.status().is_success() {
					break;
				} else if res.status().is_client_error() {
					eprintln!("{}", format!("Room not found or ID invalid").red().bold());
					continue;
				}
			},
			Err(err) => {
				eprintln!("{}", format!("{}", err).red());
				return None;
			}
		}
		break;
	}

	return connect_game(user.clone(), room, true);
}

/**
 * Connect to the websocket, wait the other player et then start the game
 * 
 * Args:
 * 		user: User - The user
 * 		room: String - The room ID
 * 		private: bool - If the game is private or not
 * 
 * Returns:
 * 		Option<bool> - The result of the game (true if the user won, false otherwise)
 * 		None - If an error occured
 */
pub fn connect_game(user: User, room: String, private: bool) -> Option<bool> {
	let mut socket = match connect_ws(user.clone(), room) {
		Ok(socket) => socket,
		Err(err) => {
			eprintln!("{}", format!("{:#?}", err).red());
			return None;
		}
	};

	if private {
		_ = socket.send(Message::Text(r#"{"message":"private"}"#.to_string()));
	} else {
		_ = socket.send(Message::Text(r#"{"message":"public"}"#.to_string()));
	}
	println!("Waiting for the game to start...");
	return game(socket, user.clone());
}

/**
 * Connect to the websocket server
 * 
 * Args:
 * 		user: User - The user
 * 		room: String - The room id
 * 
 * Returns:
 * 		Ok(tungstenite::WebSocket<tungstenite::stream::MaybeTlsStream<std::net::TcpStream>>) - The websocket connected to the game
 * 		Err(Box<dyn std::error::Error>) - If an error occured
 */
fn connect_ws(user: User, room: String) -> Result<tungstenite::WebSocket<tungstenite::stream::MaybeTlsStream<std::net::TcpStream>>, Box<dyn std::error::Error>> {
	
	// Create a TLS connector (and a TCP stream) to dodge the self-signed certificate
	let mut connector = native_tls::TlsConnector::builder();
	let connector = connector.danger_accept_invalid_certs(true);
	let connector = match connector.build() {
		Ok(connector) => connector,
		Err(err) => {
			eprintln!("{}", format!("{}", err).red().bold());
			return Err(Box::new(err));
		}
	};
	let stream = match std::net::TcpStream::connect(format!("{server}:443", server = user.get_server())) {
		Ok(stream) => stream,
		Err(err) => {
			eprintln!("{}", format!("{}", err).red().bold());
			return Err(Box::new(err));
		}
	};
	
	// Open the websocket
	match tungstenite::client_tls_with_config(("wss://{server}/ws/game/{room_id}/").replace("{server}", user.get_server().as_str()).replace("{room_id}", room.as_str()), stream, None, Some(NativeTls(connector))) {
		Ok((socket, _res)) => {
			return Ok(socket);
		},
		Err(err) => {
			eprintln!("{}", format!("{}", err).red().bold());
			return Err(Box::new(err));
		}
	};
}

fn	get_username_by_id(user: User, id: i32) -> Option<String> {
	let req = user.get_client().get("https://{server}/api/user/{id}".replace("{server}", user.get_server().as_str()).replace("{id}", id.to_string().as_str()));
	let req = req.build();
	let res = user.get_client().execute(req.expect("ERROR WHILE EXECUTING THE REQUEST"));
	match res {
		Ok(res) => {
			if res.status().is_success() {
				let body = res.text().expect("ERROR WHILE READING THE BODY");
				let json = json::parse(body.as_str()).unwrap();
				let username = &json["username"];
				return Some(username.to_string());
			} else {
				eprintln!("{}", format!("Error while getting the username").red().bold());
				return None;
			}
		},
		Err(err) => {
			eprintln!("{}", format!("{}", err).red());
			return None;
		}
	};
}
/**
 * Wait for the game to start, print the countdown and then called the game function
 * 
 * Args:
 * 		socket: tungstenite::WebSocket<tungstenite::stream::MaybeTlsStream<std::net::TcpStream>> - The websocket connected to the game
 * 		term: &Console - The console struct
 * 		paddle_l: &Paddle - The left paddle
 * 		paddle_r: &Paddle - The right paddle
 * 		score: &Score - The score
 * 
 * Returns:
 * 		Option<String> - The player number (p1 or p2)
 * 		None - If an error occured
 */
fn waiting_game(socket: &mut tungstenite::WebSocket<tungstenite::stream::MaybeTlsStream<std::net::TcpStream>>, user: User, term: &Console, paddle_l: &Paddle, paddle_r: &Paddle, score: &Score) -> Option<(String, Player, bool)> {
	_ = socket.send(Message::Text(r#"{"message":"load"}"#.to_string()));
	let mut player: String = "default".to_string();
	let mut data_player: Player = Player {
		p1id: -1,
		p1_username: "".to_string(),
		p2id: -1,
		p2_username: "".to_string()
	};

	loop {
		match socket.read() {
			Ok(msg) => {
				match msg {
					Message::Text(msg) => {
						let msg = msg.as_str();
						let json = json::parse(msg).unwrap();
						match json["action"].as_str().unwrap() {
							"counter" => {
								match json["num"].as_i32() {
									Some(num) => print_counter(term, num, paddle_l, paddle_r, score, &data_player),
									None => {
										eprintln!("{:#?}", json);
									}
								}
							},
							"start" => {
								if player == "default" || data_player.p1id == -1 || data_player.p2id == -1 {
									_ = endwin();
									eprintln!("{}", format!("Error while getting the player number").red());
									return None;
								} else {
									return Some((player, data_player, false));
								}
							},
							"playernumber" => {
								player = match json["playernumber"].as_i32() {
									Some(num) => match num {
										1 => "p1".to_string(),
										2 => "p2".to_string(),
										_ => "default".to_string()
									},
									None => {
										_ = endwin();
										eprintln!("{}", format!("Error while getting the player number").red());
										return None;
									}
								};
							},
							"playerid" => {
								data_player = Player {
									p1id: json["p1"].as_i32().unwrap(),
									p1_username: "".to_string(),
									p2id: json["p2"].as_i32().unwrap(),
									p2_username: "".to_string()
								};
								data_player.p1_username = match get_username_by_id(user.clone(), data_player.p1id) {
									Some(username) => username,
									None => {
										_ = endwin();
										eprintln!("{}", format!("Error while getting the username").red());
										return None;
									}
								};
								data_player.p2_username = match get_username_by_id(user.clone(), data_player.p2id) {
									Some(username) => username,
									None => {
										_ = endwin();
										eprintln!("{}", format!("Error while getting the username").red());
										return None;
									}
								};
							},
							"private" | "public" => {},
							"userid" => _ = socket.send(Message::Text(r#"{"message":"userid", "userid": {id}}"#.replace("{id}", &user.get_id()).to_string())),
							"allin" => {
								_ = clear();

								// Init ncurses to get the user's input
								initscr();
								keypad(stdscr(), true);
								cbreak();
								noecho();
								nodelay(stdscr(), true);
								curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);

								mvprintw(0, 0, "Waiting for the game to start...");
								refresh();
							},
							"Stop" => {
								_ = endwin();
								println!("{}", format!("The other player left the game !").red());
								return Some((player, data_player, true));
							},
							"paddle2" => {},
							"paddle1" => {},
							_ => {
								_ = endwin();
								eprintln!("Unknown action: {}", json["action"]);
								return None;
							}
						}
					},
					_ => {}
				}
			},
			Err(err) => {
				_ = endwin();
				eprintln!("ERROR\n{}", format!("{}", err).red());
				return None;
			}
		}
	}
}

fn print_counter(term: &Console, i: i32, paddle_l: &Paddle, paddle_r: &Paddle, score: &Score, data_player: &Player)
{
	print_paddle(paddle_l, &term);
	print_paddle(paddle_r, &term);
	mvaddstr(0, 0, &" ".repeat(term.width as usize));
	print_score(term, score, &data_player);
	mvaddstr((term.height / 2.0) as i32 + 1, (term.width / 2.0) as i32, &format!("{}", i));
	refresh();
}

/**
 * Handle the game loop (The game must be started)
 * Exiting when the game is over
 * 
 * Args:
 * 		socket: tungstenite::WebSocket<tungstenite::stream::MaybeTlsStream<std::net::TcpStream>> - The websocket connected to the game
 * 
 * Returns:
 * 		Option<bool> - The result of the game (true if the user won, false otherwise)
 * 		None - If an error occured
 */
fn game(mut socket: tungstenite::WebSocket<tungstenite::stream::MaybeTlsStream<std::net::TcpStream>>, user: User) -> Option<bool> {
	let mut term: Console;

	if let Some((w, h)) = term_size::dimensions() {
		term = Console {
			width: w as f64,
			height: h as f64
		};
	} else {
		println!("Error\n");
		return None;
	}

	let paddle_offset: f64 = term.width / 12.0;
 
	let mut paddle_l = Paddle { x: paddle_offset, y: (term.height / 2.0 - 1.0), old_y: 0.0 };
	let mut paddle_r = Paddle { x: (term.width - paddle_offset), y: (term.height / 2.0 - 1.0), old_y: 0.0 };
	let mut ball = Ball { x: 0.0, y: 0.0, old_x: 0.0, old_y: 0.0 };
	let mut score = Score { score1: 0, score2: 0 };

	let player = waiting_game(&mut socket, user.clone(), &term, &paddle_l, &paddle_r, &score);
	let (player, data_player, flag) = match player {
		Some((player, data_player, flag)) => (player, data_player, flag),
		None => {
			return None;
		}
	};

	if flag == true
	{
		return Some(true);
	}
	// game loop
	loop {
		// Handle the server's messages
		match socket.read() {
			Ok(msg) => match msg {
				Message::Text(msg) => {
					let msg = msg.as_str();
					let json = json::parse(msg).unwrap();
					match json["action"].as_str().unwrap() {
						"game" => {
							ball.old_x = ball.x;
							ball.old_y = ball.y;
							ball.x = (json["bx"].as_f64().unwrap() + 18.0) / 36.0 * term.width;
							ball.y = (json["bz"].as_f64().unwrap() + 9.5) / 19.0 * (term.height - (1 as f64));
							paddle_l.old_y = paddle_l.y;
							paddle_r.old_y = paddle_r.y;
							paddle_l.y = (json["plz"].as_f64().unwrap() + 9.5) / 19.0 * term.height;
							paddle_r.y = (json["prz"].as_f64().unwrap() + 9.5) / 19.0 * (term.height - (1 as f64));
						},
						"ball" => {
							ball.old_x = ball.x;
							ball.old_y = ball.y;
							ball.x = (json["bx"].as_f64().unwrap() + 18.0) / 36.0 * term.width;
							ball.y = (json["bz"].as_f64().unwrap() + 9.5) / 19.0 * (term.height - (1 as f64));
						},
						"paddle1" => { // RIGHT ONE
							paddle_r.old_y = paddle_r.y;
							paddle_r.y = (json["prz"].as_f64().unwrap() + 9.5) / 19.0 * (term.height - (1 as f64));
						},
						"paddle2" => { // LEFT ONE
							paddle_l.old_y = paddle_l.y;
							paddle_l.y = (json["plz"].as_f64().unwrap() + 9.5) / 19.0 * (term.height - (1 as f64));
						},
						"score" => {
							score.score1 = json["scorep1"].as_i32().unwrap();
							score.score2 = json["scorep2"].as_i32().unwrap();
						},
						// "private" => continue,
						"Stop" => {
							_ = endwin();
							_ = clearscreen::clear();
							_ = socket.send(Message::Text(r#"{"message":"mdr"}"#.to_string()));
							if score.score1 > score.score2 {
								if player == "p1" {
									return Some(true);
								} else {
									return Some(false);
								}
							} else {
								if player == "p2" {
									return Some(true);
								} else {
									return Some(false);
								}
							}
						},
						"start" => continue,
						"userleave" => {
							_ = endwin();
							_ = clearscreen::clear();
							println!("{}", format!("The other player left the game").red().bold());
							return Some(true);
						},
						"paddle1" => {},
						"paddle2" => {},
						_ => {
							_ = endwin();
							_ = clearscreen::clear();
							println!("Unknown action: {}", json["action"]);
							return None;
						}
					}
					render(&term, &paddle_l, &paddle_r, &ball, &score, &data_player);
				},
				_ => {
					// println!("Unknown message");
				}
			},
			Err(err) => match err {
				tungstenite::error::Error::Io(err) if err.kind() == std::io::ErrorKind::Interrupted => {
					if let Some((w, h)) = term_size::dimensions() {
						term = Console {
							width: w as f64,
							height: h as f64
						};
						let paddle_offset: f64 = term.width / 12.0;
						paddle_l.x = paddle_offset;
						paddle_r.x = term.width - paddle_offset;
					}
					continue
				}
				_ => {
					endwin();
					eprintln!("{}", format!("{}", err).red().bold());
					return None;
				}
			}
		}
		// Send the user's input to the server
		match getch() {
			27 => {
				endwin();
				let _ = clearscreen::clear();
				println!("{}", format!("You just left the game !").red());
				break;
			},
			ch => {
				let ch = match char::from_u32(ch as u32) {
					Some(ch) => {
						ch
					},
					None => ' '
				};
				if ch != ' ' {
					_ = socket.send(Message::Text(r#"{"message":"{ch}"}"#.to_string().replace("{ch}", &ch.to_string())));
				}
			}
		}
	}
	None
}

/**
 * Render the entire game (score, paddles and ball)
 * 
 * Take refs to every argument
 * 
 * Args:
 * 		term: &Console - The console struct
 * 		paddle_l: &Paddle - The left paddle
 * 		paddle_r: &Paddle - The right paddle
 * 		ball: &Ball - The ball
 * 		score: &Score - The score
 */
fn render(term: &Console, paddle_l: &Paddle, paddle_r: &Paddle, ball: &Ball, score: &Score, data_player: &Player) {
	print_score(&term, &score, &data_player);
 	print_paddle(&paddle_l, &term);
	print_paddle(&paddle_r, &term);
	print_ball(&ball);
	refresh();
}

/**
 * Print the score
 * 
 * Args:
 *		term: &Console - The console struct
 *		score: &Score - The score
 */
fn print_score(term: &Console, score: &Score, data_player: &Player) {
	mvaddstr(0, 1, data_player.p2_username.as_str());
	mvaddstr(0, ((term.width / 2.0 - 3.0) as i32).try_into().unwrap(), &format!("{} - {}", score.score2, score.score1));
	mvaddstr(0, (term.width - (data_player.p1_username.chars().count() as f64)) as i32 - 1, data_player.p1_username.as_str());
	mvaddstr(1, 0, &"-".repeat(term.width as usize));
}

/**
 * Print the paddle
 * 
 * Args:
 * 		paddle: &Paddle - Ref to paddle struct to print
 */
fn print_paddle(paddle: &Paddle, term: &Console) {
	let paddle_height = PADDLE_HEIGHT / 19.0 * (term.height);
	for i in 0..paddle_height as i32 {
		mvaddch((paddle.old_y + i as f64 - (PADDLE_HEIGHT / 2.0)) as i32, paddle.x as i32, ' ' as u32);
	}
	for i in 0..paddle_height as i32 {
		mvaddch((paddle.y + i as f64 - (PADDLE_HEIGHT / 2.0)) as i32, paddle.x as i32, '|' as u32);
	}
}

/**
 * Print the ball
 * 
 * Args:
 * 		ball: &Ball - Ref to ball struct to print
 */
fn print_ball(ball: &Ball) {
	mvaddch(ball.old_y as i32 + 1, ball.old_x as i32, ' ' as u32);
	mvaddch(ball.y as i32 + 1, ball.x as i32, 'o' as u32);
}
