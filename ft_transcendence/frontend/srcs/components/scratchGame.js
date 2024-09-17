
export function renderScratchGame() {
	const scratchGameHTML = `
    <div class="card-game-wrapper glowing">
        <div class="card-game-test" style="background-image: url(Design/blackJackImgPres.webp);">
            <div class="goldTitle">
                <div class="bg" data-lang-key='blackjack'>scratchGame</div>
                <div class="fg" data-lang-key='blackjack'>scratchGame</div>
            </div>
            <button type="button" class="btn btn-primary glowing-btn center mx-auto d-block" data-bs-toggle="modal" data-bs-target="#scratchGame">
                <span id="playBtnscratchGame" class='glowing-txt' data-lang-key='playBtn'>JOUER</span>
            </button>
        </div>
    </div>
    <!-- Modal -->
    <div class="modal" id="scratchGame" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
        <div class="modal-dialog modal-dialog-centered modal-xl" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="exampleModalLabel" data-lang-key='blackjack'>Black Jack</h5>
                    <button type="button" class="close" data-bs-dismiss="modal" aria-label="Close">
                        <span aria-hidden="true">&times;</span>
                    </button>
                </div>
                <div class="modal-body">

                <div class="container-scratch" id="js-container">
                    <canvas class="canvas-scratch w-100 h-100" id="js-canvas"></canvas>
                    <form class="form-scratch w-100 h-100" style="visibility: hidden;">
                        <h2>'Allo, 'Allo!</h2>
                        <h3>The secret code is:</h3>
                        <h1><code>HlkafSYc</code></h1>
                        <div>
                        <input type="text" name="code" placeholder="Secret Code">
                        </div>
                        <br>
                        <div>
                        <input type="submit" value="Submit">
                        </div>
                    </form>  
                </div>

                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
                    </div>
                </div>
            </div>
        </div>
    </div>
`;
    const scratchGameElement = document.createElement('div');
	scratchGameElement.classList.add('col-12', 'col-md-3');
    scratchGameElement.innerHTML = scratchGameHTML;    
	scratchGameElement.querySelector('#playBtnscratchGame').addEventListener('click', () => loadScripts());
    return scratchGameElement;
  }

  function loadScripts() {
	const scriptscratchGame = document.createElement('script');
	scriptscratchGame.type = 'module';
	scriptscratchGame.src = '../scratchTool.js';  // Assurez-vous que le chemin vers le script est correct
	scriptscratchGame.setAttribute('data-scratchGame', 'dynamic');  // Marqueur pour identifier les scripts chargés dynamiquement
	document.body.appendChild(scriptscratchGame);
}