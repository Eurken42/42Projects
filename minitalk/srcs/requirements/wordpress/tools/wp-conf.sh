#!/bin/bash
sleep 15
wp core download --locale=fr_FR --allow-root --force
wp config create --dbname=$MARIADB_DATABASENAME --dbuser=$MARIADB_ROOT_USER --dbpass=$MARIADB_ROOT_PASSWORD --dbhost=$MARIADB_HOSTNAME --allow-root
wp core install --url="scorreia.42lausanne.ch" --title="Wesh la mif" --admin_user=$MARIADB_ROOT_USER --admin_password=$MARIADB_ROOT_PASSWORD --admin_email=$MARIADB_MAIL --allow-root
wp user create $MARIADB_USER $MARIADB_MAIL2 --user_pass=$MARIADB_PASSWORD --allow-root
wp config shuffle-salts --allow-root
php-fpm7.4 -F -R
