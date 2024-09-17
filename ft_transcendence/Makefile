all:
	@mkdir -p ~/data/db
	@bash req/ip.sh
	docker-compose up --build

cli:
	@if ! docker ps --format '{{.Names}}' | grep -q "cli"; then \
		echo "You must start the project before by using the command 'make'"; \
	else \
		docker exec -it cli /usr/local/cargo/bin/cli; \
	fi



down: 
	docker-compose down --remove-orphans

debug: all
	docker-compose logs -f

look:
	docker ps -a
	@echo ''
	docker image ls -a
	@echo ''
	docker volume ls
	@echo ''
	docker network ls

clean:
	# cargo clean --manifest-path=cli/Cargo.toml
	docker image prune -a

fclean: down clean vol
	docker system prune -a --volumes
	
vol:
	docker volume rm push_db
	rm -rf ~/data

re: fclean all
	
.PHONY: all down re clean fclean vol debug look cli nginx-ip $(RUST_SOURCE)