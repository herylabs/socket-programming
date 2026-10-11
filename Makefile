all: the_client the_server

the_client: src/the_client.c
	cc -Wall -Wextra -o build/the_client src/the_client.c

the_server: src/the_server.c
	cc -Wall -Wextra -o build/the_server src/the_server.c