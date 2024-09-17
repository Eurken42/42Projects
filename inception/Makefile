DATA_FOLDER = /home/eurken/data

all:
	clear
	mkdir -p $(DATA_FOLDER)/wordpress
	mkdir -p $(DATA_FOLDER)/mariadb
	docker-compose build --no-cache
	docker-compose up -d

clean:
	clear
	docker-compose down
	docker image prune -af
	docker builder prune -af

fclean: clean
	docker-compose down
	docker system prune -af --volumes
	docker volume rm -f wordpress
	docker volume rm -f mariadb
	rm -rf $(DATA_FOLDER)/wordpress
	rm -rf $(DATA_FOLDER)/mariadb
	
re : fclean all

.PHONY: all re fclean clean list