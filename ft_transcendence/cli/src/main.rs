mod login;
mod menu;
mod user;
mod pong;
mod tournament;

use std::io::Write;
use std::error::Error;
use colored::*;
use signal_hook::{consts::{SIGHUP, SIGINT, SIGQUIT, SIGTERM}, iterator::Signals};


/**
 * Ask for the server, ping it to ensure it's up, then login the user and display the menu
 * 
 */
fn main() {
	title();
	
	// Ask for the server and try to ping it
	let srv = loop {
		let mut srv: String = String::new();
		print!("Server: ");
		let _ = std::io::stdout().flush();

		std::io::stdin()
			.read_line(&mut srv)
			.expect(&format!("Erreur lors de la lecture de l'utilisateur").red());
		srv = (*srv.trim()).to_string();

		if srv.len() <= 0 {
			eprintln!("{}", format!("Server name is empty, please try again").red());
			continue;
		}
			
		let client = reqwest::blocking::Client::builder()
			.danger_accept_invalid_certs(true)
			.build();

		let client = match client {
			Ok(client) => client,
			Err(err) => {
				eprintln!("{}", format!("{}", err).red());
				continue;
			}
		};

		let ping_req = client
			.get(("https://{server}/").replace("{server}", &srv))
			.header("User-Agent", "cli_rust")
			.header("Accept", "application/json")
			.timeout(std::time::Duration::from_secs(1));
		let ping_req = match ping_req.build() {
			Ok(ping_req) => ping_req,
			Err(err) => {
				eprintln!("{}", format!("{}", err).red());
				continue;
			}
		};
		
		let res = client.execute(ping_req);
		match res {
			Ok(res) => {
				if res.status().is_success() {
					println!("{}", format!("Server is up !").green());
					break srv;
				} else {
					eprintln!("{}", format!("Server is down, please try again").red());
					continue;
				}
			},
			Err(err) => {
				let err = err.source().unwrap().source().unwrap();
				let err = err.to_string();
				eprintln!("{}", format!("{}", err).red());
			}
		}
	};

	// Login
	let user: user::User;
	let mut max_try = 3;
	loop {
		match login::login(srv.clone()) {
			Some(user_logged) => {
				user = user_logged;
				
				sig_handler(user.clone());

				let _ = clearscreen::clear();
				println!("{}", format!("Login successful !").green().bold());
				break;
			},
			None => {
				max_try -= 1;
				if max_try <= 0 {
					eprintln!("{}", format!("Failed to login, exiting...").red().bold());
					return;
				}
				eprintln!("{}", format!("Failed to login ({} tries left)", max_try).red().bold());
				continue;
			}
		};
	}
	menu::menu(user.clone());

	login::logout(user);
	std::process::exit(0);
}

fn sig_handler(user: user::User) {
	let mut signals = Signals::new(&[SIGINT, SIGTERM, SIGQUIT, SIGHUP]).unwrap();
	std::thread::spawn(move || {
		for _ in signals.forever() {
			eprintln!("{}", format!("Exiting...").red().bold());
			
			ncurses::endwin();
			login::logout(user);

			std::process::exit(1);
		}
	});
}

fn title() {
	println!("{}", format!(r#"__        __   _                             _         _____ _____    ____   ___   ___  _     
\ \      / /__| | ___ ___  _ __ ___   ___   | |_ ___  |_   _|___ /   | __ ) / _ \ / _ \| |    
 \ \ /\ / / _ \ |/ __/ _ \| '_ ` _ \ / _ \  | __/ _ \   | |   |_ \   |  _ \| | | | | | | |    
  \ V  V /  __/ | (_| (_) | | | | | |  __/  | || (_) |  | |  ___) |  | |_) | |_| | |_| | |___ 
   \_/\_/ \___|_|\___\___/|_| |_| |_|\___|   \__\___/   |_| |____/___|____/ \___/ \___/|_____|
                                                               |_____|
"#).blue().bold());
}