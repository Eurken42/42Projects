FROM debian:bullseye

RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install mariadb-server -y

RUN mkdir -p /run/mysqld
RUN chown -R mysql:root /run/mysqld

COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY ./tools/mysql.sh /etc/mysql.sh
COPY ./conf/conf.sql /etc/conf.sql
RUN chmod a=rwx /etc/conf.sql
RUN chmod a+x /etc/mysql.sh

EXPOSE 3306

ENTRYPOINT ["sh", "/etc/mysql.sh"]