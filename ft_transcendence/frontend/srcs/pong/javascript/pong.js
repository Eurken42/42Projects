import * as THREE from 'three';
import { LoadGLTFByPath } from './ModelHelper.js';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { TextGeometry } from 'three/addons/geometries/TextGeometry.js';
import { FontLoader } from 'three/addons/loaders/FontLoader.js';
import { EffectComposer } from 'three/addons/postprocessing/EffectComposer.js';
import { RenderPass } from 'three/addons/postprocessing/RenderPass.js';
import { UnrealBloomPass } from 'three/addons/postprocessing/UnrealBloomPass.js';
//donnees de l'utilisateur stocke dans le navigateur
import { appState } from '../../components/stateManager.js';
//import { gameid } from './join.js';
// import { RectAreaLightHelper } from 'three/addons/helpers/RectAreaLightHelper.js';

let active = false;
let gameid = sessionStorage.getItem('gameid');
let userid = sessionStorage.getItem('userId');
let privategame = sessionStorage.getItem('privategame');
const scoreR = document.getElementById("scoreGuest");
const scoreL = document.getElementById("scoreHome");
const div_scoreboard = document.querySelector('.scoreboard');
const div_scoreboardTour = document.querySelector('.scoreboardTour');
const loadingElement = document.getElementById('loading_txt');
const loadingDot = document.getElementsByClassName('loading');
document.getElementById('myModalWin').style.display = "none";
document.getElementById('myModaldefeat').style.display = "none";
let game_data;
let renderer;
let scene;
let camera;
let controls;
let composer;
let player1Score = 0;
let player2Score = 0;
const initialAngle = 0.45;
const speed = 0.25;
let scoreLeft;
let scoreRight;
let ballVelocity;
let currentNum = 7;

const KeyState = {
	KeyW: false,
	KeyS: false,
	ArrowUp: false,
	ArrowDown: false,
};

if (gameid === "null" || gameid === undefined) {
	
}

window.gameSocket = new WebSocket(
	'wss://'
	+ window.location.host
	+ '/ws/'
	+ 'game'
	+ '/'
	+ gameid
	+ '/'
);

gameSocket.onerror = function(e) {
	return ;
}

div_scoreboard.style.display = 'none';
div_scoreboardTour.style.display = 'none';
loadingDot[0].style.display = 'block';
loadingElement.style.display = 'flex';
if (privategame === "true")
{
	loadingElement.innerHTML = "[WAITING FOR OPPONENT]<br>Game ID : " + gameid;
}
else 
{
	loadingElement.textContent = "[WAITING FOR OPPONENT]";
}

//console.log(privategame);

function addClassDelayed(element, className, delay) {
    setTimeout(function() {
        element.classList.add(className);
    }, delay);
}

function scaleCam() {
	return (50 - (window.innerWidth - 300) / 240);
}

function displayRotateMessage() {
    var diplayRotate = document.createElement('div');
    diplayRotate.innerHTML = "Veuillez tourner votre téléphone en mode paysage pour une meilleure expérience.";
	diplayRotate.id = "rotate-message";
    diplayRotate.style.position = 'absolute';
    diplayRotate.style.top = '50%';
    diplayRotate.style.left = '50%';
    diplayRotate.style.transform = 'translate(-50%, -50%)';
    diplayRotate.style.fontSize = '18px';
    diplayRotate.style.color = '#ffffff';
    diplayRotate.style.backgroundColor = 'rgba(0, 0, 0, 0.7)';
    diplayRotate.style.padding = '20px';
    diplayRotate.style.borderRadius = '5px';
    diplayRotate.style.zIndex = '9999';
    document.body.appendChild(diplayRotate);
}

function hideRotateMessage() {
    var diplayRotate = document.getElementById('rotate-message');
    if (diplayRotate) {
        diplayRotate.remove();
    }
}

function checkPortraitMode() {
	if (window.innerHeight > window.innerWidth) {
		displayRotateMessage();
	} else {
		hideRotateMessage();
	}
}

