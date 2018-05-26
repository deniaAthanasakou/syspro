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
	char buffer[4096];
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
		int lengthOfBuffer=0;
		char* req = createGetRequest(startingURL, host_or_IP);
		if (write(sock,req, strlen(req)) < 0)				//write in socket
			perror_exit("write");

		if ((lengthOfBuffer = read(sock, buffer, 20)) < 0)					//read from socket header
			perror_exit("read");

		buffer[lengthOfBuffer]='\0';
		int lengthOfResponse=atoi(buffer);
		printf("lengthOfResponse %d\n", lengthOfResponse);


		char* response=malloc((lengthOfResponse+1)*sizeof(char));
		int charsRead=0;

		int charsToRead;
		if(lengthOfResponse<4096)
			charsToRead=lengthOfResponse;
		else
			charsToRead=4096;

		response[0]='\0';
		while(charsRead<lengthOfResponse){
			if ((lengthOfBuffer=read(sock, buffer, charsToRead)) < 0)					//read from socket response
				perror_exit("read");

			//printf("lengthOfBuffer %d\n", lengthOfBuffer);
			buffer[lengthOfBuffer]='\0';
			//printf("buffer: %s\n", buffer);
			strcat(response, buffer);
			charsRead+=charsToRead;


			if(lengthOfResponse-charsRead<4096)
				charsToRead=lengthOfResponse-charsRead;
			else
				charsToRead=4096;
		}



		printf("Received string: %s\n", response);

		printf("charsRead %d, lengthOfResponse %d\n", charsRead, lengthOfResponse);
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

void handleResponse(char* response, char* url){
	//gets first line for OK
	//gets line for content will start with <!DOCTYPE html>
	//saves it in saveDir
}