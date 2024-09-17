import { getCookie, getProfilePicture, loadUserProfile } from "./userManager.js";
import { appState } from "./stateManager.js";
import { createPhotoComponent, createButtonComponent, createSmallButtonComponent, createPhotoComponentUrl } from "./globalComponent.js";
import { loadLanguage } from "./languageManager.js";

let isLoadingFriendsList = false;

export async function showFriendsList() {
  // getFriendRequestList();
  // if (isLoadingFriendsList) {
  //   return;
  // }
  // isLoadingFriendsList = true;
      
  const users = appState.users;
  const modalBody = document.querySelector('#friendList .modal-body');
  const table = document.createElement('table');
  while (modalBody.firstChild) {
    modalBody.removeChild(modalBody.firstChild);
  }
  table.className = 'userlist-table';
  loadUserProfile();
// Afficher les amis
for (const friendId of appState.userProfile.friendlist) {
  const friend = users.find(user => user.id === friendId);
  if (friend) {
    const friendProfile = appState.usersProfile.find(profile => profile.user === friend.id);

    // Créer un row supplémentaire pour le profil
    const profileRow = document.createElement('tr');
    profileRow.style.display = 'none';
    profileRow.className = "profile-row";
    const profileUsername = document.createElement('td');
    profileUsername.textContent = friend.username;
    profileRow.appendChild(profileUsername);
    const profileFirstName = document.createElement('td');
    profileFirstName.textContent = friend.first_name;
    profileRow.appendChild(profileFirstName);
    const profileLastName = document.createElement('td');
    profileLastName.textContent = friend.last_name;
    profileRow.appendChild(profileLastName);
    const data = await getFriendHistory(friend.id);



    // Si game_1, game_2, ou game_3 ne sont pas null, créer une nouvelle ligne pour chaque jeu
    const games = ['game_1', 'game_2', 'game_3','game_4', 'game_5', 'game_6','game_7', 'game_8', 'game_9', 'game_10']
    .map(gameKey => data.message[gameKey])
    .filter(game => game !== "NULL");
  
  if (games.length === 0) {
    const noGamesText = document.createElement('p');
    noGamesText.setAttribute('data-lang-key', 'noGamePlayed');
    noGamesText.textContent = "Aucun jeu joué";
    profileRow.appendChild(noGamesText);
  } else {
    // Ajouter des titres de colonnes pour l'historique des matchs
    const gameHeaderRow = document.createElement('tr');
    ['ID du jeu', 'Date du jeu', 'Score', 'Adversaire', 'Résultat'].forEach((header, index) => {
    const th = document.createElement('th');
    th.setAttribute('data-lang-key', `headerUserHistory${index}`);
          
    const h6 = document.createElement('h6');
    h6.textContent = header;
    th.appendChild(h6);
          
    gameHeaderRow.appendChild(th);
    });
    profileRow.appendChild(gameHeaderRow);
    games.forEach(game => {
      const gameRow = document.createElement('tr');
      gameRow.style.display = 'none';
      gameRow.className = 'gameRow';
  
      const gameId = document.createElement('td');
      gameId.textContent = game.id;
      gameRow.appendChild(gameId);

      const gameDate = document.createElement('td');
      gameDate.textContent = game.date;
      gameRow.appendChild(gameDate);
  
      const gameScore = document.createElement('td');
      gameScore.textContent = `Score: ${game.p1_score} - ${game.p2_score}`;
      gameRow.appendChild(gameScore);
  
      // Trouver l'adversaire
      const opponentId = game.p1_id === friend.id ? game.p2_id : game.p1_id;
      const opponent = users.find(user => user.id === opponentId);
      const opponentUsername = document.createElement('td');
      opponentUsername.textContent = opponent ? opponent.username : 'Inconnu';
      gameRow.appendChild(opponentUsername);
  
      // Indiquer si le match a été gagné ou perdu
      const gameResult = document.createElement('td');
      let isWinner;
      if (appState.userId == game.winner_id)
      {
        isWinner = false;
      }
      else
      {
        isWinner = true;
      }
      gameResult.setAttribute('data-lang-key', isWinner ? 'win' : 'lost');
      gameResult.textContent = isWinner ? 'win' : 'lost';
      gameRow.style.backgroundColor = isWinner ? 'green' : 'red';
      gameRow.appendChild(gameResult);
  
      // Ajouter la ligne de jeu à profileRow
      profileRow.appendChild(gameRow);
    });
  }

    await addRow(friend, friendProfile, table, 'Voir le profil', null, null, profileRow);
    table.appendChild(profileRow);
  }
  // isLoadingFriendsList = false;
}

  // Afficher les demandes d'amis
  const requests = await getFriendRequestList();
  // table.remove();

  await requests.forEach(async request => {
    if (request.to_user === appState.userId) {
        const fromUser = users.find(user => user.id === request.from_user);
        if (fromUser) {
            const fromUserProfile = appState.usersProfile.find(profile => profile.user === fromUser.id);
            // Vérifier si l'utilisateur est déjà un ami
            const isFriend = appState.userProfile.friendlist.includes(fromUser.id);
            if (isFriend) {
              // Créer un row supplémentaire pour le profil
              const profileRow = document.createElement('tr');
              profileRow.style.display = 'none';
              const profileUsername = document.createElement('td');
              profileUsername.textContent = fromUser.username;
              profileRow.appendChild(profileUsername);
              const profileFirstName = document.createElement('td');
              profileFirstName.textContent = fromUser.first_name;
              profileRow.appendChild(profileFirstName);
              const profileLastName = document.createElement('td');
              profileLastName.textContent = fromUser.last_name;
              profileRow.appendChild(profileLastName);
              const profileEmail = document.createElement('td');
              profileEmail.textContent = fromUser.email;
              profileRow.appendChild(profileEmail);
            
              // Ajouter le bouton "Voir le profil" si l'utilisateur est déjà un ami
              await addRow(fromUser, fromUserProfile, table, 'Voir le profil', null, request.id, profileRow);
              await table.appendChild(profileRow);
            } else {
                // Sinon, ajouter les boutons "Accepter" et "Refuser"
                await addRow(fromUser, fromUserProfile, table, 'Accepter', 'Refuser', request.id);
            }
        }
    }
  });
  modalBody.appendChild(table);
  loadLanguage(appState.language);
}

