import { changeView, appState} from './stateManager.js';
import { getUser, setProfilePicture, setUsername, logoutUser, getProfilePicture, setAlias, setEmail, setFirstName, setLastName, setPassword } from './userManager.js';
import { createButtonComponent, createPhotoComponent } from './globalComponent.js';
import { showGameList, showUserList } from './listComponent.js';
import { showFriendsList, updateFriendRequestsNotification } from './friendsList.js';
import { loadLanguage } from './languageManager.js';
import{ updateUserOnServer } from './userManager.js';
function escapeHTML(unsafeText) {
  let div = document.createElement('div');
  div.textContent = unsafeText;
  return div.innerHTML;
}
let test = 667;

function encodeImage(file) {
  return new Promise((resolve, reject) => {
      const reader = new FileReader();
      reader.onload = function(event) {
          resolve(event.target.result);
      };
      reader.onerror = reject;

      // Si le fichier n'est pas un Blob, le convertir en Blob
      if (!(file instanceof Blob)) {
          file = new Blob([file]);
      }

      reader.readAsDataURL(file);
  });
}

export async function renderNavbar(user){
  //const user = getUser();
  if (!user) {
    console.error('Aucun utilisateur n\'a été trouvé');
    return;
  }  
  
async function displayUserInfo(user) {
      //let currentUser = user[0];
      const pictureUrl = await getProfilePicture(user.userId);
      const userInfoDiv = document.getElementById('nav-user');
    //   user.profilePicture = getProfilePicture(user.id);
      if (userInfoDiv) {
          userInfoDiv.innerHTML = `
          <div class="nav-user-info d-md-block">
          <h4>${user.user.username}</h4>
          <h6>${user.userProfile.winrate} %</h6>
          </div>
          <div id="user-menu-button" class="nav-user-img d-md-block">
                  <div id="user-menu-button" class="img_cont_nav">
                  <img src="${pictureUrl}" alt="User Image">
                  </div>
          </div>
          `;
      }
  }
  
async  function renderUserMenu(user) {
    const pictureUrl = await getProfilePicture(user.userId);
    const userMenuHTML = `
        <div id="user-menu" class="user-menu-hidden">


        <div class="user-menu-img">
        <img src="${pictureUrl}" alt="User Image">
        <button type="button" class="close close-menu-button" aria-label="Close"> <span aria-hidden="true">&times;</span> </button>
        <button type="button" class="edit edit-menu-button btn btn-primary" aria-label="Edit" data-bs-toggle="modal" data-bs-target="#editPicture"> <span aria-hidden="true">&#9998;</span> </button>
        </div>
            <div class="user-menu-title">
                <h3>${user.user.username}</h3>
                <h4>${user.userProfile.game_won} <span data-lang-key="matchesWon">matchs gagnés</span></h4>
                <h4>${user.userProfile.game_lost} <span data-lang-key="matchesLost">matchs perdus</span></h4>
                <h4>${user.userProfile.winrate} %</h4>
            </div>
            <div class="user-menu-info">
            <button type="button" class="user-menu-li" aria-label="Edit" data-bs-toggle="modal" data-bs-target="#addFriend"> 
                <i class="fas fa-user-plus"></i><h6 data-lang-key='addFriend'>ajouter un ami</h6>
            </button>
            <button id="boutonamis" type="button" class="user-menu-li" aria-label="Edit" data-bs-toggle="modal" data-bs-target="#friendList">
              <i class="fas fa-user-plus"></i>
              <h6 data-lang-key='FriendList'>Liste d'ami</h6>
              <div class="notification-bubble" style="display: none;"></div>
            </button>
            <button type="button" class="user-menu-li" aria-label="Edit" data-bs-toggle="modal" data-bs-target="#editPicture">
                    <i class="fas fa-cog"></i><h6 data-lang-key='setProfile'>Editer le profil</h6>
            </button>
            </div>
            <div class="user-menu-logout">
              <button id="logoutBtn" class="btn btn-logout btn-outline-light btn-lg px-5" data-lang-key='logout'>Déconnexion</button>
            </div>
        </div>

        <!-- Modal set user -->
        <div class="modal fade" id="editPicture" tabindex="-1" role="dialog" aria-labelledby="editPictureLabel" aria-hidden="true">
            <div class="modal-dialog modal-fullscreen" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title" id="editPictureLabel" data-lang-key='editPicture'>changer l'image de profil</h5>
                        <button type="button" class="close" data-bs-dismiss="modal" aria-label="Close">
                            <span aria-hidden="true">&times;</span>
                        </button>
                    </div>
                    <div class="modal-body">
                      <form>
                      <label for="newProfilePicture"  class="text-white" data-lang-key='newPicture'>Nouvelle image</label>
                        <div class="input-group">
                          <input class="form-control" type="file" id="newProfilePicture">
                          <img id="preview" style="display: block;" />
                        </div>
                          <div class="form-group">
                          <label for="formGroupExampleInput"  class="text-white" data-lang-key='newUsername'>Nouveau username</label>
                          <input type="text" class="form-control" id="newUsername" placeholder="Username">
						      <div class="form-group">
							<label for="newAlias" class="text-white" data-lang-key='newAlias'>Nouvel alias</label>
							<input type="text" class="form-control" id="newAlias" placeholder="Alias">
							</div>
							<div class="form-group">
							<label for="newFirstName" class="text-white" data-lang-key='newFirstName'>Nouveau prénom</label>
							<input type="text" class="form-control" id="newFirstName" placeholder="Prénom">
							</div>
							<div class="form-group">
							<label for="newLastName" class="text-white" data-lang-key='newLastName'>Nouveau nom</label>
							<input type="text" class="form-control" id="newLastName" placeholder="Nom">
							</div>
							<div class="form-group">
							<label for="newEmail" class="text-white" data-lang-key='newEmail'>Nouveau email</label>
							<input type="email" class="form-control" id="newEmail" placeholder="Email">
							</div>
								<div class="form-group">
									<label for="newPassword" class="text-white" data-lang-key='newPassword'>Nouveau mot de passe</label>
									<input type="password" class="form-control" id="newPassword" placeholder="Mot de passe">
								</div>
								<div class="form-group">
									<label for="confirmPassword" class="text-white" data-lang-key='confirmPassword'>Confirmer le mot de passe</label>
									<input type="password" class="form-control" id="confirmPassword" placeholder="Confirmer le mot de passe">
								</div>
							</div>
							</form>
							</div>
							
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" data-bs-dismiss="modal" data-lang-key='close'>Close</button>
                        <button id="userSaveChange" type="button" class="btn btn-primary"  data-bs-dismiss="modal" data-lang-key='saveChanges'>Save changes</button>
                    </div>
                </div>
            </div>
        </div>

        <!-- Modal add a friend -->
        <div class="modal fade modal-fullscreen modal-dialog modal-lg" id="addFriend" tabindex="-1" role="dialog" aria-labelledby="addFriendLabel" aria-hidden="true">
            <div class="modal-dialog modal-fullscreen" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title" id="editPictureLabel" data-lang-key='addFriend'>Add a friend</h5>
                        <button type="button" class="close" data-bs-dismiss="modal" aria-label="Close">
                            <span aria-hidden="true">&times;</span>
                        </button>
                    </div>
                    <div class="modal-body text-white">

                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" data-bs-dismiss="modal" data-lang-key='close'>Close</button>
                        <button id="userSaveChange" type="button" class="btn btn-primary"  data-bs-dismiss="modal" data-lang-key='saveChanges'>Save changes</button>
                    </div>
                </div>
            </div>
        </div>
        
        <!-- Modal show friendlist -->
        <div class="modal modal-fullscreen fade modal-dialog modal-lg" id="friendList" tabindex="-1" role="dialog" aria-labelledby="friendListLabel" aria-hidden="true">
            <div class="modal-dialog modal-fullscreen" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title" id="editPictureLabel" data-lang-key='FriendList'>FriendList</h5>
                        <button type="button" class="close" data-bs-dismiss="modal" aria-label="Close">
                            <span aria-hidden="true">&times;</span>
                        </button>
                    </div>
                    <div class="modal-body text-white">

                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" data-bs-dismiss="modal" data-lang-key='close'>Close</button>
                        <button id="userSaveChange" type="button" class="btn btn-primary"  data-bs-dismiss="modal" data-lang-key='saveChanges'>Save changes</button>
                    </div>
                </div>
            </div>
        </div>
    `;      
    document.body.insertAdjacentHTML('beforeend', userMenuHTML);
}  

    async function insertNavbarHTML() {
        const navbarHTML = `
    <nav class="navbar navbar-expand-lg bg-body-tertiary">
      <div class="container-fluid">
      <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarTogglerDemo02" aria-controls="navbarTogglerDemo02" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon fas fa-bars"></span>
      </button>
    <div class="collapse navbar-collapse" id="navbarTogglerDemo02">
      <ul class="nav-div-btn navbar-nav me-auto mb-2 mb-lg-0">
        <li class="nav-glowing-btn">
          <button id='navChatBtn' class='glowing-btn'><span class='glowing-txt' data-lang-key='home'>HOME</span></button>
        </li>
        <li class="nav-glowing-btn">
          <button id='navGameBtn' class='glowing-btn'><span class='glowing-txt' data-lang-key='game'>GAME</span></button>
        </li>
      </ul>
    </div>
    <div class="collapse navbar-collapse navbar-logo" href="logoProject"><img id="logo-img" src="Design/LogoTranscendance3.png" alt=""></div>
      <div class="nav-user" id="nav-user">

        </div>
      </div>
    </div>
  </nav>
    `;
    document.body.insertAdjacentHTML('afterbegin', navbarHTML);
  }
  insertNavbarHTML();
  await displayUserInfo(user);
  await renderUserMenu(user);
  await setupButtonListener();
  await loadLanguage(appState.language);
//   showUserList();
  // await showFriendsList();
}

