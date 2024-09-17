# CLI

## Install
Cette application CLI peut etre compilée depuis les sources ou dockerizée.

### Docker
Décommenter la partie CLI dans le docker-compose a la racine du projet [ft_transcendence](/)
Pour se connecter au container et lancer l'application
```bash
make cli
```

### From sources
Pour compiler l'application depuis les sources, il faut avoir [cargo](https://doc.rust-lang.org/cargo/getting-started/installation.html) installé.
* Se rendre a la racine du dossier [cli](/cli)
* Lancer la commande
```bash
cargo install --path .
```
* Le binaire sera automatiquement installer dans */usr/local/cargo/bin/cli* et il sera possible de le lancer directement avec la commande
```bash
cli
```

## Lancement
Lors du lancement de l'application, l'adresse du serveur nous est demandée. Aucun port n'est requis.
Il est important de noter que si l'application est dockerizée sur le même ordinateur que le serveur, l'adresse du serveur sera **nginx** (l'IP du poste fonctionnerai aussi, mais pas *localhost*)

## Utilisation
Une fois le serveur entré, l'app demande un user + password. Il n'est **PAS** possible de créer un user ou de le modifier depuis le CLI.

### Menu
Il existe 3 menu:

**->** le menu principal (apparaît après la connexion de l'utilisateur)

**->** le menu Pong (permet de rejoindre le matchmaking, créer une partie privée ou d'en rejoindre une)

**->** le menu Tournament (permet de rejoindre ou de créer un tournoi)
	
### Jouer
* W - Monter le paddle
* S - Descendre le paddle

> [!TIP]
> Il est vivement recommandé de réduire au minimum le delai entre la répetition des touches du clavier pour une meilleur expérience utilisateur lors des parties
> Il est déconseillé de quitter l'application en fermant le terminal (ou alt+f4) car votre utilisateur ne sera jamais déconnecté (impossible de s'y reconnecter donc). Il est néanmoins possible de quitter à tout moment avec ctrl+c

## Uninstall
* Lancer la commande
```bash
cargo uninstall cli
```