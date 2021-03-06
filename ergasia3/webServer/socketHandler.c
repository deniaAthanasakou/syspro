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
#include <pthread.h>

#define BUFFSIZE 4096

void createSocket(int servingPort, int commandPort, char* rootDirectory, struct timeb* begin, int numThreads){

	Stats* stats = malloc(sizeof(Stats));
	initializeStats(stats);

	//create thread pool
	ThreadPool* pool = createThreadPool(numThreads, rootDirectory, stats);

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
		perror_exit("Binding to serving port");
	}

	/* Listen for connections */
	if (listen(my_socket, 5) < 0){					
		perror_exit("Listening");
	}

	//for command port
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
		perror_exit("Binding to command port");
	}

	/* Listen for connections */
	if (listen(my_CommandSocket, 5) < 0){				
		perror_exit("Listening");
	}


	printf("Listening for connections to port %d\n", servingPort);
	printf("Listening for connections to command port %d\n", commandPort);

	//initialization of fd_set
	fd_set* myFdSet= malloc(sizeof(fd_set));
	clientlen = sizeof(client);
	


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
			perror_exit("Select");
		}	

		if(FD_ISSET(my_CommandSocket, myFdSet)){		//get command
			/* accept connection */
			if ((my_new_CommandSocket = accept(my_CommandSocket, clientptr, &clientlen))< 0){				//accepts connection with clientptr
				perror_exit("Accepting connection to command port");
			}
			char command[15];
			int commandLength=0;
			if((commandLength=read(my_new_CommandSocket, command, 15)) > 0){
				if(commandLength>=2){
					command[commandLength-2]='\0';
					if(!strcmp(command, "STATS")){
						struct timeb end;
						ftime(&end); 
						char* timeStr = timeToString(begin, &end);
						
						char statsResults[100];
						sprintf(statsResults, "Server up for %s, served %d pages, %ld bytes\n", timeStr, stats->pagesServed, stats->bytes);

						if (write(my_new_CommandSocket, statsResults, strlen(statsResults)) < 0){	
							perror_exit("write");
						}

						free(timeStr);

					}
					else if(!strcmp(command, "SHUTDOWN")){
						break;
					}
				}
			}
			close(my_new_CommandSocket); /* parent closes socket to client */
		}

		if(FD_ISSET(my_socket, myFdSet)){			//get request from crawler			/* accept connection */

			if ((my_new_socket = accept(my_socket, clientptr, &clientlen))< 0){				//accepts connection with clientptr
				perror_exit("Accepting connection");
			}

			insertFd(pool, my_new_socket);
			pthread_cond_signal(&(pool->cond_nonempty));
		}	
	}

	close(my_socket); /* parent closes socket to client */
	close(my_CommandSocket); /* parent closes socket to client */
	
	free(myFdSet);
	free(stats);
	destroyThreadPool(pool);
	printf("Closing server.\n");
}

int readFromSocket(int newSocket, char* rootDirectory, ThreadPool* pool) {
	char request[1024];
	char buffer[BUFFSIZE+1];
	

	int requestLength=0;
	if(read(newSocket, &requestLength, sizeof(int)) < 0){ 		//get length of request
		perror_exit("read");
	}

	if(requestLength>=1024){
		printf("Error! Request is too big.\n");
		exit(1);
	}

	if(read(newSocket, request, requestLength) < 0) //get request
		perror_exit("read");
	request[requestLength]='\0';

	if(!strcmp(request, "Connection Ended")){		
		printf("Closing connection to crawler.\n");
		close(newSocket); /* Close socket */
		return 0;
	}

	
	char* response = handleRequest(request, rootDirectory, pool);
	
	int responseLength = strlen(response);
	if (write(newSocket, &responseLength, sizeof(int)) < 0){		//send length of response to crawler
		free(response);
		perror_exit("write");
	}

	int charsW=0;			//chars written so far

	int charsToWrite;		//number of chars to be written each time
	if(responseLength<BUFFSIZE)
		charsToWrite=responseLength;
	else
		charsToWrite=BUFFSIZE;

	int actualWritten=0;
	while(charsW<responseLength){
		if ((actualWritten=write(newSocket, response+charsW, charsToWrite)) < 0){					//write content to buffer
			free(response);
			perror_exit("write");
		}

		charsW+=actualWritten;

		if(responseLength-charsW<BUFFSIZE)
			charsToWrite=responseLength-charsW;
		else
			charsToWrite=BUFFSIZE;
	}
	free(response);
	
	close(newSocket); /* Close socket */
	return 1;

}

