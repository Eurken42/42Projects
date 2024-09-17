FROM nginx:1.19.0-alpine

RUN apk add openssl
RUN apk add net-tools
RUN apk add -u nghttp2

RUN apk add npm

RUN npm install --save three
RUN npm install --save vite


RUN mkdir -p /etc/nginx/ssl

RUN openssl req -x509 -nodes -days 365 -newkey rsa:4096 -keyout /etc/ssl/private/vgroux.key -out /etc/ssl/certs/vgroux.crt -subj "/C=CH/ST=Lausanne/L=Lausanne/O=42 School/OU=vgroux/CN=vgroux.42.fr/";

RUN mkdir -p /var/www/html && chmod 755 /var/www/html

COPY srcs/ /var/www/html/

COPY ./tools/nginx.conf /etc/nginx/conf.d/default.conf

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]