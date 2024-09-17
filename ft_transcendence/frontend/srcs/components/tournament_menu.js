import { loadTournamentPong } from "./pongComponent.js";
import { appState } from "./stateManager.js";
const errorLink = document.getElementById('error');

export function Tournament()
{
	// console.log(errorLink);
	let url = `/api/tournament/create/${appState.userId}`;
	fetch(url, {
		method: 'GET',
		credentials: 'same-origin'
	})
	.then(response => response.json())
	.then(data => {
		// console.log('Success:', data);
		sessionStorage.setItem("tournament_id", data['tournamentid']);
		sessionStorage.setItem("playernb", data['playernb']);
		loadTournamentPong();
	})
	.catch((error) => {
		console.error('Error:', error);
	});
}

export function joinTournament(tournamentid) {
	return new Promise((resolve, reject) => {
		let userid = appState.userId;
		let csrf = getCookie("csrftoken");
		if (!isNaN(tournamentid) && tournamentid > 0 && tournamentid <= 9999)
		{
			fetch(`/api/tournament/join/${tournamentid}/${userid}`, {
				method: 'POST',
				headers: {
					'Content-Type': 'application/json',
					'X-CSRFToken': csrf,
				},
				body: JSON.stringify({ tournamentid, userid }),
				credentials: 'same-origin' 
			})
			.then(response => response.json())
			.then(data => {
				if(data['message'] == 'ok')
				{
					sessionStorage.setItem("tournament_id", tournamentid);
					sessionStorage.setItem("playernb", data['playernb']);
					loadTournamentPong();
					resolve(true);
				}
				else
				{
					reject(`Le tournoi ${tournamentid} n'existe pas, veuillez reessayer`);
				}
			})
			.catch((error) => {
				console.error('Error:', error);
			});
			
		}
	});
}

function getCookie(name) {
	const value = `; ${document.cookie}`;
	const parts = value.split(`; ${name}=`);
	if (parts.length === 2) return parts.pop().split(';').shift();
}