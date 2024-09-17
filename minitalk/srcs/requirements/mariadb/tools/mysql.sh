#!/bin/bash
sed -i "s|\${MARIADB_ROOT_USER}|$MARIADB_ROOT_USER|g" /etc/conf.sql
sed -i "s|\${MARIADB_ROOT_PASSWORD}|$MARIADB_ROOT_PASSWORD|g" /etc/conf.sql
sed -i "s|\${MARIADB_USER}|$MARIADB_USER|g" /etc/conf.sql
sed -i "s|\${MARIADB_PASSWORD}|$MARIADB_PASSWORD|g" /etc/conf.sql
mysqld --init-file="/etc/conf.sql"
exec mysqld