function    setupButtonListener() {
  document.getElementById('navChatBtn').addEventListener('click', function() {
      changeView('hero');
  });
  
  document.getElementById('navGameBtn').addEventListener('click', function() {
      changeView('game');
  });

  document.getElementById('user-menu-button').addEventListener('click', async function() {
	
    try {
      await updateFriendRequestsNotification();
      // await showFriendsList();
      await showUserList();
      loadLanguage(appState.language);
    } catch (error) {
		console.error('An error occurred:', error);
    }
	
    const userMenu = document.getElementById('user-menu');
    if (userMenu) {
		userMenu.style.display = 'block';
    } else {
		console.error('No element with ID "user-menu" found');
    }
});

document.getElementById('boutonamis').addEventListener('click', async function() {
  test *= -1;
  try {
    if (test > 0)
    {
      await showFriendsList();
      test *= -1;
      changeView(appState.currentView);
    }
  } catch (error) {
  console.error('An error occurred:', error);
  }
});

document.getElementById('logoutBtn').addEventListener('click', logoutUser);

document.querySelector('.close-menu-button').addEventListener('click', function() {
	document.getElementById('user-menu').style.display = 'none';
});

document.querySelector('input[type=file]').addEventListener('change', function(event) {
	const file = event.target.files[0];
    encodeImage(file).then(function(dataUrl) {
		document.querySelector('img').src = dataUrl;
    });
});

document.querySelector('#newProfilePicture').addEventListener('change', function() {
	var file = this.files[0];
    if (file) {
		setProfilePicture(file);
        var reader = new FileReader();
        reader.onload = function(e) {
			var preview = document.querySelector('#preview');
            preview.src = e.target.result;
            preview.style.display = 'block';
        };
        reader.readAsDataURL(file);
    }
});

  function updateUserInfoInNavbar(user) {
    const userInfoDiv = document.getElementById('nav-user');
    if (userInfoDiv) {
        let escapedUsername = escapeHTML(user.username);
        userInfoDiv.innerHTML = `
        <div class="nav-user-info">
        <h4>${user.user.username}</h4>
        <h6>${user.userProfile.winrate} % </h6>
        </div>
        <div id="user-menu-button" class="nav-user-img">
                <div id="user-menu-button-inner" class="img_cont_nav">
                <img id="profile-picture" alt="User Image">
                </div>
        </div>
        `;

        document.getElementById('user-menu-button-inner').addEventListener('click', function() {
            const userMenu = document.getElementById('user-menu');
            if (userMenu.style.display === 'block') {
                userMenu.style.display = 'none';
            } else {
              getProfilePicture(appState.userId);
                userMenu.style.display = 'block';
            }
        });
    }
}

document.querySelector('#userSaveChange').addEventListener('click', function() {
  // console.log('Click on save changes')
  const newProfilePictureFile = document.querySelector('#newProfilePicture').files[0];
  let newUsername = document.querySelector('#newUsername').value;
  let newAlias = document.querySelector('#newAlias').value;
  let newFirstName = document.querySelector('#newFirstName').value;
  let newLastName = document.querySelector('#newLastName').value;
  let newEmail = document.querySelector('#newEmail').value;
  let newPassword = document.querySelector('#newPassword').value;
  let confirmPassword = document.querySelector('#confirmPassword').value;
  if (newProfilePictureFile) {
    setProfilePicture(newProfilePictureFile);
    const displayedProfilePicture = document.querySelector('.user-menu-img img');
    displayedProfilePicture.src = URL.createObjectURL(newProfilePictureFile);
    updateUserInfoInNavbar(appState);
  }
  // if (newUsername) {
  //   let escapedUsername = escapeHTML(newUsername);
  //   setUsername(escapedUsername);
  //   const displayedUsername = document.querySelector('.user-menu-title');
  //   displayedUsername.textContent = escapedUsername;
  //   updateUserInfoInNavbar(appState);
  // }

	function updateUserInfo(field, value) {
    value = value ? escapeHTML(value) : '';

    switch(field) {
      case 'email':
        setEmail(value);
        break;
      case 'username':
        setUsername(value);
        break;
      case 'first_name':
        setFirstName(value);
        break;
      case 'last_name':
        setLastName(value);
        break;
      case 'alias':
        setAlias(value);
        break;
      case 'password':
        setPassword(value);
        break;
      default:
        console.error('Invalid field');
    }
	}

	if (newPassword === confirmPassword) {
		updateUserInfo('password', confirmPassword);
	}
	updateUserInfo('email', newEmail);
	updateUserInfo('first_name', newFirstName);
	updateUserInfo('last_name', newLastName);
	updateUserInfo('username', newUsername);
	updateUserInfo('alias', newAlias);
  updateUserOnServer(appState);
});
 }

// window.onload = function() {
//   updateFriendRequestsNotification();
// };