function init() {
	// Renderer
	renderer = new THREE.WebGLRenderer({
		canvas: document.querySelector('#background'),
		antialias: true,
	});
	renderer.setSize(window.innerWidth, window.innerHeight);
	renderer.shadowMap.enabled = true;

	// Scene
	scene = new THREE.Scene();
	//scene.background = new THREE.Color('purple');

	// Camera
	camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight);
	camera.position.set(0, scaleCam(), scaleCam());
	// Controls
	controls = initControls();

	// Postprocessing
	composer = initPostprocessing();

	scoreL.textContent = 0;
	scoreR.textContent = 0;
	// Load the GLTF model and handle the PaddleRight
	LoadGLTFByPath(scene)
		.then(() => {
			handleBackground();
			handleGround();
			handleLight();
			handleText();
			gameSocket.send(JSON.stringify({
				'message' : 'load'
			}));
			document.getElementById("userList").innerHTML = "";
			if (div_scoreboard) {
				div_scoreboard.style.display = 'flex';
			}
			loadingElement.style.display = 'none';
			loadingDot[0].style.display = 'none';
			// checkPortraitMode();
			// createScoreTexts();
		})
		.catch((error) => {
			console.error('Error loading JSON scene:', error);
		});
		scene.castShadow = true;
		scene.receiveShadow = true;
		// Animation loop
		animate();
}


function handleText() {
	scoreLeft = scene.getObjectByName('Text');
	scene.add(scoreLeft);
	scene.remove(scoreLeft);
	scoreRight = scene.getObjectByName('Text001');
	scene.add(scoreRight);
	scene.remove(scoreRight);
}

function handleBall() {
	const ballName = 'Ball';
	ball = scene.getObjectByName(ballName);
	if (ball) {
		ball.castShadow = true;
		// ball.receiveShadow = true;
		ball.position.set(0, 0, 0);
		ballVelocity = new THREE.Vector3(Math.cos(initialAngle) * speed, 0, Math.sin(initialAngle) * speed);
	} else {
		console.error('Ball not found');
	}
	
}

function handleLight() {
	const light = new THREE.AmbientLight( 0xFFFFFFF , 0.4 ); // soft white light
	const dLight = new THREE.DirectionalLight( 0xFFFFFFF, 1.1 );
	dLight.castShadow = true;
	dLight.shadow.mapSize.width = 4096;
	dLight.shadow.mapSize.height = 4096;
	const d = 35;
	dLight.shadow.camera.left = - d;
	dLight.shadow.camera.right = d;
	dLight.shadow.camera.top = d;
	dLight.shadow.camera.bottom = - d;
	scene.add( light );
	scene.add( dLight );
	const width = 35;
	const height = 5;
	const intensity = 1.9;
	const rectLightDown = new THREE.RectAreaLight( 0xffffff, intensity,  width, height );
	const rectLightUp = new THREE.RectAreaLight( 0xffffff, intensity,  width, height );
	rectLightDown.position.set( 0, 0, 8.7 );
	rectLightUp.position.set( 0, 0, -8.7 );
	rectLightDown.lookAt( 0, 0, 0 );
	rectLightUp.lookAt( 0, 0, 0 );
	scene.add( rectLightDown );
	scene.add( rectLightUp );
}

function onWindowResize() {
	// checkPortraitMode();
	camera.position.set(0, scaleCam(), scaleCam());
	camera.aspect = window.innerWidth / window.innerHeight;
	camera.updateProjectionMatrix();
	renderer.setSize(window.innerWidth, window.innerHeight);
}

function initControls() {
	const newControls = new OrbitControls(camera, renderer.domElement);
	newControls.maxPolarAngle = Math.PI * 0.5;
	newControls.minDistance = 25;
	newControls.maxDistance = 45;
	return newControls;
}

function initPostprocessing() {
	const renderScene = new RenderPass(scene, camera);
	const bloomPass = new UnrealBloomPass(new THREE.Vector2(window.innerWidth, window.innerHeight), 0.1, 1, 0.60);
	const newComposer = new EffectComposer(renderer);
	newComposer.castShadow = true;
	newComposer.addPass(renderScene);
	newComposer.addPass(bloomPass);
	
	return newComposer;
}

