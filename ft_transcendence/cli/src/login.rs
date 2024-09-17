use std::io::Write;
use std::time::Duration;
use std::sync::Arc;
use reqwest::cookie::Jar;
use colored::Colorize;

use crate::user::User;

// Ask the user for login and password, and then return the connection status
pub fn login(srv: String) -> Option<User> {
	print!("Login: ");
	let _ = std::io::stdout().flush();

	let mut login: String = String::new();
	std::io::stdin()
		.read_line(&mut login)
		.expect("Erreur lors de la lecture de l'utilisateur");
	login = (*login.trim()).to_string();
	
	println!("Password: ");

	let password = match rpassword::read_password() {
		Ok(str) => str,
		Err(_) => {
			eprintln!("{}", format!("ERREUR LORS DE LA LECTURE DU MOT DE PASSE").red());
			return None;
		}
	
	};
	return connection(srv, login, password);
}

// Use the provide login and password to connect to the server
fn connection(srv: String, login: String, password: String) -> Option<User> {
	let jar = Arc::new(Jar::default());
	
	let client = reqwest::blocking::Client::builder()
		.danger_accept_invalid_certs(true)
		.cookie_provider(Arc::clone(&jar))
		.build();
	let client = match client {
		Ok(client) => client,
		Err(err) => {
			eprintln!("{}", err);
			return None;
		}
	};
	
	let mut user = User::new();
	user.fill(String::from(""), String::from(""), client, srv);

	let csrf_token = match user.get_csrf() {
		Some(csrf) => csrf,
		None => {
			eprintln!("{}", format!("Error while getting the CSRF token").red());
			return None;
		}
	};
	let req = user.get_client()
		.post(("https://{server}/auth/login/").replace("{server}", &user.get_server()))
		.header("User-Agent", "cli_rust")
		.header("Accept", "application/json")
		.header("X-CSRFToken", csrf_token)
		.header("Referer", "https://{server}/".replace("{server}", &user.get_server()))
		.body((r#"{"username":"{email}","password":"{password}"}"#).replace("{email}", &login).replace("{password}", &password))
		.timeout(Duration::from_secs(3));

	let req = req.build().expect("ERROR WHILE BUILDING THE REQUEST");
	let res = user.get_client().execute(req);

	match res {
		Ok(res) => {
			if !res.status().is_success() {
				// eprintln!("{:#?}", res);
				return None;
			}
			let res = res.text().ok();
			let res = match res {
				Some(res) => res,
				None => {
					eprintln!("{}", format!("Error in respond: {:#?}", res).red());
					return None;
				}
			};
			match json::parse(&res) {
				Ok(res) => {
					if res["message"] == -1 {
						return None;
					}
					user.set_id(res["id"].to_string());
					user.set_username(login);
				},
				Err(err) => {
					eprintln!("Error in respond: {:#?}", err);
					return None;
				}
			}
		},
		Err(err) => {
			eprintln!("Error in respond: {:#?}", err);
			return None;
		}
	}
	return Some(user);
}

pub fn logout(user: User) {
	let req = user.get_client().get("https://{server}/auth/logout/{id}".replace("{server}", user.get_server().as_str()).replace("{id}", user.get_id().as_str()));
	let req = req.build().expect("ERROR WHILE BUILDING THE REQUEST");
	let res = user.get_client().execute(req);
	match res {
		Ok(_) => {},
		Err(err) => {
			eprintln!("{}", format!("{}", err).red());
		}
	}
}