FROM debian:bullseye

RUN		apt update -y &&\
		apt upgrade -y &&\
		apt install -y nginx
RUN		mkdir -p /etc/nginx/ssl &&\
		apt install -y openssl
RUN		apt install -y vim
RUN		openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key -subj "/C=CH/ST=NE/L=Lausanne/O=42 Lausanne/OU=42/CN=scorreia.42lausanne.ch/UID=scorreia@student.42lausanne.ch"
RUN		mkdir -p /var/www/wordpress
RUN		chown -R www-data:www-data /var/www/wordpress

COPY	conf/nginx.conf /etc/nginx/nginx.conf

EXPOSE 443

CMD [ "nginx", "-g", "daemon off;" ]