char* getResponse(char* firstFline, int contentLength, char* content){
	char date[100];
	time_t now = time(0);
	struct tm tm = *gmtime(&now);
	strftime(date, sizeof date, "%a, %d %b %Y %H:%M:%S %Z", &tm);


	char* response = malloc((strlen(firstFline)+strlen(content)+150)*sizeof(char));
	sprintf(response, "%s\nDate: %s\nServer: myhttpd/1.0.0 (Ubuntu64)\nContent-­Length: %d\nContent-­Type: text/html\nConnection: Closed\n\n%s\n", firstFline, date, contentLength, content);

	return response;
}

char* handleRequest(char* req, char* rootDirectory, ThreadPool* pool){	//will check for line with GET and line with Host
	char* response=NULL;

	char* initialReq=malloc((strlen(req)+1)*sizeof(char));
	strcpy(initialReq, req);
	int hostFlag=0;		//no host was given
	char* GETLine=NULL;

	char* line = strtok (req,"\n");
	while (line != NULL)
	{	
		if(strlen(line)>2 && line[0]=='G' && line[1]=='E' && line[2]=='T'){
			GETLine=malloc((strlen(line)+1)*sizeof(char));
			strcpy(GETLine, line);
		}
		if(strlen(line)>4 && line[0]=='H' && line[1]=='o' && line[2]=='s' && line[3]=='t' && line[4]==':'){
			hostFlag=1;
		}

		line = strtok (NULL, "\n");
	}
	//check if request is valid
	if(strlen(initialReq)>3 && initialReq[strlen(initialReq)-1]=='\n' && initialReq[strlen(initialReq)-2]=='\n'){ //if last line is empty
		char* page=checkGETLine(GETLine);
		if(page==NULL || hostFlag==0){
			response=getResponseForBadRequest();
		}
		else{			//check page
			ResponseStr* responseStr = getResponseStrOfPage(page, rootDirectory);

			if(!strcmp(responseStr->firstLine, "HTTP/1.1 200 OK")){
				pthread_mutex_lock(&(pool->mtxStats));
				pool->stats->pagesServed++;
				pool->stats->bytes+=responseStr->contentLength;
				pthread_mutex_unlock(&(pool->mtxStats));
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
			
	free(initialReq);
	return response;

}

char* checkGETLine(char* GETLine){
	char* page=NULL;

	char* word=strtok (GETLine," \t");
	if (strcmp(word, "GET")!=0){
		printf("was not GET\n");
		return NULL;
	}

	word=strtok (NULL," \t");		//page
	if(word==NULL){
		printf("word NULL\n");
		return NULL;
	}
	page=malloc((strlen(word)+1)*sizeof(char));
	strcpy(page, word);

	word=strtok (NULL," \t\n");
	if (word==NULL || strcmp(word, "HTTP/1.1")!=0){
		free(page);
		return NULL;
	}

	word=strtok (NULL," \t\n");
	if(word!=NULL){
		printf("word was not NOT NULL\n");
		free(page);
		return NULL;
	}
	return page;
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

char* timeToString(struct timeb* begin,  struct timeb* end){

	long int secDifference = end->time-begin->time;
	int millisecDifference = abs(end->millitm - begin->millitm);
	int hr=0, min=0, sec=0;

	if(secDifference>3600){
		min = secDifference/60;
		sec = secDifference%60;
		hr = min/60;
		min = min%60;
	}
	else{
		min = secDifference/60;
		sec = secDifference%60;
	}

	char* timeStr=malloc(20*sizeof(char));
	timeStr[0]='\0';

	if (hr<10)
	{
		sprintf(timeStr, "0%d:", hr);
	}
	else{
		sprintf(timeStr, "%d:", hr);
	}

	if (min<10)
	{
		sprintf(timeStr + strlen(timeStr), "0%d:", min);
	}
	else{
		sprintf(timeStr + strlen(timeStr), "%d:", min);
	}

	if (sec<10)
	{
		sprintf(timeStr + strlen(timeStr), "0%d.", sec);
	}
	else{
		sprintf(timeStr + strlen(timeStr), "%d.", sec);
	}

	if (millisecDifference<10)
	{
		sprintf(timeStr + strlen(timeStr), "0%d", millisecDifference);
	}
	else{
		sprintf(timeStr + strlen(timeStr), "%d", millisecDifference);
	}

	timeStr[strlen(timeStr)]='\0';

	return timeStr;

}