#include <stdio.h>
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* internet sockets */
#include <unistd.h> /* read, write, close */
#include <netdb.h> /* gethostbyaddr */
#include <stdlib.h> /* exit */
#include <string.h> /* strlen */

#include "errorHandler.h"

void createSocket(int port, int commandPort){

	int sock, i;
	char buf[256];
	struct sockaddr_in server;
	struct sockaddr *serverptr = (struct sockaddr*)&server;
	struct hostent *rem;
	
	/* Create socket */
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror_exit("socket");
	/* Find server address */
	if ((rem = gethostbyname(argv[1])) == NULL) {
		herror("gethostbyname"); exit(1);
	}

	server.sin_family = AF_INET; /* Internet domain */
	memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
	server.sin_port = htons(port); /* Server port */

	/* Initiate connection */
	if (connect(sock, serverptr, sizeof(server)) < 0)
		perror_exit("connect");

	printf("Connecting to %s port %d\n", argv[1], port);

	do {
		printf("Give input string: ");
		fgets(buf, sizeof(buf), stdin); /* Read from stdin*/
		for(i=0; buf[i] != '\0'; i++) { /* For every char */
			/* Send i-th character */
			if (write(sock, buf + i, 1) < 0)
				perror_exit("write");
			/* receive i-th character transformed */
			if (read(sock, buf + i, 1) < 0)
				perror_exit("read");
		}
		printf("Received string: %s", buf);
	} while (strcmp(buf, "END\n") != 0); /* Finish on "end" */
	close(sock); /* Close socket and exit */
}