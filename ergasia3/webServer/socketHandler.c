#include <stdio.h>
#include <sys/wait.h> /* sockets */
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* internet sockets */
#include <netdb.h> /* gethostbyaddr */
#include <unistd.h> /* fork */
#include <stdlib.h> /* exit */
#include <ctype.h> /* toupper */
#include <signal.h> /* signal */

#include "socketHandler.h"
#include "errorHandler.h"


void createSocket(int servingPort, int commandPort){

	int my_socket, my_new_socket;
	struct sockaddr_in server, client;
	socklen_t clientlen;
	struct sockaddr *serverptr=(struct sockaddr *)&server;
	struct sockaddr *clientptr=(struct sockaddr *)&client;
	struct hostent *rem;


	if ((my_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){			//socket creation
		perror_exit("Socket creation");
	}

	server.sin_family = AF_INET; /* Internet domain */
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(commandPort); /* The given port */



	/* Bind socket to address */
	if (bind(my_socket, serverptr, sizeof(server)) < 0){
		perror_exit("Binding");
	}

	/* Listen for connections */
	if (listen(my_socket, 5) < 0){						//5 is default and represents queue_length
		perror_exit("Listening");
	}
	printf("Listening for connections to port %d\n", commandPort);
	printf("before while\n");
	while (1) { 
		clientlen = sizeof(client);
		/* accept connection */


		//gets stuck here because client side does not exist yet
		if ((my_new_socket = accept(my_socket, clientptr, &clientlen))< 0){				//accepts connection with clientptr
			perror_exit("Accepting connection");
		}
		printf("after accept\n");
		/* Find client's name */
		if ((rem = gethostbyaddr((char *) &client.sin_addr.s_addr,sizeof(client.sin_addr.s_addr), client.sin_family))== NULL) {
			perror_exit("Could not find client's name. Error in gethostbyaddr");
		}
		printf("Accepted connection from %s\n", rem->h_name);

		//rest is useless because we want threads, not processes

		//switch (fork()) { /* Create child for serving client */
		/*	case -1: /* Error */
		/*		perror("fork"); break;
			case 0: /* Child process */
		/*		close(sock); child_server(newsock);
				exit(0);
		}*/
		close(my_socket); /* parent closes socket to client */
		close(my_new_socket); /* parent closes socket to client */
	}


	printf("Everything is ok.\n");
}



