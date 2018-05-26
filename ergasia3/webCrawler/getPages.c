#include <stdio.h>
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* internet sockets */
#include <unistd.h> /* read, write, close */
#include <netdb.h> /* gethostbyaddr */
#include <stdlib.h> /* exit */
#include <string.h> /* strlen */

#include "errorHandler.h"
#include "getPages.h"

void connectToServer(int servingPort, int commandPort, char* host_or_IP, char* startingURL){

	int sock, i;
	char buffer[1024];
	struct sockaddr_in server;
	struct sockaddr *serverptr = (struct sockaddr*)&server;
	struct hostent *rem;
	
	/* Create socket */
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror_exit("socket");

	/* Find server address */
	if ((rem = gethostbyname(host_or_IP)) == NULL) {
		herror("gethostbyname"); exit(1);
	}

	server.sin_family = AF_INET; /* Internet domain */
	memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
	server.sin_port = htons(servingPort); /* Server port */

	/* Initiate connection */
	if (connect(sock, serverptr, sizeof(server)) < 0)
		perror_exit("connect");

	printf("Connecting to %s port %d\n", host_or_IP, servingPort);

	

	do {
		//printf("Give input string: ");
		//fgets(buf, sizeof(buf), stdin); /* Read from stdin*/

		char* req = createGetRequest(startingURL, host_or_IP);
		if (write(sock,req, strlen(req)) < 0)				//write in socket
			perror_exit("write");

		if (read(sock, buffer, 1024) < 0)					//read from socket
			perror_exit("read");


		/*for(i=0; buf[i] != '\0'; i++) { /* For every char */
			/* Send i-th character */
		//	if (write(sock, buf + i, 1) < 0)				//write in socket
		//		perror_exit("write");
			/* receive i-th character transformed */
		//	if (read(sock, buf + i, 1) < 0)					//read from socket
		//		perror_exit("read");
		//}
		printf("Received string: %s\n", buffer);
		strcpy(buffer, "END\n");
	} while (strcmp(buffer, "END\n") != 0); /* Finish on "end" */
	close(sock); /* Close socket and exit */
}



char* createGetRequest(char* url, char* host){
	char* getReq = malloc((strlen(url)+strlen(host)+200)*sizeof(char));
	//strcpy(getReq, "hello");
	sprintf(getReq, "GET %s HTTP/1.1\nUser-­Agent: Mozilla/4.0 (compatible;; MSIE5.01;; Windows NT)\nHost: %s\nAccept-­Language: en-­us\nAccept-­Encoding: gzip, deflate\nConnection: Keep-­Alive\n\n", url, host);

	//printf("sizeof req %ld\n",strlen(getReq));
	//printf("str = %s", getReq);

	return getReq;
	
}