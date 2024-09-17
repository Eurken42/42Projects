import { onlineMatchmaking } from "./pong_menu.js";
import { Multiplayer } from "./pong_menu.js";
import { joinGame } from "./pong_menu.js";
import { Tournament } from "./tournament_menu.js";
import { joinTournament } from "./tournament_menu.js";
import { logoutUser } from "./userManager.js";
import { appState } from "./stateManager.js";
// import { makeid } from "../pong/javascript/pong.js" 
//import * as PongMenu from "./pong_menu.js";

export let scriptStarted;


export function renderPong() {
	const pongHTML = `
	<div class="card-game-wrapper glowing">
    <div class="card-game-test" style="background-image: url(Design/PongCoverImage.webp);">
        <div class="goldTitle">
            <div class="bg">Pong</div>
            <div class="fg">Pong</div>
        </div>
        <button type="button" class="btn btn-primary glowing-btn center mx-auto d-block button" data-bs-toggle="modal" data-bs-target="#pong">
        <span id="playBtnPong" class='glowing-txt' data-lang-key='playBtn'>JOUER</span></button>
    </div>
</div>
<!-- Modal -->
<div class="modal" id="pong" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
<div class="modal-dialog modal-fullscreen" role="document">
    <div class="modal-content">
        <div class="modal-header">
            <h5 class="modal-title" id="exampleModalLabel">Pong</h5>
            <button type="button" class="close" data-bs-dismiss="modal" aria-label="Close">
            <span aria-hidden="true">&times;</span>
            </button>
        </div>
        <div class="modal-body">
            <div class="card-game-wrapper glowing inside-card-modal">
                <!-- origPongContent -->
                <div id="origPong" class="card-game-inside">
                    <div class="d-flex flex-row justify-content-between pong-glowing-btn">
                        <link rel="stylesheet" type="text/css" href="../pong/css/pong_menu.css">
                        <div class="menugrid">
                            <nav class="nav">
                                <a id="localPongBtn" class="nav-link"  data-lang-key="localGame">Local</a>
                                <a id="multiPongBtn" class="nav-link" data-lang-key="createPriv">Create Private</a>
                                <div class="nav-link">
                                    <a  id="joinPongBtn"  data-lang-key="joinPriv">Join Private</a>
                                    <input type="text" id="gameCodeInputPrivate" class="inputGame" placeholder="Game ID">
                                </div>
                                <a class="errorGameInput" id="errorGameInputPrivate"></a>
                                <a id="searchBtn" class="nav-link"  data-lang-key="onlineMatchmaking">Online Matchmaking</a>
                                <a id="createTournament" class="nav-link" data-lang-key="createTourn">Create Tournament</a>
                                <div class="nav-link">
                                    <a id="joinTournamentBtn"  data-lang-key="joinTourn">Join Tournament</a>
                                    <input type="text" id="gameCodeInputTournament" class="inputGame" placeholder="Tournament ID">
                                </div>
                                <a class="errorGameInput" id="errorGameInputTournament"></a>
                                <a class="nav-link" data-bs-dismiss="modal">Exit</a>
                            </nav>
                        </div>
                    </div>
                </div>
                <!-- pongLocalContent -->
                <div id="pongLocal" class="h-100 align-items-center d-none">
                    <canvas id="backgroundLocal" class="h-100 w-100"></canvas>
                    <div id="countdownPong"></div>
                    <div id="displayscore"></div>
                    <div id ="displayvictory"></div>
                </div>
                <!-- multiplayerModalContent -->
                <div id="pongMulti" class="h-100 align-items-center d-none" style="position: relative;">
					<div class="load-3">
                        <div class="loading">
                            <p id="loading_txt">[GAME DOESN'T EXIST]</p>
                            <div class="line"></div>
                            <div class="line"></div>
                            <div class="line"></div>
                        </div>
                    </div>
                    <div id="countdownNorm" class="countdown"></div>
                    <div class="scoreboard">
                        <div class="row">
                            <div class="col col-display" id="scoreHome">0</div>
                            <div class="col col-display" id="scoreGuest">0</div>
                        </div>
                    </div>
					<div id="myModaldefeat" class="modaldeafeat">
						<p>DEFAITE</p>
					</div>
					<div id="myModalWin" class="modalWin">
						<p  data-lang-key="win">VICTOIRE</p>
					</div>
                    <canvas id="background" class="h-100 w-100"></canvas>
                </div>
                <!-- joinPongContent -->
                <div id="joinPong" class="h-100 align-items-center d-none">
                    <input id="chat-message-input" type="text" size="20"><br>
                    <input id="chat-message-submit" type="button" value="Send">
                </div>
                <!-- onlineMatchmaking --!>
                    <div id="matchmaking" class="h-100 align-items-center d-none">
                    </div>
                    
                    <!-- tournamentModalContent -->
                <div id="pongTournament" class="h-100 align-items-center d-none">
                    <canvas id="backgroundTournament" class="h-100 w-100"></canvas>
                    <div id="countdownTour" class="countdown"></div>
                    <div class="scoreboardTour">
                        <div class="row">
                            <div class="col col-display" id="scoreHomeTour">0</div>
                            <div class="col col-display" id="scoreGuestTour">0</div>
                        </div>
                    </div>
                    <div class="load-3">
                        <div class="loading">
                            <p id="loading_txt_tournament">[TOURNAMENT DOESN'T EXIST]</p>
							<ul id="userList"></ul>
                            <div class="line"></div>
                            <div class="line"></div>
                            <div class="line"></div>
                        </div>
                    </div>
                    <div id="myModal" class="modal">
                        <div class="modal-content">
                            <p>DEFAITE</p>
                            <p id="error"></p>
                            <button id="defaiteBtn">Revenir au menu</button>
                        </div>
                    </div>
                    <div id="myModal2" class="modal2">
                        <div id="startBtnDiv" class="startBtn">
                            <p data-lang-key="wonTourn">VOUS AVEZ REMPORTEZ LE TOURNOI, FELICITATIONS</p>
                            <button id="winnerBtn">Revenir au menu</button>
                        </div>
                    </div>
                    <div id="myModal3" class="modal3">
                        <div id="nextBtnDiv" class="nextBtn">
                            <p  data-lang-key="win">VICTOIRE</p>
                            <p id="score"></p>
                            <button id="nextGameBtn"  data-lang-key="nextGame">Prochaine partie</button>
                        </div>
                    </div>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
                    <button type="button" class="btn btn-primary">Save changes</button>
                </div>
            </div>
        </div>
    </div>
</div>`;
	const pongElement = document.createElement('div');
	pongElement.classList.add('col-12', 'col-md-6');
	pongElement.innerHTML = pongHTML;

	// let defeatButton = document.getElementById('defaiteBtn'); // Remplacez 'defeatButtonId' par l'ID réel de votre bouton
	// let winnerButton = document.getElementById('winnerBtn'); // Remplacez 'winnerButtonId' par l'ID réel de votre bouton
	// console.log(defeatButton);
	// // Ajoutez un gestionnaire d'événements click à chaque bouton
	// defeatButton.addEventListener('click', function() {
	// 	changeView('hero');
	// });

	// winnerButton.addEventListener('click', function() {
	// 	changeView('hero');
	// });
		
	addEventListeners(pongElement);
							
function addEventListeners(element) {
		const origPong = element.querySelector('#origPong');
		const multiPongBtn = element.querySelector('#multiPongBtn');
		const joinPongBtn = element.querySelector('#joinPongBtn');
		const pongMulti = element.querySelector('#pongMulti');
		const pongLocal = element.querySelector('#pongLocal');
		const localPongBtn = element.querySelector('#localPongBtn');
		const previousDiv = origPong ? pongMulti.previousElementSibling : null;
		const pongModal = element.querySelector('#pong');
		const matchmakingBtn = element.querySelector('#searchBtn');
		const pongTournament = element.querySelector('#pongTournament');
		const joinTournamentBtn = element.querySelector('#joinTournamentBtn');
		const createTournament = element.querySelector('#createTournament');
		const gameIdInputElem = element.querySelector('#gameCodeInputPrivate');

		gameIdInputElem.addEventListener('keyup', function(event) {
			if (event.code === 'Enter') {
				event.preventDefault();
				joinPongBtn.click();
			}
		});

		// * TOURNAMENTPONG
		createTournament.addEventListener('click', toggleVisibility);
		createTournament.addEventListener('click', function() {
			Tournament();
			pongLocal.classList.add('d-none');
			origPong.classList.add('d-none');
			pongMulti.classList.add('d-none');
			document.querySelectorAll('.card-game-inside > div').forEach(div => {
				div.classList.add('d-none');
			});
			pongTournament.classList.remove('d-none');
			var data = document.querySelector('#pongTournament').innerHTML;
			document.querySelector('#pongTournament').innerHTML = data;
		});
		
		//* JOINTOURNAMENT
		joinTournamentBtn.addEventListener('click', toggleVisibility);
		joinTournamentBtn.addEventListener('click', function() {
		const tournamentid = element.querySelector('#gameCodeInputTournament').value;
		const errorInputTour = document.getElementById('errorGameInputTournament');
		if (!isNaN(tournamentid) && tournamentid > 0 && tournamentid <= 9999)
		{
			joinTournament(tournamentid)
			.then(success => {
				if (success) {
					pongLocal.classList.add('d-none');
					origPong.classList.add('d-none');
					pongMulti.classList.add('d-none');
					document.querySelectorAll('.card-game-inside > div').forEach(div => {
						div.classList.add('d-none');
					});
					pongTournament.classList.remove('d-none');
					var data = document.querySelector('#pongTournament').innerHTML;
					document.querySelector('#pongTournament').innerHTML = data;
				}
			})
			.catch(error => {
				// console.log(error);
				errorInputTour.textContent = error;
				errorInputTour.style.display = "block";
				setTimeout(function() {
					errorInputTour.style.display = "none";
				}, 4000);
			});
		}
		else {
			errorInputTour.textContent = `Le tournoi ${tournamentid} n'existe pas, veuillez reessayer`;
			errorInputTour.style.display = "block";
			setTimeout(function() {
				errorInputTour.style.display = "none";
			}, 4000);
		}
		});

	//* LOCALPONG
	localPongBtn.addEventListener('click', toggleVisibility);
	localPongBtn.addEventListener('click', function() {
		origPong.classList.add('d-none');
		pongTournament.classList.add('d-none');
		pongMulti.classList.add('d-none');
		document.querySelectorAll('.card-game-inside > div').forEach(div => {
			div.classList.add('d-none');
		});
		pongLocal.classList.remove('d-none');
		var data = document.querySelector('#pongLocal').innerHTML;
		document.querySelector('#pongLocal').innerHTML = data;
		loadLocalPong();
	});

		// * JoinBtn
		multiPongBtn.addEventListener('click', toggleVisibility);

		joinPongBtn.addEventListener('click', function() {
		const gameIdInput = document.getElementById('gameCodeInputPrivate').value;
		const errorInput = document.getElementById('errorGameInputPrivate');
		if (!isNaN(gameIdInput) && gameIdInput > 0 && gameIdInput <= 9999) {	
			joinGame(gameIdInput)
				.then(success => {
					if (success) {
						pongLocal.classList.add('d-none');
						pongTournament.classList.add('d-none');
						origPong.classList.add('d-none');
						document.querySelectorAll('.card-game-inside > div').forEach(div => {
							div.classList.add('d-none');
						});
						pongMulti.classList.remove('d-none');
						var data = document.querySelector('#pongMulti').innerHTML;
						document.querySelector('#pongMulti').innerHTML = data;
					}
				})
				.catch(error => {
					errorInput.textContent = error;
					errorInput.style.display = "block";
					setTimeout(function() {
						errorInput.style.display = "none";
					}, 4000);
				});
		} else {
			errorInput.textContent = `La partie ${gameIdInput} n'existe pas, veuillez reessayer`;
			errorInput.style.display = "block";
			setTimeout(function() {
				errorInput.style.display = "none";
			}, 4000);
		}
});
		//* MULTIPONG
		multiPongBtn.addEventListener('click', toggleVisibility);		
		multiPongBtn.addEventListener('click', function() {
			Multiplayer();
			pongLocal.classList.add('d-none');
			origPong.classList.add('d-none');
			pongTournament.classList.add('d-none');
			document.querySelectorAll('.card-game-inside > div').forEach(div => {
				div.classList.add('d-none');
			});
			pongMulti.classList.remove('d-none');
			var data = document.querySelector('#pongMulti').innerHTML;
			document.querySelector('#pongMulti').innerHTML = data;
		});

		//* MATCHMAKING
		matchmakingBtn.addEventListener('click', toggleVisibility);
		matchmakingBtn.addEventListener('click', function() {
			onlineMatchmaking();
			pongLocal.classList.add('d-none');
			origPong.classList.add('d-none');
			pongTournament.classList.add('d-none');
			document.querySelectorAll('.card-game-inside > div').forEach(div => {
				div.classList.add('d-none');
			});
			pongMulti.classList.remove('d-none');
			var data = document.querySelector('#pongMulti').innerHTML;
			document.querySelector('#pongMulti').innerHTML = data;
			unloadScript();
		});

		
		pongModal.addEventListener('show.bs.modal', function () {
			appState.inModalGame = true;
			document.getElementById("userList").innerHTML = "";
			scriptStarted = true;
			document.querySelectorAll('.card-game-inside > div').forEach(div => {
				div.classList.remove('d-none');
			});
			origPong.classList.remove('d-none');
		});

		pongModal.addEventListener('hidden.bs.modal', function () {
			appState.inModalGame = false;
			document.getElementById("userList").innerHTML = "";
			unloadScript();
			scriptStarted = false;
			const pongLocal = element.querySelector('#pongLocal');
			const pongMulti = element.querySelector('#pongMulti');
			const pongTournament = element.querySelector('#pongTournament');
			pongLocal.classList.add('d-none');
			pongMulti.classList.add('d-none');
			pongTournament.classList.add('d-none');
			origPong.classList.remove('d-none');
		});
		
		// Define the event handler
		function toggleVisibility() {
			pongMulti.classList.toggle('d-none');
			if (previousDiv) {
				previousDiv.classList.toggle('d-none');
			}
		}
	}

	return pongElement;
}

