import { loadMultiPong } from "./pongComponent.js";

const errorLink = document.getElementById('errorGameInputPrivate');
let gameid;
let privategame = false;

function makeid(length) {
	let result = '';
	const characters = '0123456789';
	const charactersLength = characters.length;
	let counter = 0;
	while (counter < length) {
	  result += characters.charAt(Math.floor(Math.random() * charactersLength));
	  counter += 1;
	}
	return result;
  }

export function Multiplayer() {
	let url = '/api/game/create/';
	// console.log(url);
	fetch(url, {
		method: 'GET',
		credentials: 'same-origin' 
	})
	.then(response => response.json())
	.then(data => {
		// console.log('Success:', data);
		privategame = true;
		sessionStorage.setItem("privategame", privategame);
		sessionStorage.setItem("gameid", data['id']);
		loadMultiPong();
	})
	.catch((error) => {
		console.error('Error:', error);
	});
  }

export function joinGame(gameid) {
	return new Promise((resolve, reject) => {
		let url = '/api/game/' + gameid;
		if (!isNaN(gameid) && gameid > 0 && gameid <= 9999) {	
			// console.log(url);
			fetch(url, {
				method: 'GET',
				credentials: 'same-origin'
			})
			.then(response => response.json())
			.then(data => {
				// console.log('Success:', data);
				if (data['message'] == "Not found") {
					reject(`La partie ${gameid} n'existe pas, veuillez reessayer`);
				} else {
					privategame = true;
					sessionStorage.setItem("privategame", privategame);
					sessionStorage.setItem("gameid", gameid);
					loadMultiPong();
					resolve(true);
				}
			})
			.catch((error) => {
				console.error('Error:', error);
				reject(error);
			});
		} else {
			errorLink.style.display = "block";
			errorLink.textContent = `La partie ${gameid} n'existe pas, veuillez reessayer`;
			setTimeout(() => {
				errorLink.style.display = "none";
			}, 3000);
			reject(`La partie ${gameid} n'existe pas, veuillez reessayer`);
		}
	});
}

export function onlineMatchmaking() {
	let url = '/api/game/search/';
	// console.log(url);
	fetch(url, {
		method: 'GET',
		credentials: 'same-origin' 
	})
	.then(response => response.json())
	.then(data => {
		// console.log('Success:', data);
		if (data['message'] == "ok") {
			gameid = data['id'];
			privategame = false;
			sessionStorage.setItem("privategame", privategame);
			sessionStorage.setItem("gameid", gameid);
			loadMultiPong();
		} else if (data['message'] == 'Not Found'){
			gameid = data['id'];
			privategame = false;
			sessionStorage.setItem("privategame", privategame);
			sessionStorage.setItem("gameid", gameid);
			
			console.log("L'homme methode GET") // IMPORTANT NE PAS ENLEVER!!!
		}
		// console.log('id search' + gameid);
	})
	.catch((error) => {
		console.error('Error:', error);
	});
}

function getCookie(name) {
	const value = `; ${document.cookie}`;
	const parts = value.split(`; ${name}=`);
	if (parts.length === 2) return parts.pop().split(';').shift();
}
