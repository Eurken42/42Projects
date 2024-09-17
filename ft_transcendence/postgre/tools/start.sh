#!/bin/bash
# service postgresql start

adduser --disabled-password --gecos "" $POSTGRES_USER
echo    $POSTGRES_USER:$POSTGRES_PASSWORD | /usr/sbin/chpasswd

echo    "CREATE USER $POSTGRES_USER WITH ENCRYPTED PASSWORD '$POSTGRES_PASSWORD';" >> postgres.sql
echo    "CREATE DATABASE $POSTGRES_DB OWNER $POSTGRES_USER WITH TEMPLATE template0;" >> postgres.sql
echo    "GRANT ALL PRIVILEGES ON DATABASE $POSTGRES_DB TO $POSTGRES_USER;" >> postgres.sql
echo	"ALTER DATABASE $POSTGRES_DB REFRESH COLLATION VERSION;" >> postgres.sql

psql -v ON_ERROR_STOP=1 -U $POSTGRES_USER -dbname $POSTGRES_DB -f postgres.sql
rm postgres.sql
su postgres