// Change le contenu de la modale.
function changeDivContent(newContent) {
	const div = document.querySelector('.card-game-inside');
	div.innerHTML = newContent;
}

export function unloadScript() {
	// Désactiver les scripts chargés dynamiquement
	document.querySelectorAll('script[type="module"][data-pong="dynamic"]').forEach(script => {
		script.setAttribute('data-disabled', 'true');
		script.removeAttribute('type');
		if (window.gameSocket) {
			window.gameSocket.close();
			// console.log(window.gameSocket.readyState);
		}
		if (window.tournamentSocket) {
			window.tournamentSocket.close();
			// console.log(window.tournamentSocket.readyState);
		}
		// console.log(script);
		script.remove(); // Supprimer le script du DOM
	});
}


function loadLocalPong() {
	// Créer et ajouter le script localpong.js
	document.querySelectorAll('script[data-disabled="true"]').forEach(script => {
		script.setAttribute('type', 'module');
		script.removeAttribute('data-disabled');
	});
	const scriptLocalPong = document.createElement('script');
	scriptLocalPong.type = 'module';
	scriptLocalPong.src = '../localpong/localpong.js?' + new Date().getTime(); // Ajoute un horodatage à l'URL
	scriptLocalPong.setAttribute('data-pong', 'dynamic');  // Marqueur pour identifier les scripts chargés dynamiquement
	document.body.appendChild(scriptLocalPong);
}

