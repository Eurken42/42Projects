import * as THREE from 'three';
import { LoadGLTFByPath } from './ModelHelper.js';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { EffectComposer } from 'three/addons/postprocessing/EffectComposer.js';
import { RenderPass } from 'three/addons/postprocessing/RenderPass.js';
import { UnrealBloomPass } from 'three/addons/postprocessing/UnrealBloomPass.js';
import { scriptStarted } from '../components/pongComponent.js';

// main
let scene;
let renderer;
let camera;
let controls;
let composer;
let scoreRight = 0;
let scoreLeft = 0;
const initialAngle = 0.45;
const speed = 0.25;
const mooveSpeed = 0.1;
const wallLimit = 6.5;
const ballLimit = 8.5;
let load = false;
let countdownValue = 3;
let speedIncreaseFactor = 0.7; // Facteur d'augmentation de la vitesse
let displayvictoryElement = document.getElementById('displayvictory');
let displayScoreElement = document.getElementById('displayscore');
let countdownElement = document.getElementById('countdownPong');
// const deltaTime = 30;
let PaddleRight;
let PaddleLeft;
let ball;
let ballVelocity;
let finished = false;

const KeyState = {
	KeyW: false,
	KeyS: false,
	ArrowUp: false,
	ArrowDown: false,
};

function displayvictory() {
    if (scoreLeft === finalScore) {
		displayvictoryElement.textContent = "Left player won !"
    } else if (scoreRight === finalScore) {
		displayvictoryElement.textContent = "Right player won !";
    }
	finished = true;
}

function countdown() {
	countdownElement.style.display = 'block';
	if (countdownValue > 0) {
		countdownElement.textContent = countdownValue + '...';
		countdownValue -= 1;
		setTimeout(countdown, 1000);
	} else {
		countdownElement.textContent = 'Go !!!';
		setTimeout(function() {
			countdownElement.style.display = 'none';
		}, 1000);
	}
}

function displayScore() { 
    if (displayScoreElement) {
        displayScoreElement.textContent = 'Score: ' + scoreLeft + ' - ' + scoreRight;
    } else {
        console.error('displayScoreElement is not defined');
    }
}

