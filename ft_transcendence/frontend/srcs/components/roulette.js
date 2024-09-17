export function spinWheel(ballAnim) {
    document.querySelector(".winner").textContent = "";
    document.querySelector("#winnerMsg").textContent = ``;
  
    const randInt = (min, max) => {
      return Math.floor(Math.random() * (max - min + 1)) + min;
    };
  
    const winAngle = randInt(1800, 3600);
    ballAnim.setAttribute("values", `0 50 50; ${winAngle} 50 50`);
  
    const index = Math.round(winAngle / (360 / 38)) % 38;
    const winNumber = nums[index];
  
    balls.forEach((ball) => {
      ball.beginElement();
    }, false);
  
    // individual active classes on the number bets
    const bets = document.querySelectorAll(".active");
    // console.log(bets);
    let betsMade = [];
  
    bets.forEach((bet) => {
      // pay the man
      oldMoney = totalMoney;
      totalMoney--;
      updateMoney();
  
      // store the text content for each of the active bets
      betsMade.push(bet.querySelector("text").textContent);
    }); 
    
    // how we check our non-individual number winners
    const checkWinner = (elt, arr, winnings = 1) => {
      if (elt.classList.contains("active")) {
        if (arr.includes(winNumber)) {
          // conso÷le.log("total money = " + totalMoney);
          moneyWon === winnings;
          totalMoney += winnings;
          lostWon = totalMoney - oldMoney;
          updateMoney();
          win();
        }
      }
    }
    
    // run this after a roll delay
    balls[0].addEventListener('endEvent', (event) => {
      // console.log('spin over!');
      // if our individual winners include the winning number, tell us we won
      if (betsMade.includes(winNumber.toString())) {
        totalMoney = totalMoney + 38;
        moneyWon = totalMoney - oldMoney;
        updateMoney();
        win();
      } else {
        lose();
      }
  
      checkWinner(redBtn, redNums, 2);
      checkWinner(blackBtn, blackNums, 2);
      checkWinner(evenBtn, evenNums, 2);
      checkWinner(oddBtn, oddNums, 2);
      checkWinner(firstHalf, firstHalfNums, 2);
      checkWinner(secondHalf, secondHalfNums, 2);
      checkWinner(firstThird, thirdsNums[0], 3);
      checkWinner(secondThird, thirdsNums[1], 3);
      checkWinner(lastThird, thirdsNums[2], 3);
      checkWinner(two2one[0], two2oneNums[0], 3);
      checkWinner(two2one[1], two2oneNums[1], 3);
      checkWinner(two2one[2], two2oneNums[2], 3);
      
      document.querySelector(".winner").textContent = winNumber;
    });
  }
  
  export function renderRoulette() {
    //spinWheel();
      const rouletteHTML = `
      <div class="card-game-wrapper glowing">
        <div class="card-game-test" style="background-image: url(Design/RoulettePresImg.webp);">
          <div class="goldTitle">
            <div class="bg" data-lang-key='roulette'>Roulette</div>
            <div class="fg" data-lang-key='roulette'>Roulette</div>
          </div>
          <button type="button" class="btn btn-primary glowing-btn center mx-auto d-block" data-bs-toggle="modal" data-bs-target="#roulette">
          <span id="playBtnRoulette" class='glowing-txt' data-lang-key='playBtn'>JOUER</span></button>
        </div>
      </div>
            
            <!-- Modal -->
            <div class="modal" id="roulette" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
              <div class="modal-dialog modal-dialog-centered modal-xl" role="document">
                <div class="modal-content">
                  <div class="modal-header">
                    <h5 class="modal-title" id="exampleModalLabel" data-lang-key='roulette'>Roulette</h5>
                    <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                      <span aria-hidden="true">&times;</span>
                    </button>
                  </div>
                  <div class="modal-body">
                      <div class="container">
                          <div class="box1">
                          <svg id="rouletteWheel" viewBox="0 0 100 100">
                              <title>Spin the wheel!</title>
                              <radialGradient id="board">
                              <stop offset="0%" stop-color="#332701" />
                              <stop offset="50%" stop-color="#ffe69c" />
                              <stop offset="100%" stop-color="#332701" />
                              </radialGradient>
                              <radialGradient id="spinner">
                              <stop offset="0%" stop-color="#dee2e6" />
                              <stop offset="100%" stop-color="#adb5bd" />
                              </radialGradient>
                              <filter id="blur" x="-100%" y="-200%" width="400%" height="400%">
                              <feGaussianBlur in="SourceGraphic" stdDeviation="2" />
                              </filter>
                              <circle cx="50" cy="50" r="49" fill="url('#board')" stroke='#ffe69c' stroke-width="1" />
                              <circle cx="50" cy="50" r="36" fill="none" stroke='#212529' stroke-width="12" />
                              <circle cx="50" cy="50" r="36" fill="none" stroke='#fff' stroke-width="10.5" />
                              <g id="rotateMe">
                              <g transform="rotate(85.2 50 50)">
                      
                                  <circle cx="50" cy="50" r="36" fill="none" stroke='#dc3545' stroke-width="10" stroke-dasharray="5.952" />
                                  <circle cx="50" cy="50" r="36" fill="none" stroke='#212529' stroke-width="10" stroke-dasharray="5.952" stroke-dashoffset="5.952" />
                                  <circle cx="50" cy="50" r="36" fill="none" stroke='#198754' stroke-width="10" stroke-dasharray="5.952 260 5.952" />
                                  <circle cx="50" cy="50" r="36" fill="none" stroke='#198754' stroke-width="10" stroke-dasharray="5.952 260 5.952" transform="rotate(180 50 50)" />
                                  <circle cx="50" cy="50" r="22" fill="#d63384" />
                                  <g>
                                  <rect fill="#212529" height="4" width="30" x="35" y="48" rx="2" filter="url(#blur)" />
                                  <rect fill="#212529" height="30" width="4" x="48" y="35" rx="2" filter="url(#blur)" />
                                  <rect fill="url('#spinner')" height="4" width="30" x="35" y="48" rx="2" />
                                  <rect fill="url('#spinner')" height="30" width="4" x="48" y="35" rx="2" />
                                  <circle cx="50" cy="50" r="4" fill="#212529" filter="url(#blur)" />
                                  <circle cx="50" cy="50" r="4" fill="url('#spinner')" />
                                  </g>
                                  <circle cx="50" cy="50" r="35" fill="none" stroke='#212529' stroke-width="0.5" />
                                  <circle cx="50" cy="50" r="35" fill="none" stroke='#fff' stroke-width="0.4" />
                                  <text id="r" x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" class="moneyDot">17</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(9.474 50 50)">5</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(18.947 50 50)">22</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(28.421 50 50)">34</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(37.895 50 50)">15</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(47.368 50 50)">3</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(56.842 50 50)">24</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(66.316 50 50)">36</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(75.789 50 50)">13</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(85.263 50 50)">1</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(94.737 50 50)">00</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(104.211 50 50)">27</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(113.684 50 50)">10</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(123.158 50 50)">25</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(132.632 50 50)">29</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(142.105 50 50)">12</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(151.579 50 50)">8</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(161.053 50 50)">19</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(170.526 50 50)">31</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(180.000 50 50)">18</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(189.474 50 50)">6</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(198.947 50 50)">21</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(208.421 50 50)">33</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(217.895 50 50)">16</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(227.368 50 50)">4</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(236.842 50 50)">23</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(246.316 50 50)">35</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(255.789 50 50)">14</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(265.263 50 50)">2</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(274.737 50 50)">0</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(284.211 50 50)">28</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(293.684 50 50)">9</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(303.158 50 50)">26</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(312.632 50 50)">30</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(322.105 50 50)">11</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(331.579 50 50)">7</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(341.053 50 50)">20</text>
                                  <text x="50" y="89" text-anchor="middle" dominant-baseline="middle" font-size="6" fill="#fff" font-weight="900" stroke="#212529" stroke-width="0.1" textLength="4" lengthAdjust="spacingAndGlyphs" transform="rotate(350.526 50 50)">32</text>
                              </g>
                              <animateTransform attributeName="transform" attributeType="XML" type="rotate" values="0 50 50; -360 50 50" dur="10s" begin="0s" repeatCount="indefinite" />
                              <g>
                                  <circle cx="50" cy="5" r="2" fill="url('#spinner')" stroke="rgba(0,0,0,0.3)" stroke-width="0.2">
                                  <animate class="ball" attributeName="cy" values="5; 17" dur="6s" begin="indefinite" fill="freeze" keyTimes="0;1" keySplines="0.76 0.05 0.98 0.03" calcMode="spline" />
                                  <animate class="ball" attributeName="r" values="2;1.8" dur="6s" begin="indefinite" fill="freeze" />
                                  </circle>
                      
                                  <animateTransform class="ball ballAnim" attributeName="transform" attributeType="XML" type="rotate" values="0 50 50; 1800 50 50" dur="6s" begin="indefinite" fill="freeze" keyTimes="0;1" keySplines="0.05 0.97 0.89 0.98" calcMode="spline" />
                              </g>
                              </g>
                              <circle cx="50" cy="50" r="3.5" fill="#6610f2" />
                              <text id="win" class="winner" font-size="6" x="50" y="50.5" textLength="5" lengthAdjust="spacingAndGlyphs" fill="#ffc107" stroke="#fff" stroke-width="0.05" font-weight="900" text-anchor="middle" dominant-baseline="middle" font-size="6"></text>
                              <use href="#win" transform="translate(40 40)" />
                              <use href="#win" transform="translate(-40 40)" />
                              <use href="#win" transform="translate(-40 -40)" />
                              <use href="#win" transform="translate(40 -40)" />
                              <path id="path" d="M 30.2 69.8 A 28 28 0 0 0 69.8 69.8" fill="none" />
                      
                          <text font-size="7" fill="#6610f2" textLength="43.9885" lengthAdjust="spacingAndGlyphs">
                          <textPath id="winnerMsg" href="#path" startOffset="0" side="right">
                          </textPath>
                              </text>
                          </svg>
                          </div>
                          <div class="box2">
                          <svg viewBox="-1 0 142 51" class="betPlacement">
                              <g class="betBackgrounds">
                              <g id="rd">
                                  <circle id="rc" cx="15" cy="5.5" r="4" />
                                  <use href="#rc" transform="translate(0 0)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(0 10)" fill="#212529" />
                                  <use href="#rc" transform="translate(0 20)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(10 0)" fill="#212529" />
                                  <use href="#rc" transform="translate(10 10)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(10 20)" fill="#212529" />
                                  <use href="#rc" transform="translate(20 0)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(20 10)" fill="#212529" />
                                  <use href="#rc" transform="translate(20 20)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(30 0)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(30 10)" fill="#212529" />
                                  <use href="#rc" transform="translate(30 20)" fill="#212529" />
                                  <use href="#rc" transform="translate(40 0)" fill="#212529" />
                                  <use href="#rc" transform="translate(40 10)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(40 20)" fill="#212529" />
                                  <use href="#rc" transform="translate(50 0)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(50 10)" fill="#212529" />
                                  <use href="#rc" transform="translate(50 20)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(60 0)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(60 10)" fill="#212529" />
                                  <use href="#rc" transform="translate(60 20)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(70 0)" fill="#212529" />
                                  <use href="#rc" transform="translate(70 10)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(70 20)" fill="#212529" />
                                  <use href="#rc" transform="translate(80 0)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(80 10)" fill="#212529" />
                                  <use href="#rc" transform="translate(80 20)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(90 0)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(90 10)" fill="#212529" />
                                  <use href="#rc" transform="translate(90 20)" fill="#212529" />
                                  <use href="#rc" transform="translate(100 0)" fill="#212529" />
                                  <use href="#rc" transform="translate(100 10)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(100 20)" fill="#212529" />
                                  <use href="#rc" transform="translate(110 0)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(110 10)" fill="#212529" />
                                  <use href="#rc" transform="translate(110 20)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(45 40)" fill="#dc3545" />
                                  <use href="#rc" transform="translate(65 40)" fill="#212529" />
                              </g>
                              </g>
                              <g dominant-baseline="middle" text-anchor="middle" font-size="6" font-weight="900">
                              <g transform="translate(0 0.5)">
                                  <g class="placeBet">
                                  <rect x="10" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="15" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="4">3</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="20" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="25" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="4">6</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="30" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="35" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="4">9</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="40" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="45" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">12</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="50" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="55" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">15</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="60" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="65" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">18</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="70" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="75" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">21</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="80" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="85" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">24</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="90" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="95" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">27</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="100" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="105" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">30</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="110" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="115" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">33</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="120" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="125" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">36</text>
                                  </g>
                              </g>
                              <g transform="translate(0 10.5)">
                                  <g class="placeBet">
                                  <rect x="10" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="15" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="4">2</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="20" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="25" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="4">5</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="30" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="35" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="4">8</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="40" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="45" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">11</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="50" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="55" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">14</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="60" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="65" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">17</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="70" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="75" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">20</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="80" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="85" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">23</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="90" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="95" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">26</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="100" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="105" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">29</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="110" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="115" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">32</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="120" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="125" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">35</text>
                                  </g>
                              </g>
                              <g transform="translate(0 20.5)">
                                  <g class="placeBet">
                                  <rect x="10" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="15" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="4">1</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="20" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="25" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="4">4</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="30" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="35" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="4">7</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="40" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="45" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">10</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="50" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="55" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">13</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="60" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="65" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">16</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="70" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="75" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">19</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="80" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="85" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">22</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="90" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="95" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">25</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="100" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="105" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">28</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="110" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="115" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">31</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect x="120" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="125" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="6" lengthAdjust="spacingAndGlyphs">34</text>
                                  </g>
                              </g>
                              <g transform="translate(0 30.5)">
                                  <g class="placeBet firstThird">
                                  <rect x="10" height="10" width="40" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="30" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="12" lengthAdjust="spacingAndGlyphs">1st 12</text>
                                  </g>
                                  <g class="placeBet secondThird">
                                  <rect x="50" height="10" width="40" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="70" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="12" lengthAdjust="spacingAndGlyphs">2nd 12</text>
                                  </g>
                                  <g class="placeBet lastThird">
                                  <rect x="90" height="10" width="40" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="110" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="12" lengthAdjust="spacingAndGlyphs">3rd 12</text>
                                  </g>
                              </g>
                              <g transform="translate(0 40.5)">
                                  <g class="placeBet firstHalf">
                                  <rect x="10" height="10" width="20" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="20" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="14" lengthAdjust="spacingAndGlyphs">1 to 18</text>
                                  </g>
                                  <g class="placeBet even">
                                  <rect x="30" height="10" width="20" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="40" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="12" lengthAdjust="spacingAndGlyphs">EVEN</text>
                                  </g>
                                  <g class="placeBet red">
                                  <rect x="50" height="10" width="20" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="60" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="10" lengthAdjust="spacingAndGlyphs">RED</text>
                                  </g>
                                  <g class="placeBet black">
                                  <rect x="70" height="10" width="20" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="80" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="14" lengthAdjust="spacingAndGlyphs">BLACK</text>
                                  </g>
                                  <g class="placeBet odd">
                                  <rect x="90" height="10" width="20" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="100" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="10" lengthAdjust="spacingAndGlyphs">ODD</text>
                                  </g>
                                  <g class="placeBet secondHalf">
                                  <rect x="110" height="10" width="20" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text x="120" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="14" lengthAdjust="spacingAndGlyphs">19 to 36</text>
                                  </g>
                              </g>
                              <g>
                                  <g class="placeBet">
                                  <rect x="0" y="0.5" height="15" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text transform="rotate(-90 10 10)" x="12" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="10" lengthAdjust="spacingAndGlyphs">00</text>
                                  </g>
                                  <g class="placeBet">
                                  <rect y="15.5" height="15" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text transform="rotate(-90 10 10)" x="-2.5" y="5.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="5" lengthAdjust="spacingAndGlyphs">0</text>
                                  </g>
                              </g>
                              <g class="two2oneColumns">
                                  <g class="placeBet two2one">
                                  <rect x="130" y="0.5" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text transform="rotate(-90 10 10)" x="14.5" y="135.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="7" lengthAdjust="spacingAndGlyphs">2 to 1</text>
                                  </g>
                                  <g class="placeBet two2one">
                                  <rect x="130" y="10.5" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text transform="rotate(-90 10 10)" x="4.5" y="135.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="7" lengthAdjust="spacingAndGlyphs">2 to 1</text>
                                  </g>
                                  <g class="placeBet two2one">
                                  <rect x="130" y="20.5" height="10" width="10" fill="rgba(0,0,0,0)" stroke="#fff" stroke-width="0.5" />
                                  <text transform="rotate(-90 10 10)" x="-5.5" y="135.5" fill="#fff" stroke="#212529" stroke-width="0.1" textLength="7" lengthAdjust="spacingAndGlyphs">2 to 1</text>
                                  </g>
                              </g>
                              </g>
                          </svg>
                          </div>
                          <div class="winners">
                              <button class="roll" title="Spin the wheel!"><span>ROLL</span></button>
                              <div class="total_money">
                                  <div class="money_title">Total Money: </div>
                                  <div class="money_info"> <span class="money">100</span>
                                  <span class="confetti"></span></div>
                              </div>
                              <span class="winner">36</span>
                              <span class="winner2">Take a Spin!</span>
                          </div>
                  </div>
                  </div>
                      <div>
                      </div>
                      <div class="modal-footer">
                      <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
                      <button type="button" class="btn btn-primary">Save changes</button>
                  </div>
              </div>
          </div>
      </div>
  </div>
  </div>
      `;
  
      const rouletteElement = document.createElement('div');
  rouletteElement.classList.add('col-12', 'col-md-3');
  rouletteElement.innerHTML = rouletteHTML;

  const roll = rouletteElement.querySelector(".roll");
  const wheel = rouletteElement.querySelector("#rouletteWheel");

  //document.body.appendChild(rouletteElement);
  rouletteElement.querySelector('#playBtnRoulette').addEventListener('click', () => loadRouletteScripts());

  return rouletteElement;
}
  
  export function setupRoulette(rouletteElement) {
    // console.log("setupRoulette");
    const ballAnim = rouletteElement.querySelector(".ballAnim");
    spinWheel(ballAnim);
        let nums = ["00", 27,10,25,29,12,8,19,31,18,6,21,33,16,4,23,35,14,2,0,28,9,26,30,11,7,20,32,17,5,22,34,15,3,24,36,13,1];
        let two2oneNums = [
          [3,6,9,12,15,18,21,24,27,30,33,36],
          [2,5,8,11,14,17,20,23,26,29,32,35],
          [1,4,7,10,13,16,19,22,25,28,31,34]
        ];
        let thirdsNums = [
          [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
          [13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24],
          [25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36]
        ];
        let redNums = [1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36];
        let blackNums = [2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35];
        let oddNums = [1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35];
        let evenNums = [2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36];
        let firstHalfNums = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18];
        let secondHalfNums = [19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36];
        let moneyWon = 0;
        const roll = rouletteElement.querySelector(".roll");
        const wheel = rouletteElement.querySelector("#rouletteWheel");
        const evenBtn = rouletteElement.querySelector(".even");
        const oddBtn = rouletteElement.querySelector(".odd");
        const blackBtn = rouletteElement.querySelector(".black");
        const redBtn = rouletteElement.querySelector(".red");
        const firstHalf = rouletteElement.querySelector(".firstHalf");
        const secondHalf = rouletteElement.querySelector(".secondHalf");
        const firstThird = rouletteElement.querySelector(".firstThird");
        const secondThird = rouletteElement.querySelector(".secondThird");
        const lastThird = rouletteElement.querySelector(".lastThird");
        //const ballAnim = rouletteElement.querySelector(".ballAnim");
        const balls = rouletteElement.querySelectorAll(".ball");
        const betBtnsSVG = rouletteElement.querySelectorAll(".placeBet");
        const two2one = rouletteElement.querySelectorAll(".two2one");
        
        let totalMoney = 100;
        let oldMoney = 0;
        let lostWon = 0;
        
        
        const randInt = (min, max) => {
          return Math.floor(Math.random() * (max - min + 1)) + min;
        };
        
        betBtnsSVG.forEach((btn) => {
          btn.addEventListener("click", (evt) => {
            btn.classList.toggle("active");
          });
        });
        
        
        function updateMoney() {
          rouletteElement.querySelector(".money").innerHTML = totalMoney;
        }
        
        function win() {
          document.querySelector("#winnerMsg").textContent = `Winner!: +${moneyWon}!`;
          // confetti!
          confetti(rouletteElement.querySelector(".confetti"), { spread: window.innerWidth });
        }
        
        function lose() {
            lostWon = oldMoney - totalMoney;
            rouletteElement.querySelector("#winnerMsg").textContent = `House wins, you lost ${lostWon}!`;
        }
        
        if (roll) {
          roll.addEventListener("click", spinWheel);
        }
      
        if (wheel) {
          wheel.addEventListener("click", spinWheel);
        }
      }

      export async function runRoulette() {
        const rouletteElement = await renderRoulette();
        /* setupRoulette(rouletteElement); */
      
/*         document.addEventListener('DOMContentLoaded', (event) => {
          console.error("DOMContentLoaded");
          setupRoulette(rouletteElement);
        }); */
      } 
      function loadRouletteScripts() {
        const scriptRoulette = document.createElement('script');
        scriptRoulette.type = 'module';
        scriptRoulette.src = '../rouletteTool.js';  // Assurez-vous que le chemin vers le script est correct
        scriptRoulette.setAttribute('data-roulette', 'dynamic');  // Marqueur pour identifier les scripts chargés dynamiquement
        document.body.appendChild(scriptRoulette);
    }
      
  