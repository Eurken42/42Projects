export function renderUserMenu(user) {
	get
    const userMenuHTML = `
        <div id="user-menu" class="user-menu-hidden">
            <div class="user-menu-img">
                <img id="profile-picture" alt="User Image">
            </div>
            <div class="user-menu-info">
                <li class="active">
                    <a href="#"><span class="fa fa-close"></span></a>
                </li>
                </div>
            </div>
        </div>
    `;
    document.body.insertAdjacentHTML('beforeend', userMenuHTML);
}