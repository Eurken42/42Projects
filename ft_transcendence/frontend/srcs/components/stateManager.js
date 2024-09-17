import { getUser, loadUser, getCurrentUser, loadGameList, logoutUser } from './userManager.js';
import { renderNavbar } from './navbar.js';
import { renderHero } from './hero.js';
import { renderPong } from './pongComponent.js';
import { renderLogin } from './login.js';
import { renderRun } from './runGame.js';
import { LanguageBtn, loadLanguage } from './languageManager.js';
import { createListCardComponent, renderDiv } from './globalComponent.js';
import { showGameList, } from './listComponent.js';

let currentIndex = -1;

// Initialisation de l'état de l'application et du current user
export let appState = {
    currentView: 'login',
    user: null,
    userId: null,
    //liste des users (username, nom, email, etc.)
    users: [],
    //liste userProfile (avec stats, photo de profil, etc.) de tous les users
    usersProfile: [],
    //userProfile (avec stats, photo de profil, etc.) du user
    userProfile: null,
    urlHistory: ['login'],
    renderedComponents: {},
    language: 'fr',
    newViewAdded: false,
    isLogged: false,
    inModalGame: false
};

async function updateGameList() {
    if (appState.currentView == 'game' && appState.inModalGame == false) {
        let text;
        switch (appState.language) {
            case 'fr':
                text = "HISTORIQUE DES PARTIES";
                break;
            case 'de':
                text = "SPIELVERLAUF";
                break;
            case 'us':
                text = "GAME HISTORY";
                break;
            default:
                text = "HISTORIQUE DES PARTIES";
                break;
        }
		// console.log("ton pere la chiennnnnng");
        const game = renderPong();
        const gameListHTML = await showGameList();
        const cardHistory = createListCardComponent('pongPlayed', text, gameListHTML);
        await renderDiv([cardHistory, game], 'row');
    }
    setTimeout(updateGameList, 5000);
}

// Fonction pour changer la vue actuelle de l'application
export function changeView(newView) {
    if (appState.currentView !== newView) {
        appState.currentView = newView;
        }
    appState.newViewAdded = true;
    location.hash = newView;
    sessionStorage.setItem('appState', JSON.stringify(appState));
    if (newView !== 'login') {
        loadUser();
    }
}

// Écouteur d'événement pour changer la vue lorsque l'URL change (rajoute le # à l'URL lorsqu'on change de vue)
window.addEventListener("hashchange", function () {
    const newView = location.hash.substring(1);
    if (appState.currentView !== newView) {
		appState.currentView = newView;
    }
    if (!appState.user && newView !== 'login') {
        window.location.hash = 'login';
        return;
    }
    renderApp();
});

// Fonction pour que l'historique du navigateur fonctionne correctement avec les vues de l'application (popstate se declenche lorsque l'on presse sur precedent)
window.addEventListener("popstate", function () {
    const newView = location.hash.substring(1);
    const newIndex = appState.urlHistory.lastIndexOf(newView);
    if (!appState.user && newView !== 'login') {
        window.location.hash = 'login';
        return;
    }
    if (newView === 'login' && appState.user) {
        const confirmLogout = window.confirm('Si vous revenez à cette page, vous serez déconnecté. Êtes-vous sûr de vouloir continuer ?');
        if (confirmLogout) {
            logoutUser();
        } else {
            history.pushState(null, null, '#' + appState.urlHistory[appState.urlHistory.length - 1]);
        }
    } else if (appState.newViewAdded) {
        appState.currentView = newView;
        if (appState.urlHistory[appState.urlHistory.length - 1] !== newView) {
            appState.urlHistory.push(newView);
        }
        currentIndex++;
        appState.newViewAdded = false;
    } else if (newIndex < currentIndex) {
        appState.currentView = newView;
        if (appState.urlHistory[appState.urlHistory.length - 1] !== newView) {
            appState.urlHistory.push(newView);
        }
        currentIndex++;
    } else {
        appState.urlHistory.pop();
        currentIndex--;
    }
});

window.addEventListener("pushstate", function () {
    const newView = location.hash.substring(1);
    if (appState.currentView !== newView) {
        appState.currentView = newView;
        if (appState.urlHistory[appState.urlHistory.length - 1] !== newView) {
            appState.urlHistory.push(newView);
        }
    }
});

window.addEventListener('beforeunload', () => {
    sessionStorage.setItem('appState', JSON.stringify(appState));
});

export function getCurrentView() {
    return appState.currentView;
}

// Fonction principale pour rendre l'application en fonction de l'état actuel
export async function renderApp() {
    initializeAppState();
    validateCurrentView();
    await renderCurrentView();
}

function initializeAppState() {
    const storedAppState = sessionStorage.getItem('appState');
    if (storedAppState) {
        appState = JSON.parse(storedAppState);
    }
    if (!location.hash || appState.userId == 0) {
        location.hash = '#login';
    }
    appState.renderedComponents = JSON.parse(sessionStorage.getItem('renderedComponents')) || {};
    loadLanguage(appState.language);
    const view = window.location.pathname.substring(1);
    appState.currentView = ['login', 'hero', 'game', 'chat'].includes(view) ? view : 'login';
    appState.currentView = location.hash.substring(1) || 'login';
    document.body.innerHTML = '';
    sessionStorage.setItem('appState', JSON.stringify(appState));
}

function validateCurrentView() {
    const validViews = ['login', 'game', 'hero'];
    if (!validViews.includes(appState.currentView)) {
        document.body.innerHTML =
            '<div class="error-404"><img src="../Design/Mflury404.jpg"><h1 data-lang-key="error-404">Erreur 404 : Page non trouvée</h1><div>';
        throw new Error('Invalid view');
    }
    if (!appState.renderedComponents) {
        appState.renderedComponents = {};
    }
}

async function renderCurrentView() {
    switch (appState.currentView) {
        case 'login':
            appState.urlHistory = ['login'];
            await renderLoginView();
            break;
        default:
            await renderDefaultView();
            break;
    }
}

async function renderLoginView() {
    if (!appState.renderedComponents.login) {
        await LanguageBtn();
        renderLogin();
        appState.renderedComponents.login = true;
    } else {
        await LanguageBtn();
        renderLogin();
    }
}

async function renderDefaultView() {
    if (!appState.user) {
        appState.currentView = 'login';
        await renderLoginView();
    }
    switch (appState.currentView) {
        case 'hero':
            await renderHeroView();
            break;
        case 'game':
            await renderGameView();
            break;
    }
}

async function renderHeroView() {
    if (!document.querySelector('.navbar')) {
        await LanguageBtn();
        await renderHero();
        await renderNavbar(appState);
        appState.renderedComponents.hero = true;
        appState.renderedComponents.navbar = true;
    }
}

async function renderGameView() {
    if (!appState.renderedComponents.game) {
        await LanguageBtn();
        if (!document.querySelector('.navbar')) {
            await renderNavbar(appState);
        }
        const game = await renderPong();
        const game2 = await renderRun();
        const gameListHTML = await showGameList();
        const cardHistory = createListCardComponent('pongPlayed', 'Games', gameListHTML);
        await renderDiv([cardHistory, game], 'row');
        await LanguageBtn();
        appState.renderedComponents.game = true;
        appState.renderedComponents.navbar = true;
    }
    loadLanguage(appState.language);
}

window.addEventListener('beforeunload', function (e) {
    // console.log('***&&&%%%$$$&&***$$$***%^^%');
    logoutUser();
});


renderApp();
updateGameList();