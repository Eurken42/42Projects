use std::io;
use std::io::Write;

use crate::user::User;
use crate::pong;
use crate::tournament;
use colored::Colorize;


fn print_menu() {
	println!("{}", format!(r" __  __").yellow().bold());
	println!("{}", format!(r"|  \/  | ___ _ __  _   _ ").yellow().bold());
	println!("{}", format!(r"| |\/| |/ _ \ '_ \| | | |").yellow().bold());
	println!("{}", format!(r"| |  | |  __/ | | | |_| |").yellow().bold());
	println!("{}", format!(r"|_|  |_|\___|_| |_|\__,_|").yellow().bold());
	println!();
}

/**
 * Display the menu and handle the user's choice
 * 
 * Args:
 * 		user: User - The user that is currently logged in
 */
pub fn menu(user: User) {
	loop {
		print_menu();

		let mut choice = String::new();
		println!("1. Game");
		println!("2. Tournament");
		println!("q. Quit\n");

		print!("Choice: ");
		_ = io::stdout().flush();
		io::stdin()
			.read_line(&mut choice)
			.expect("Error while reading user input");
		choice = (*choice.trim()).to_string();
		
		_ = clearscreen::clear();
		match choice.as_str() {
			"1" =>  menu_game(user.clone()),
			"2" => menu_tournament(user.clone()),
			"q" => break,
			_ => {
				println!("{}", format!("Invalid choice").red());
				continue;
			}
		}
	}
}

fn print_game() {
	println!("{}", format!(r" __  __                     ____ ").yellow().bold());
	println!("{}", format!(r"|  \/  | ___ _ __  _   _   / ___| __ _ _ __ ___   ___ ").yellow().bold());
	println!("{}", format!(r"| |\/| |/ _ \ '_ \| | | | | |  _ / _` | '_ ` _ \ / _ \").yellow().bold());
	println!("{}", format!(r"| |  | |  __/ | | | |_| | | |_| | (_| | | | | | |  __/").yellow().bold());
	println!("{}", format!(r"|_|  |_|\___|_| |_|\__,_|  \____|\__,_|_| |_| |_|\___|").yellow().bold());
	println!();
}

/**
 * Display the game menu and handle the user's choice	
 * 
 * Args:
 * 		user: User - The user that is currently logged in
 */
fn menu_game(user: User) {
	loop {
		print_game();

		let mut choice = String::new();
		println!("1. Matchmaking");
		println!("2. Create a private game");
		println!("3. Join a private game");
		println!("q. Back to the menu\n");

		print!("Choice: ");
		let _ = io::stdout().flush();
		io::stdin()
			.read_line(&mut choice)
			.expect("Error while reading user input");
		choice = (*choice.trim()).to_string();
		
		_ = clearscreen::clear();
		match choice.as_str() {
			"1" => {
				match pong::matchmaking(user.clone()) {
					Some(res) => {
						if res {
							println!("{}", format!("You won the game").green().bold());
						} else {
							println!("{}", format!("You lost the game").red().bold());
						}
					},
					None => {
						// println!("{}", format!("Error during the game").red());
					}
				}
			},
			"2" => {
				match pong::create_game(user.clone()) {
					Some(res) => {
						if res {
							println!("{}", format!("You won the game").green().bold());
						} else {
							println!("{}", format!("You lost the game").red().bold());
						}
					},
					None => {
						// println!("{}", format!("Error during the game").red());
					}
				}
			},
			"3" => {
				match pong::join_game(user.clone()) {
					Some(res) => {
						if res {
							println!("{}", format!("You won the game").green().bold());
						} else {
							println!("{}", format!("You lost the game").red().bold());
						}
					},
					None => {
						// println!("{}", format!("Error during the game").red());
					}
				}
			},
			"4" | "q" => break,
			_ => {
				println!("{}", format!("Invalid choice").red());
				continue;
			}
		}
	}
}

fn print_tournament() {
	println!("{}", format!(r" __  __                    _____                                                 _   ").yellow().bold());
	println!("{}", format!(r"|  \/  | ___ _ __  _   _  |_   _|__  _   _ _ __ _ __   __ _ _ __ ___   ___ _ __ | |_ ").yellow().bold());
	println!("{}", format!(r"| |\/| |/ _ \ '_ \| | | |   | |/ _ \| | | | '__| '_ \ / _` | '_ ` _ \ / _ \ '_ \| __|").yellow().bold());
	println!("{}", format!(r"| |  | |  __/ | | | |_| |   | | (_) | |_| | |  | | | | (_| | | | | | |  __/ | | | |_ ").yellow().bold());
	println!("{}", format!(r"|_|  |_|\___|_| |_|\__,_|   |_|\___/ \__,_|_|  |_| |_|\__,_|_| |_| |_|\___|_| |_|\__|").yellow().bold());
	println!();
}

/**
 * Display the tournament menu and handle the user's choice
 * 
 * Args:
 * 		user: User - The user that is currently logged in
 */
fn menu_tournament(user: User) {
	loop {
		print_tournament();
	
		let mut choice = String::new();
		println!("1. Create a tournament");
		println!("2. Join a tournament");
		println!("q. Back to the menu\n");

		print!("Choice: ");
		let _ = io::stdout().flush();
		io::stdin()
			.read_line(&mut choice)
			.expect("Error while reading user input");
		choice = (*choice.trim()).to_string();

		_ = clearscreen::clear();
		match choice.as_str() {
			"1" => tournament::create_tournament(user.clone()),
			"2" => tournament::join_tournament(user.clone()),
			"q" => break,
			_ => eprintln!("{}", format!("Invalid choice").red())
		}
	}
}
