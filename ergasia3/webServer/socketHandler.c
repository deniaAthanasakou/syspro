#include <stdio.h>
#include <string.h>
#include <sys/wait.h> /* sockets */
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* internet sockets */
#include <netdb.h> /* gethostbyaddr */
#include <unistd.h> /* fork */
#include <stdlib.h> /* exit */
#include <ctype.h> /* toupper */
#include <signal.h> /* signal */
#include <time.h>

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
	server.sin_port = htons(servingPort); /* The given port */



	/* Bind socket to address */
	if (bind(my_socket, serverptr, sizeof(server)) < 0){
		perror_exit("Binding");
	}

	/* Listen for connections */
	if (listen(my_socket, 5) < 0){						//5 is default and represents queue_length
		perror_exit("Listening");
	}
	printf("Listening for connections to port %d\n", servingPort);
	getResponce("OK", 2, "he");
	while (1) { 
		clientlen = sizeof(client);
		/* accept connection */

		if ((my_new_socket = accept(my_socket, clientptr, &clientlen))< 0){				//accepts connection with clientptr
			perror_exit("Accepting connection");
		}

		/* Find client's name */
		if ((rem = gethostbyaddr((char *) &client.sin_addr.s_addr,sizeof(client.sin_addr.s_addr), client.sin_family))== NULL) {
			perror_exit("Could not find client's name. Error in gethostbyaddr");
		}
		printf("Accepted connection from %s\n", rem->h_name);

		readFromSocket(my_new_socket);

		close(my_socket); /* parent closes socket to client */
		close(my_new_socket); /* parent closes socket to client */
	}


	printf("Everything is ok.\n");
}

void readFromSocket(int newSocket) {
	char buf[1];

	while(read(newSocket, buf, 1) > 0) { /* Receive 1 char */
		putchar(buf[0]); /* Print received char */
		/* Capitalize character */
		buf[0] = 'a';//toupper(buf[0]);
		/* Reply */
		if (write(newSocket, buf, 1) < 0)
			perror_exit("write");
	}
	printf("Closing connection.\n");
	close(newSocket); /* Close socket */

}

char* getResponce(char* firstFline, int contentLength, char* content){

	char date[100];
	time_t now = time(0);
	struct tm tm = *gmtime(&now);
	strftime(date, sizeof date, "%a, %d %b %Y %H:%M:%S %Z", &tm);
	printf("Time is: [%s]\n", date);


	char* responce = malloc((strlen(firstFline)+strlen(content)+150)*sizeof(char));
	int length = strlen(firstFline)+strlen(content)+150;
	sprintf(responce, "%s\nDate: %s\nServer: myhttpd/1.0.0 (Ubuntu64)\nContent-­Length: %d\nContent-­Type: text/html\nConnection: Closed\n\n[%s]\n", firstFline, date, contentLength, content);

	printf("sizeof req %ld, %d\n",strlen(responce), length);
	printf("str = %s", responce);

	return responce;
}