async function addRow(user, userProfile, table, buttonText1, buttonText2, requestId, profileRow) {
  const row = document.createElement('tr');
  const nameCell = document.createElement('td');
  const photoCell = document.createElement('td');
  const buttonCell1 = document.createElement('td');
  const buttonCell2 = buttonText2 ? document.createElement('td') : null;
  const profilePicture = await getProfilePicture(user.id);
  const photoComponent = await createPhotoComponentUrl(profilePicture, userProfile.winrate);
  const onlineStatusCell = document.createElement('td');
  if (userProfile.online) {
    if (userProfile.in_game) {
      onlineStatusCell.textContent = 'in game';
      onlineStatusCell.dataset.langKey = 'inGame';
      onlineStatusCell.style.backgroundColor = 'orange';
    } else {
      onlineStatusCell.textContent = 'online';
      onlineStatusCell.dataset.langKey = 'online';
      onlineStatusCell.style.backgroundColor = 'green';
    }
  } else {
    onlineStatusCell.textContent = 'offline';
    onlineStatusCell.dataset.langKey = 'offline';
    onlineStatusCell.style.backgroundColor = 'red';
  }
  
  let buttonComponent1;
  if (buttonText1) {
    buttonComponent1 = createSmallButtonComponent(buttonText1, 'viewProfileButton', buttonText1, (event) => {
      if (buttonText1 === 'Accepter') {
        acceptFriendRequest(user.id, requestId);
        buttonCell1.innerHTML = '';
        if (buttonCell2) {
          row.removeChild(buttonCell2);
        }
      } else if (buttonText1 === 'Voir le profil') {
        profileRow.style.display = '';
        Array.from(profileRow.children).forEach(child => {
          if (child.tagName === 'TR') {
            child.style.display = '';
          }
        });
      } else {
        profileRow.style.display = profileRow.style.display === 'none' ? '' : 'none';
      }
    });
  }

  const buttonComponent2 = buttonText2 ? createSmallButtonComponent(buttonText2, 'denyFriendButton', buttonText2, (event) => {
      denyFriendRequest(appState.userId, requestId);
      table.removeChild(row);
  }) : null;

  nameCell.textContent = user.username;
  photoCell.appendChild(photoComponent);
  if (buttonComponent1) {
    buttonCell1.appendChild(buttonComponent1);
  }
  if (buttonCell2) {
      buttonCell2.appendChild(buttonComponent2);
  }

  row.appendChild(photoCell);
  row.appendChild(nameCell);
  row.appendChild(onlineStatusCell);
  row.appendChild(buttonCell1);
  if (buttonCell2) {
      row.appendChild(buttonCell2);
  }
  table.appendChild(row);
  loadLanguage(appState.language);
}

export function sendFriendRequest(fromId, toUsername) {
    const data = { username: fromId, password: toUsername };
    const csrfToken = getCookie('csrftoken');
    fetch('/api/send_friend', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'X-CSRFToken': csrfToken,
      },
      body: JSON.stringify(data),
    })
    .then(response => response.json())
    .then(data => console.log(data))
    .catch((error) => {
      console.error('Error:', error);
    });
  }

  export function acceptFriendRequest(userId, requestId) {
    const data = { username: userId, password: requestId };
    const csrfToken = getCookie('csrftoken');
    fetch('/api/accept_friend', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'X-CSRFToken': csrfToken,
      },
      body: JSON.stringify(data),
    })
    .then(response => response.json())
    .then(data => console.log(data))
    .catch((error) => {
      console.error('Error:', error);
    });
  }

  export function denyFriendRequest(userId, requestId) {
    const data = { username: userId, password: requestId };
    const csrfToken = getCookie('csrftoken');
    fetch('/api/deny_friend', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'X-CSRFToken': csrfToken,
      },
      body: JSON.stringify(data),
    })
    .then(response => response.json())
    .then(data => console.log(data))
    .catch((error) => {
      console.error('Error:', error);
    });
  }

  export function getFriendRequestList() {
    return fetch('/api/friendlist', {
      method: 'GET',
    })
    .then(response => response.json())
    .catch((error) => {
      console.error('Error:', error);
    });
}

export function getFriendHistory(friendId){
  return fetch(`api/get_friend/${friendId}`)
    .then(response => response.json())
    .then(data => {
      return data;
    })
    .catch(error => {
      console.error('Erreur:', error);
    });
}

export function updateFriendRequestsNotification() {
    getFriendRequestList().then(requests => {
        const pendingRequests = requests.filter(request => request.to_user === appState.userId);
        const notificationBubble = document.querySelector('.notification-bubble');
        if (pendingRequests.length > 0) {
            notificationBubble.textContent = pendingRequests.length;
            notificationBubble.style.display = 'block';
        } else {
            notificationBubble.style.display = 'none';
        }
        return pendingRequests;
    });
}