export function loadMultiPong() {
	document.querySelectorAll('script[data-disabled="true"]').forEach(script => {
		script.setAttribute('type', 'module');
		script.removeAttribute('data-disabled');
	});
	const scriptMultiPong = document.createElement('script');
	scriptMultiPong.type = 'module';
	scriptMultiPong.src = '../pong/javascript/pong.js?' + new Date().getTime(); // Ajoute un horodatage à l'URL
	scriptMultiPong.setAttribute('data-pong', 'dynamic');  // Marqueur pour identifier les scripts chargés dynamiquement
	document.body.appendChild(scriptMultiPong);
}

export function loadTournamentPong() {
	document.querySelectorAll('script[data-disabled="true"]').forEach(script => {
		script.setAttribute('type', 'module');
		script.removeAttribute('data-disabled');
	});
	const scriptTournament = document.createElement('script');
	scriptTournament.type = 'module';
	scriptTournament.src = '../pong/javascript/pong_tournament.js?' + new Date().getTime(); // Ajoute un horodatage à l'URL
	scriptTournament.setAttribute('data-pong', 'dynamic');  // Marqueur pour identifier les scripts chargés dynamiquement
	document.body.appendChild(scriptTournament);
}

window.addEventListener('beforeunload', function (e) {
    // console.log('***&&&%%%$$$&&***$$$***%^^%');
	logoutUser();
});
