import { createButtonComponent,  } from "./globalComponent.js";

export function renderRun() {
    const runHTML = `
        <div class="card-game-wrapper glowing">
            <div class="card-game-test" style="background-image: url(Design/RushCoverImage.webp);">
                <div class="goldTitle">
                    <div class="bg">Casino Rush</div>
                    <div class="fg">Casino Rush</div>
                </div>
                <button type="button" class="btn btn-primary glowing-btn center mx-auto d-block button" data-toggle="modal" data-target="#run">
                <span id="playBtnRun" class='glowing-txt' data-lang-key='playBtn'>JOUER</span></button>
            </div>
        </div>

            <!-- Modal -->
        <div class="modal" id="run" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
            <div class="modal-dialog modal-dialog-centered modal-xl" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title" id="exampleModalLabel">Casino Rush</h5>
                        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                        <span aria-hidden="true">&times;</span>
                        </button>
                    </div>
                    <div class="modal-body">
                    <div class="card-game-wrapper glowing inside-card-modal">
                    <div class="card-game-inside" style="background-image: url(Design/RushCoverImage.webp);">
                        <div class="goldTitle">
                            <div class="bg">Casino Rush</div>
                            <div class="fg">Casino Rush</div>
                        </div>
                        <div class="d-flex flex-column" id="menu">
                            <div class="d-flex flex-row justify-content-between mb-2">
                                <button id="createBtn" class='glowing-btn'><span class='glowing-txt' data-lang-key='createRoomPong'>CREATE GAME</button>
                                <button id="joinBtn" class='glowing-btn'><span class='glowing-txt' data-lang-key='joinRoomPong'>JOIN GAME</button>
                                <button id="listBtn" class='glowing-btn'><span class='glowing-txt' data-lang-key='joinRandomRoomPong'>LIST GAME</button>
                            </div>
                            <input type="text" class=id="gameCodeInput" placeholder="Enter Game Code"><br>
                            <a id="error"></a>
                        </div>
                    </div>
                </div>
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
                        <button type="button" class="btn btn-primary">Save changes</button>
                    </div>
                </div>
            </div>
        </div>
    `;

    const runLocal = `
    <h1>partie en local</h1>
    `;
    const runElement = document.createElement('div');
    runElement.classList.add('col-12', 'col-md-6');
    runElement.innerHTML = runHTML;
    const originalModalContent = runElement.querySelector('.modal-content').innerHTML;

    /**
     * Ajoute des gestionnaires d'événements aux boutons dans la modale.
     * - Le bouton 'localPongBtn' déclenche le jeu Pong en mode local.
     * - Le bouton 'multiPongBtn' change le contenu de la modale pour le mode multijoueur -> a faire.
     * - Le bouton 'tourPongBtn' change le contenu de la modale pour le mode tournoi -> a faire.
     */
/*     function addEventListeners() {
        runElement.querySelector('#localRunBtn').addEventListener('click', function() {
            changeDivContent(runLocal);
            initPong();
        });

        runElement.querySelector('#multiRunBtn').addEventListener('click', function() {
            changeDivContent('Contenu pour le mode multijoueur');
        });

        runElement.querySelector('#tourRunBtn').addEventListener('click', function() {
            changeDivContent('Contenu pour le mode tournoi');
        });
    }

    addEventListeners(); */

    // Réinitialise le contenu de la modale lorsque celle-ci est fermée.
    runElement.querySelector('#run').addEventListener('hidden.bs.modal', function () {
        runElement.querySelector('.modal-content').innerHTML = originalModalContent;
        addEventListeners();
    });

    return runElement;
}

// Change le contenu de la modale.
function changeDivContent(newContent) {
    const div = document.querySelector('.card-game-inside');
    div.innerHTML = newContent;
}