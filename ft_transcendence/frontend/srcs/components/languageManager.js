import { appState, renderApp } from "./stateManager.js";
import { getCookie } from "./login.js";

export function LanguageBtn() {
    const languageBtnHTML = `
    <div class="dropdown dropdown-language">
        <button class="btn btn-secondary dropdown-toggle" type="button" id="languageDropdown" data-bs-toggle="dropdown" aria-expanded="false">
            <i class="flag-icon flag-icon-${appState.language}"></i>
        </button>
        <ul class="dropdown-menu dropdown-menu-lang" aria-labelledby="languageDropdown">
            <li><a class="dropdown-item" data-lang="fr" href="#"><i class="flag-icon flag-icon-fr"></i></a></li>
            <li><a class="dropdown-item" data-lang="us" href="#"><i class="flag-icon flag-icon-us"></i></a></li>
            <li><a class="dropdown-item" data-lang="de" href="#"><i class="flag-icon flag-icon-de"></i></a></li>
        </ul>
    </div>
    `;
    document.body.insertAdjacentHTML('afterbegin', languageBtnHTML);

    const dropdownButton = document.querySelector('#languageDropdown');

    document.querySelectorAll('.dropdown-item').forEach(item => {
        item.addEventListener('click', (event) => {
            event.preventDefault();
            const lang = event.currentTarget.getAttribute('data-lang');
            dropdownButton.innerHTML = event.currentTarget.innerHTML;
            appState.language = lang;
            sessionStorage.setItem('language', lang);
            sessionStorage.setItem('appState', JSON.stringify(appState));
            loadLanguage(appState.language);
            if (appState.user) {
                updateUserLanguageOnServer(lang);
            }
            renderApp();
        });
    });
}

export function loadLanguage(lang) {
    if (!lang) {
        console.error('No language specified');
        return;
    }
    fetch('../json/' + lang + '.json')
        .then(response => response.json())
        .then(data => {
            const elements = document.querySelectorAll('[data-lang-key]');
            elements.forEach(element => {
                const key = element.getAttribute('data-lang-key');
                const translation = data[key];
                if (translation) {
                    element.textContent = translation;
                }
            });
            const dropdownButton = document.querySelector('#languageDropdown');
            if (dropdownButton) {
                const flagIcon = dropdownButton.querySelector('.flag-icon');
                if (flagIcon) {
                    flagIcon.className = '';
                    flagIcon.classList.add('flag-icon', 'flag-icon-' + lang);
                }
            }
        });
}

function updateUserLanguageOnServer(language) {
    let languageMap = {
        'fr': 1,
        'us': 2,
        'de': 3
    };
    let csrfToken = getCookie('csrftoken');
    fetch('api/update_language/' + appState.userId, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'X-CSRFToken': csrfToken,
        },
        body: JSON.stringify({language: languageMap[language]}),
    })
    .then(response => {
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json();
    })
    .catch((error) => {
        console.error('Error:', error);
    });
}