function handleGround() {
	const groundName = 'Ground';
	const Ground = scene.getObjectByName(groundName);
	Ground.position.y = -0.5;
	// Ground.roughness = 1.8;
	Ground.receiveShadow = true;
}

// Fonction pour gérer l'appui sur une touche
function handleKeyDown(event) {
	if (currentNum < 0) {
		if (event.code == 'ArrowUp')
		{
			gameSocket.send(JSON.stringify({
			'message' : 'Up'
			}));
		}
		else if (event.code == 'ArrowDown')
		{
			gameSocket.send(JSON.stringify({
			'message' : 'Down'
			}));
		}
		else if (event.code == 'KeyW')
		{
			gameSocket.send(JSON.stringify({
				'message' : 'W'
			}));
		}
		else if (event.code == 'KeyS')
		{
			gameSocket.send(JSON.stringify({
				'message' : 'S'
			}));
		}
		else if (event.code == 'Enter')
		{
			gameSocket.send(JSON.stringify({
				'message' : 'Start'
			}));
		}
		else if (event.code == 'Escape')
		{
			gameSocket.send(JSON.stringify({
			'message' : 'Stop'
			}));
		}
	}
}

// Fonction pour gérer le relâchement d'une touche
function handleKeyUp(event) {
	if (KeyState.hasOwnProperty(event.code)) {
		KeyState[event.code] = false;
	}
}


function handleBackground() {
	// scene.background += new THREE.Color(Math.random() % 21);
	const time = performance.now() * 0.001; // Utilisez le temps pour créer une animation fluide

    // Modifiez ici les valeurs pour ajuster la couleur et le mouvement
    const hue = (time * 10) % 360; // Changement de teinte
    const saturation = 100; // Intensité de la couleur
    const lightness = 50; // Luminosité

    // Convertissez HSL en couleur RVB
    const color = new THREE.Color().setHSL(hue / 360, saturation / 100, lightness / 100);

    // Appliquez la couleur au fond de la scène
   scene.background = color;
}

function anim() {
    if (currentNum >= 0) {
        addClassDelayed(document.getElementById("countdownNorm"), "puffer", 600);
		currentNum--;
        if (currentNum > 0) {
            document.getElementById("countdownNorm").innerHTML = currentNum;
        } else if (currentNum == 0) {
            document.getElementById("countdownNorm").innerHTML = "GO !";
        } else {
            document.getElementById("countdownNorm").innerHTML = "";
            document.getElementById("countdownNorm").classList.remove("puffer");
            return;
        }
        document.getElementById("countdownNorm").classList.remove("puffer");
    } else {
        return;
    }
}

let whoami;

