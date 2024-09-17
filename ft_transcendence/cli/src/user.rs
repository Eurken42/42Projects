use reqwest::blocking::Client;
use colored::Colorize;
use std::time::Duration;

#[derive(Clone)]
#[derive(Debug)]
pub struct User {
	id: String,
	username: String,
	logged_in: bool,
	client: Client,
	server: String,
}

impl User {
	pub fn new() -> User {
		User {
			id: String::new(),
			username: String::new(),
			logged_in: false,
			client: Client::new(),
			server: String::new(),
		}
	}
	
	pub fn fill(&mut self, id: String, username: String, client: Client, server: String) {
		self.id = id;
		self.username = username;
		self.logged_in = true;
		self.client = client;
		self.server = server;
	}
	
	pub fn get_client(&self) -> Client {
		self.client.clone()
	}

	pub fn get_server(&self) -> String {
		self.server.clone()
	}

	pub fn get_id(&self) -> String {
		self.id.clone()
	}

	pub fn get_csrf(&self) -> Option<String> {
		let crsf = self.client.get("https://{server}/api/√".replace("{server}", self.server.as_str()))
			.header("User-Agent", "cli_rust")
			.header("Accept", "application/json")
			.timeout(Duration::from_secs(3));
		let crsf = crsf.build();
		let res_csrf = self.client.execute(crsf.expect("ERROR WHILE BUILDING THE REQUEST"));
		let csrf = match res_csrf {
			Ok(res) => {
				if res.headers().get("set-cookie").is_none() {
					eprintln!("{}", format!("No CSRF-Token in the header").red());
					return None;
				}
				let csrf = res.headers().get("set-cookie").unwrap();
				csrf.to_str().unwrap().to_string()
			},
			Err(err) => {
				eprintln!("{}", format!("Error in respond: {:#?}", err).red());
				return None;
			}
		};
		let csrf_token = csrf.split(';').nth(0).unwrap().split('=').nth(1).unwrap().to_string();

		return Some(csrf_token);
	}

	pub fn set_id(&mut self, id: String) {
		self.id = id;
	}

	pub fn set_username(&mut self, username: String) {
		self.username = username;
	}
}
