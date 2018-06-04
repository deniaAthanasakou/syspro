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
#include <sys/select.h>
#include <sys/time.h>
#include "socketHandler.h"
#include "errorHandler.h"
#include "pageHandler.h"

#define BUFFSIZE 4096


void createSocket(int servingPort, int commandPort, char* rootDirectory, int numOfThreads, struct timeval* begin){

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




	int my_CommandSocket, my_new_CommandSocket;
	struct sockaddr_in serverForCommand;
	struct sockaddr *serverptrForCommand=(struct sockaddr *)&serverForCommand;


	if ((my_CommandSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){			//socket creation
		perror_exit("Socket creation");
	}

	serverForCommand.sin_family = AF_INET; /* Internet domain */
	serverForCommand.sin_addr.s_addr = htonl(INADDR_ANY);
	serverForCommand.sin_port = htons(commandPort); /* The given port */


	/* Bind socket to address */
	if (bind(my_CommandSocket, serverptrForCommand, sizeof(serverForCommand)) < 0){
		perror_exit("Binding");
	}

	/* Listen for connections */
	if (listen(my_CommandSocket, 5) < 0){						//5 is default and represents queue_length
		perror_exit("Listening");
	}


	printf("Listening for connections to port %d\n", servingPort);
	printf("Listening for connections to command port %d\n", commandPort);
	int pagesServed=0;

	//initialization of fd_set
	fd_set* myFdSet= malloc(sizeof(fd_set));
	clientlen = sizeof(client);
	Stats* stats = malloc(sizeof(Stats));
	initializeStats(stats);


	while (1) { 
		FD_ZERO(myFdSet); /* clear all bits in fdset */
		FD_SET(my_socket, myFdSet); /* turn on bit for fd my_socket */
		FD_SET(my_CommandSocket, myFdSet); /* turn on bit for fd my_CommandSocket */
		int nfds=0;
		if(my_socket>my_CommandSocket){
			nfds=my_socket+1;
		}
		else{
			nfds=my_CommandSocket+1;
		}
		if(select(nfds, myFdSet, NULL, NULL, NULL)<0){
			printf("error in select\n");
			perror_exit("Select");
		}		
		if(FD_ISSET(my_CommandSocket, myFdSet)){		//get command
			/* accept connection */
			if ((my_new_CommandSocket = accept(my_CommandSocket, clientptr, &clientlen))< 0){				//accepts connection with clientptr
				perror_exit("Accepting connection with telnet");
			}
			char command[15];
			int commandLength=0;
			if((commandLength=read(my_new_CommandSocket, command, 15)) > 0){
				if(commandLength>=2){
					command[commandLength-2]='\0';
					printf("COMMAND '%s'\n", command);

					if(!strcmp(command, "STATS")){
						printf("in STATS\n");
						struct timeval end;
						gettimeofday(&end, NULL); 

						unsigned int t = (end.tv_usec - begin->tv_usec)/1000;	// /1000 to get milliseconds
						printf("millisecs %d\n", t);

						printf("served %d pages, %ld bytes\n", stats->pagesServed, stats->bytes);
						initializeStats(stats);

					}
					else if(!strcmp(command, "SHUTDOWN")){
						printf("in SHUTDOWN\n"); 
						//send signal to all threads to stop
						break;
					}
					else{
						printf("ignore\n"); 
					}
				}
			}
		}

		if(FD_ISSET(my_socket, myFdSet)){			//get request from crawler			/* accept connection */
			if ((my_new_socket = accept(my_socket, clientptr, &clientlen))< 0){				//accepts connection with clientptr
				perror_exit("Accepting connection with client");
			}
			readFromSocket(my_new_socket, rootDirectory, stats);
		}		
	}




	close(my_socket); /* parent closes socket to client */
	//close(my_new_socket); /* parent closes socket to client */ //isws na mh xreiazetai
	close(my_CommandSocket); /* parent closes socket to client */
	close(my_new_CommandSocket); /* parent closes socket to client */ //isws na mh xreiazetai
	free(myFdSet);
	printf("Everything is ok.\n");
	//
	free(stats);
}

int readFromSocket(int newSocket, char* rootDirectory, Stats* stats) {
	char request[1024];
	char buffer[BUFFSIZE];
	int requestLength=0;
	//memset(request, 0, 1024);

	while(1){

		if((requestLength = read(newSocket, request, 1024)) > 0){ /* Receive GET */
			request[requestLength]='\0';

			/*if(!strcmp(request, "Connection Ended")){
				printf("DONEEEE\n");
				break;
			}*/

			printf("req %s\n", request);
			char* response = handleRequest(request, rootDirectory, stats);

			long responseLength = strlen(response);

			sprintf(buffer, "%ld", responseLength);
			if (write(newSocket, buffer, strlen(buffer)) < 0){		//send header to crawler
				free(response);
				perror_exit("writee");			//error here
			}
			printf("lengthOfResponse %ld\n", responseLength);
			printf("response %s\n", response);
			int charsW=0;	//num of chars written so far

			int charsToWrite;
			if(responseLength<BUFFSIZE)
				charsToWrite=responseLength;
			else
				charsToWrite=BUFFSIZE;

			//printf("response is %s\n", response);

			while(charsW<responseLength){
				//printf("charsToWrite = %d, charsW %d, responseLength %ld\n",charsToWrite, charsW, responseLength);
				if (write(newSocket, response+charsW, charsToWrite) < 0){					//write content to buffer
					free(response);
					perror_exit("writef");
				}

				charsW+=charsToWrite;


				if(responseLength-charsW<BUFFSIZE)
					charsToWrite=responseLength-charsW;
				else
					charsToWrite=BUFFSIZE;
			}

			free(response);
		}
		else{
			perror_exit("read");
		}
		//memset(request, 0, 1024);
	}
	printf("Closing connection.\n");
	close(newSocket); /* Close socket */
	return 1;

}

char* getResponse(char* firstFline, int contentLength, char* content){
	//printf("content = %sOPs\n", content);
	char date[100];
	time_t now = time(0);
	struct tm tm = *gmtime(&now);
	strftime(date, sizeof date, "%a, %d %b %Y %H:%M:%S %Z", &tm);
	//printf("Time is: [%s]\n", date);


	char* response = malloc((strlen(firstFline)+strlen(content)+150)*sizeof(char));
	//int length = strlen(firstFline)+strlen(content)+150;
	sprintf(response, "%s\nDate: %s\nServer: myhttpd/1.0.0 (Ubuntu64)\nContent-­Length: %d\nContent-­Type: text/html\nConnection: Closed\n\n%s\n", firstFline, date, contentLength, content);
	//strcpy(response, "Hello");
	//printf("sizeof req %ld, %d\n",strlen(response), length);
	//printf("str = %s", response);
	//printf("response = %sOPP\n", response);
	
	return response;
}

char* handleRequest(char* req, char* rootDirectory, Stats* stats){	//will check for line with GET and line with Host
	char* response=NULL;

	char* initialReq=malloc((strlen(req)+1)*sizeof(char));
	strcpy(initialReq, req);

	char* GETLine=NULL;
	char* hostLine=NULL;

	char* line = strtok (req,"\n");
	while (line != NULL)
	{	
		//printf("line is '%s'\n",line );
		if(strlen(line)>3 && line[0]=='G' && line[1]=='E' && line[2]=='T' && line[3]==' '){
			GETLine=malloc((strlen(line)+1)*sizeof(char));
			strcpy(GETLine, line);
		}
		if(strlen(line)>5 && line[0]=='H' && line[1]=='o' && line[2]=='s' && line[3]=='t' && line[4]==':' && line[5]==' '){
			hostLine=malloc((strlen(line)+1)*sizeof(char));
			strcpy(hostLine, line);
		}

		line = strtok (NULL, "\n");
	}
	//check if request is valid
	if(strlen(initialReq)>3 && initialReq[strlen(initialReq)-1]=='\n' && initialReq[strlen(initialReq)-2]=='\n'){ //if last line is empty
		char* page=checkGETLine(GETLine);
		if(page==NULL || checkHostLine(hostLine)==0){
			printf("Wrong request\n");
			response=getResponseForBadRequest();
		}
		else{			//check page
			//printf("page is '%s'\n", page);
			ResponseStr* responseStr = getResponseStrOfPage(page, rootDirectory);

			if(!strcmp(responseStr->firstLine, "HTTP/1.1 200 OK")){
				stats->pagesServed++;
				stats->bytes+=responseStr->contentLength;

			}

			response = getResponse(responseStr->firstLine, responseStr->contentLength, responseStr->content);
			free(responseStr->content);
			free(responseStr->firstLine);
			free(responseStr);
			free(page);
		}
		
		
	}
	else{
		response=getResponseForBadRequest();
	}

	if(GETLine)
			free(GETLine);
	if(hostLine)
			free(hostLine);
			
	free(initialReq);
	return response;

}

char* checkGETLine(char* GETLine){
	char* page=NULL;

	char* word=strtok (GETLine," \t");
	if (strcmp(word, "GET")!=0)
		return NULL;

	word=strtok (NULL," \t");		//page
	if(word==NULL){
		return NULL;
	}
	page=malloc((strlen(word)+1)*sizeof(char));
	strcpy(page, word);

	word=strtok (NULL," \t\n");
	if (word==NULL || strcmp(word, "HTTP/1.1")!=0)
		return NULL;

	word=strtok (NULL," \t\n");
	if(word!=NULL){
		return NULL;
	}
	return page;
}

int checkHostLine(char* HostLine){

	char* word=strtok (HostLine," \t");
	if (strcmp(word, "Host:")!=0)
		return 0;

	word=strtok (NULL," \t");		//may need to change this
	if(word==NULL || strcmp(word, "localhost")!=0){
		return 0;
	}

	word=strtok (NULL," \t\n");
	if(word!=NULL){
		return 0;
	}
	return 1;
}

char* getResponseForBadRequest(){

	char* response = malloc((strlen("Wrong request.")+1)*sizeof(char));
	strcpy(response, "Wrong request.");
	return response;
}


void initializeStats(Stats* stats){
	stats->pagesServed=0;
	stats->bytes=0;
}




