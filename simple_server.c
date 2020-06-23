#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

char server_message[1024] = "17BEC1074\tAkshat Srivastava\n17BEC1171\tApoorv kansal\n17BEC1169\tRaunak Srivastava";


void * handle_connection(void * p_client_socket){
	pthread_t thr = pthread_self();
	printf("process id %lu\n", thr);


	int client_socket = *((int*)p_client_socket);
	free(p_client_socket);
	send(client_socket, server_message, sizeof(server_message),0);
	sleep(8);
	printf("closing process: %lu\n", thr);
	close(client_socket);
	return NULL;
}

int main(){


	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);


	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

	listen(server_socket, 100);
	int client_socket;
	printf("Listening on port: 8080\n");


	while(1){
		client_socket = accept(server_socket, NULL, NULL);
		pthread_t t;
		int *pclient = malloc(sizeof(int));
		*pclient = client_socket;
		pthread_create(&t,NULL,handle_connection, pclient);

	}

	return 0;
}