gameSocket.onmessage = function(e) {
	
	game_data = JSON.parse(e.data);
	if (game_data.action == "userid") {
		gameSocket.send(JSON.stringify({
			'message' : 'userid',
			'userid' : appState.userId
		}));
	} 
	else if (game_data.action == "allin") {
		loadingElement.textContent = "[LOADING GAME ...]";
		init();
	}
	else if(game_data.action == "playernumber") {
		whoami = game_data.playernumber;
	}
	else if (game_data.action == "private")
	{
		if (privategame == 'true')
		{
			gameSocket.send(JSON.stringify({
			'message' : 'private'
			}));
		}
		else
		{
			gameSocket.send(JSON.stringify({
			'message' : 'public'
			}));
		}
	} else if (game_data.action == 'Stop') {
		gameSocket.send(JSON.stringify({
			'message' : 'mdr'
			}));
		// const errorElement = document.getElementById('error');
		// errorElement.textContent = "Final score : " + game_data.scorep2 + " - " + game_data.scorep1;
		if (game_data.winner != 0){
			if (whoami == game_data.winner)
				document.getElementById('myModalWin').style.display = "block";
			else
				document.getElementById('myModaldefeat').style.display = "block";
		}
		else
		{
			if (game_data.scorep1 > game_data.scorep2) {
				if (whoami == 1)
					document.getElementById('myModalWin').style.display = "block";
				else
					document.getElementById('myModaldefeat').style.display = "block";
			}
			else {
				if (whoami == 2)
					document.getElementById('myModalWin').style.display = "block";
				else
					document.getElementById('myModaldefeat').style.display = "block";
			}
		}
		// document.getElementById("myModal").style.display = "block";
		sessionStorage.setItem("gameid", null);
		gameSocket.close();
	} else if (game_data.action == "userleave") {
		// const errorElement = document.getElementById('error');
		// errorElement.textContent = "A user left the game";
		// document.getElementById("myModal").style.display = "block";
		gameSocket.close();
	} else if (game_data.action == 'score') {
		if (game_data.scorep1 != undefined && game_data.scorep2 != undefined) {
			// const scoreL = document.getElementById("scoreHome");
			scoreL.textContent = game_data.scorep2;
			// const scoreR = document.getElementById("scoreGuest");
			scoreR.textContent = game_data.scorep1;
		}
	} else if (game_data.action == 'counter') {
		if (game_data.num < currentNum) {
			currentNum = game_data.num;
			if (currentNum >= 0) {
				setTimeout(function() {}, 1500);
				setInterval(function() { anim(); }, 1325);
			}
		}
	}
	else {	
		const ball = scene.getObjectByName('Ball');
		const PaddleLeft = scene.getObjectByName("LeftPaddle");
		const PaddleRight = scene.getObjectByName("RightPaddle");
		if (game_data.action == 'paddle1' && PaddleRight) {
			PaddleRight.position.x = parseFloat(game_data.prx);
			PaddleRight.position.z = parseFloat(game_data.prz);
		} else if (game_data.action == 'paddle2' && PaddleLeft) {
			PaddleLeft.position.x = parseFloat(game_data.plx);
			PaddleLeft.position.z = parseFloat(game_data.plz);
		} else if (game_data.action == 'ball' && ball) {
			ball.position.x = parseFloat(game_data.bx);
			ball.position.z = parseFloat(game_data.bz);
		}
		else if (game_data.action == 'score') {
			if (game_data.scorep1 != undefined && game_data.scorep2 != undefined) {
				const scoreElement = document.getElementById("score");
				scoreElement.textContent = game_data.scorep2 + " - " + game_data.scorep1;
			}
		} else if (game_data.action == 'counter') {
			if (game_data.num < currentNum) {
				currentNum = game_data.num;
				if (currentNum >= 0) {
					setTimeout(function() {}, 1500);
					setInterval(function() { anim(); }, 1325);
				}
			}
		}
	}
};


function update_game_data() {
	const PaddleRightName = 'RightPaddle';
	const PaddleLeftName = 'LeftPaddle';
	ball = scene.getObjectByName('Ball');
	PaddleRight = scene.getObjectByName(PaddleRightName);
	PaddleLeft = scene.getObjectByName(PaddleLeftName);
	// console.log(PaddleRight);
	// console.log(ball);
	PaddleRight.position.x = parseFloat(game_data.paddleright_position_x);
	PaddleRight.position.z = parseFloat(game_data.paddleright_position_z);
	PaddleLeft.position.x = parseFloat(game_data.paddleleft_position_x);
	PaddleLeft.position.z = parseFloat(game_data.paddleleft_position_z);
	//PaddleLeft.position.z = parseFloat(game_data.paddleleft_position_z);
	ball.position.x = parseFloat(game_data.ball_position_x);
	ball.position.z = parseFloat(game_data.ball_position_z);

}

function animate() {
	requestAnimationFrame(animate);
	controls.update();
	//composer.render(scene, camera);
	renderer.render(scene, camera);
}

document.addEventListener('keydown', handleKeyDown);
document.addEventListener('keyup', handleKeyUp);
window.addEventListener('resize', onWindowResize);