function init() {
	// Renderer
	resetScore();
	renderer = new THREE.WebGLRenderer({
		canvas: document.querySelector('#backgroundLocal'),
		antialias: true,
	});
	renderer.setSize(window.innerWidth, window.innerHeight);
	renderer.shadowMap.enabled = true;

	// Scene
	scene = new THREE.Scene();
	scene.background = new THREE.Color('purple');

	// Camera
	camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight);
	camera.position.set(0, 5, 5);

	// Controls
	controls = initControls();

	// Postprocessing
	composer = initPostprocessing();

	// Load the GLTF model and handle the PaddleRight
	LoadGLTFByPath(scene)
		.then(() => {
			handleGround();
			handleLight();
			handleText();
			handleBall();
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
	const scoreLeft = scene.getObjectByName('Text');
	scene.add(scoreLeft);
	scene.remove(scoreLeft);
	const scoreRight = scene.getObjectByName('Text001');
	scene.add(scoreRight);
	scene.remove(scoreRight);
}

function resetScore() {
	scoreLeft = 0;
	scoreRight = 0;
	if (displayScoreElement)
		displayScoreElement.textContent = 'Score: ' + scoreLeft + ' - ' + scoreRight;
	countdownValue = 3;
	countdown();
}

function handleBall() {
    const ballName = 'Ball';
    ball = scene.getObjectByName(ballName);
    if (ball) {
        ball.castShadow = true;
        ball.position.set(0, 0, 0);

        // Générer un angle aléatoire entre 40 et 60 degrés pour la première direction
        let angle1_deg = Math.random() * (60 - 40) + 40;
        let angle1_rad = angle1_deg * Math.PI / 180;
        // Calculer les composantes x et z de la vitesse de la balle pour la première direction
        let bv1_x = Math.cos(angle1_rad) * speed;
        let bv1_z = Math.sin(angle1_rad) * speed;

        // Générer un angle aléatoire entre 120 et 140 degrés pour la deuxième direction
        let angle2_deg = Math.random() * (140 - 120) + 120;
        let angle2_rad = angle2_deg * Math.PI / 180;
        // Calculer les composantes x et z de la vitesse de la balle pour la deuxième direction
        let bv2_x = Math.cos(angle2_rad) * speed;
        let bv2_z = Math.sin(angle2_rad) * speed;

        // Sélectionner aléatoirement l'une des deux directions pour le départ de la balle
		if (Math.random() < 0.5 && countdownValue == 0) {
            ballVelocity = new THREE.Vector3(bv1_x, 0, bv1_z);
        } else {
            ballVelocity = new THREE.Vector3(bv2_x, 0, bv2_z);
        }
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
	Ground.position.y = -1.9;
	Ground.receiveShadow = true;
}

// Fonction pour gérer l'appui sur une touche
function handleKeyDown(event) {
	if (KeyState.hasOwnProperty(event.code)) {
		KeyState[event.code] = true;
	}
}

// Fonction pour gérer le relâchement d'une touche
function handleKeyUp(event) {
	if (KeyState.hasOwnProperty(event.code)) {
		KeyState[event.code] = false;
	}
}

function handlePaddleRight() {
	const PaddleRightName = 'RightPaddle';
	PaddleRight = scene.getObjectByName(PaddleRightName);
	// x === 15
	
	if (PaddleRight) {
		PaddleRight.castShadow = true;
		// PaddleRight.receiveShadow = true;
		if (KeyState['ArrowUp'] && PaddleRight.position.z - mooveSpeed > -wallLimit && finished == false) {
			PaddleRight.position.z -= mooveSpeed;
		}
		if (KeyState['ArrowDown'] && PaddleRight.position.z + mooveSpeed < wallLimit && finished == false) {
			PaddleRight.position.z += mooveSpeed;
		}	
	}
}

function handlePaddleLeft() {
	const PaddleLeftName = 'LeftPaddle';
	PaddleLeft = scene.getObjectByName(PaddleLeftName);
	
	if (PaddleLeft) {
		PaddleLeft.castShadow = true;
		// PaddleLeft.receiveShadow = true;
		if (KeyState['KeyW'] && PaddleLeft.position.z - mooveSpeed > -wallLimit && finished == false) {
			PaddleLeft.position.z -= mooveSpeed;
		}
		if (KeyState['KeyS'] && PaddleLeft.position.z + mooveSpeed < wallLimit && finished == false) {
			PaddleLeft.position.z += mooveSpeed;
		}
	} 
}


function handlePaddleCollision() {
	const ballRadius = ball.geometry.boundingSphere.radius;
	const PaddleSizeX = 0;
	const PaddleSizeZ = PaddleLeft.geometry.boundingBox.max.z + 3;
	let isColliding = false;
	// console.log(PaddleSizeZ);

	if (PaddleLeft && PaddleRight && !isColliding) {
		// Vérifier la collision avec le paddle gauche
		if (
			ball.position.x - ballRadius < PaddleLeft.position.x + PaddleSizeX / 2 &&
			ball.position.x + ballRadius > PaddleLeft.position.x - PaddleSizeX / 2 &&
			ball.position.z + ballRadius > PaddleLeft.position.z - PaddleSizeZ / 2 &&
			ball.position.z - ballRadius < PaddleLeft.position.z + PaddleSizeZ / 2
			) {
				isColliding = true;
				ballVelocity.x *= -1;
				speedIncreaseFactor += 0.1;
			}
			// Vérifier la collision avec le paddle droit
			if (
				ball.position.x - ballRadius < PaddleRight.position.x + PaddleSizeX / 2 &&
				ball.position.x + ballRadius > PaddleRight.position.x - PaddleSizeX / 2 &&
				ball.position.z + ballRadius > PaddleRight.position.z - PaddleSizeZ / 2 &&
				ball.position.z - ballRadius < PaddleRight.position.z + PaddleSizeZ / 2
				) {
					isColliding = true;
					ballVelocity.x *= -1;
					speedIncreaseFactor += 0.1;
				}
			}
			isColliding = false;
	}

const finalScore = 5;
	
function handleWallColision() {
		if (ball.position.z > ballLimit || ball.position.z < -ballLimit) {
			ballVelocity.z *= -1;
		} else if (ball.position.x > 18) {
			scoreRight += 1;
			displayScore();
			ball.position.set(0, 0, 0);
			speedIncreaseFactor = 0.6;
			ballVelocity = new THREE.Vector3(Math.cos(initialAngle) * speed * -1, 0, Math.sin(initialAngle) * speed * -1);
		} else if( ball.position.x < -18) {
			scoreLeft += 1;
			displayScore();
			ball.position.set(0, 0, 0);
			speedIncreaseFactor = 0.6;
			ballVelocity = new THREE.Vector3(Math.cos(initialAngle) * speed, 0, Math.sin(initialAngle) * speed);
		}
		if (scoreLeft === finalScore || scoreRight === finalScore)
		{
			ball.position.set(0, 0, 0);
			ballVelocity = new THREE.Vector3(0, 0, 0);
			displayvictory();
			return ;
		}
}
	
	function updateBall() {
		if (ball) {
			ball.position.z += ballVelocity.z * speedIncreaseFactor;
			ball.position.x += ballVelocity.x * speedIncreaseFactor;
			// console.log(speedIncreaseFactor);
			handlePaddleCollision();
			handleWallColision();
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

let animationId;

function animate() {
	if (scriptStarted) {
		handlePaddleLeft();
		handlePaddleRight();
		if (countdownValue == 0)
			updateBall();
		controls.update();
		composer.render(scene, camera);
		animationId = requestAnimationFrame(animate);
	}
	else {
		stopAnimation();
	}
}

function stopAnimation() {
	cancelAnimationFrame(animationId);
	displayScoreElement.textContent = "";
	displayvictoryElement.textContent = "";
	countdownElement.textContent = "";
}

document.addEventListener('keydown', handleKeyDown);
document.addEventListener('keyup', handleKeyUp);

// Appel de la fonction d'initialisation
init();