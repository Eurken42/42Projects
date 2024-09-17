FROM    debian:bullseye

RUN		apt update -y &&\
		apt upgrade -y
RUN     apt-get -y install wget
RUN 	apt-get -y install sendmail
RUN     apt-get -y install	php \
							php-fpm \
							php-mysql
RUN     wget https://fr.wordpress.org/wordpress-6.4.3-fr_FR.tar.gz -P /var/www
RUN		cd /var/www && tar -xvzf wordpress-6.4.3-fr_FR.tar.gz && rm wordpress-6.4.3-fr_FR.tar.gz
RUN		chmod u=rwx,g=rx,o=rx /var/www/wordpress

COPY	./conf/php.conf /etc/php/7.4/fpm/pool.d/www.conf

RUN     mkdir -p /run/php
RUN     chmod 755 /run/php

RUN		wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN		chmod +x wp-cli.phar
RUN		mv wp-cli.phar /usr/local/bin/wp

COPY	./tools/wp-conf.sh /etc/wp-conf.sh

RUN		chmod +x /etc/wp-conf.sh

WORKDIR /var/www/wordpress

EXPOSE	9000

CMD		["sh", "/etc/wp-conf.sh"]