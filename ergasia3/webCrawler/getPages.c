#include <stdio.h>
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* internet sockets */
#include <unistd.h> /* read, write, close */
#include <netdb.h> /* gethostbyaddr */
#include <stdlib.h> 
#include <string.h>
#include <pthread.h> 

#include <sys/stat.h>

#include "errorHandler.h"
#include "pageHandler.h"
#include "getPages.h"
#define BUFFSIZE 4096

void connectToServer(int servingPort, int commandPort, char* host_or_IP, char* startingURL, char* save_dir, int numThreads, struct timeb* begin){

	Stats* stats = malloc(sizeof(Stats));
	initializeStats(stats);
	Queue* queue=createQueue();
	
	int sock, i;
	struct sockaddr_in server;
	struct sockaddr *serverptr = (struct sockaddr*)&server;
	struct hostent *rem;
	
	/* Find server address */
	if ((rem = gethostbyname(host_or_IP)) == NULL) {
		free(stats);
		destroyQueue(queue);
		herror("gethostbyname"); exit(1);
	}

	server.sin_family = AF_INET; /* Internet domain */
	memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
	server.sin_port = htons(servingPort); /* Server port */
	
	printf("Connecting to %s port %d\n", host_or_IP, servingPort);

	//for command port
	int my_CommandSocket, my_new_CommandSocket;			
	struct sockaddr_in crawlerForCommand;
	struct sockaddr *crawlerptrForCommand=(struct sockaddr *)&crawlerForCommand;


	if ((my_CommandSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){			//socket creation
		free(stats);
		destroyQueue(queue);
		perror_exit("Socket creation");
	}

	crawlerForCommand.sin_family = AF_INET; /* Internet domain */
	crawlerForCommand.sin_addr.s_addr = htonl(INADDR_ANY);
	crawlerForCommand.sin_port = htons(commandPort); /* The given port */


	/* Bind socket to address */
	if (bind(my_CommandSocket, crawlerptrForCommand, sizeof(crawlerForCommand)) < 0){
		perror_exit("Binding to command port");
	}

	/* Listen for connections */
	if (listen(my_CommandSocket, 5) < 0){		
		perror_exit("Listening");
	}

	struct sockaddr_in client;
	socklen_t clientlen;
	struct sockaddr *clientptr=(struct sockaddr *)&client;
	clientlen = sizeof(client);


	printf("Listening for connections to command port %d\n", commandPort);

	//initialization of fd_set
	fd_set* myFdSet= malloc(sizeof(fd_set));

	//create thread pool
	ThreadPool* pool = createThreadPool(numThreads, save_dir, stats, host_or_IP, queue, startingURL, serverptr);

	while(1){	//do select

		FD_ZERO(myFdSet); /* clear all bits in fdset */
		FD_SET(my_CommandSocket, myFdSet); /* turn on bit for fd my_CommandSocket */

		if(select(my_CommandSocket+1, myFdSet, NULL, NULL, NULL)<0){
			perror_exit("Select");
		}	

		if(FD_ISSET(my_CommandSocket, myFdSet)){		//get command
			/* accept connection */
			if ((my_new_CommandSocket = accept(my_CommandSocket, clientptr, &clientlen))< 0){				//accepts connection with clientptr
				free(myFdSet);
				free(stats);
				destroyQueue(queue);
				destroyThreadPool(pool);
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
						sprintf(statsResults, "Crawler up for %s, served %d pages, %ld bytes\n", timeStr, stats->pagesServed, stats->bytes);

						if (write(my_new_CommandSocket, statsResults, strlen(statsResults)) < 0){		//send length of response to crawler
							perror_exit("write");
						}
						free(timeStr);

					}
					else if(!strcmp(command, "SHUTDOWN")){

						//ending message
						/* Create socket */
						if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
							perror_exit("socket");

						/* Initiate connection */
						if (connect(sock, serverptr, sizeof(server)) < 0)
							perror_exit("connect");

						readWriteInSocket(sock, save_dir, stats, NULL, host_or_IP, NULL, 1);	
						close(sock);

						pthread_mutex_lock(&(pool->mtxContinueWorking));
						pool->continueWorking = 0;
						pthread_mutex_unlock(&(pool->mtxContinueWorking));
						pthread_cond_broadcast(&(pool->cond_nonemptyQueue));
						break;
					}
					else if(strstr(command, "SEARCH")){
						printf("This function has not been implemented :(\n");
					}
				}
			}
			close(my_new_CommandSocket);
		}	
	}
	
	close(my_CommandSocket); /* Close socket and exit */
	free(myFdSet);
	free(stats);
	destroyThreadPool(pool);
	printf("Closing crawler.\n");
}


void readWriteInSocket(int sock, char* save_dir, Stats* stats, char* pageName, char* host_or_IP, ThreadPool* pool, int endFlag){
	char buffer[BUFFSIZE+1];

	if(endFlag){
		int endLength = strlen("Connection Ended")+1;		
		if (write(sock,&endLength, sizeof(int)) < 0)				//write length in socket to close connection
			perror_exit("write");

		if (write(sock,"Connection Ended",endLength) < 0)				//write in socket to close connection
			perror_exit("write");
		return;
	}

	//create and send request
	char* req = createGetRequest(pageName, host_or_IP);

	int requestLength=strlen(req)+1;

	if (write(sock,&requestLength, sizeof(int)) < 0)				//write in socket request length
		perror_exit("write");

	if (write(sock,req, requestLength) < 0)							//write in socket request
		perror_exit("write");
	free(req);



	//get and handle response
	int lengthOfBuffer=0;
	int responseLength = 0;
	
	if ((lengthOfBuffer = read(sock, &responseLength, sizeof(int))) < 0)					//read from socket header length of response
		perror_exit("read");

	char* response=malloc((responseLength+1)*sizeof(char));
	int charsRead=0;

	int charsToRead;
	if(responseLength<BUFFSIZE)
		charsToRead=responseLength;
	else
		charsToRead=BUFFSIZE;

	response[0]='\0';
	while(charsRead<responseLength){

		if ((lengthOfBuffer=read(sock, buffer, charsToRead)) < 0)					//read from socket response
			perror_exit("read");

		buffer[lengthOfBuffer]='\0';
		strcat(response, buffer);
		charsRead+=lengthOfBuffer;

		if(responseLength-charsRead<BUFFSIZE)
			charsToRead=responseLength-charsRead;
		else
			charsToRead=BUFFSIZE;
	}
	handleResponse(response, pageName, save_dir, pool, stats);
	free(response);		
	free(pageName);
	close(sock); /* Close socket*/

}

char* createGetRequest(char* url, char* host){
	char* getReq = malloc((strlen(url)+strlen(host)+200)*sizeof(char));
	sprintf(getReq, "GET %s HTTP/1.1\nUser-­Agent: Mozilla/4.0 (compatible;; MSIE5.01;; Windows NT)\nHost: %s\nAccept-­Language: en-­us\nAccept-­Encoding: gzip, deflate\nConnection: Keep-­Alive\n\n", url, host);

	return getReq;
	
}

void handleResponse(char* response, char* url, char* save_dir, ThreadPool* pool, Stats* stats){
	//gets first line for OK
	//saves it in saveDir
	char* tempResponse= malloc((strlen(response)+1)*sizeof(char));
	strcpy(tempResponse, response);
	char* tempResponse2=tempResponse;

	char* fileName=malloc((strlen(url)+strlen(save_dir)+1)*sizeof(char));
	sprintf(fileName, "%s%s",save_dir, url);
	
	createDir(url, save_dir);
	if(file_exists(fileName)){
		free(tempResponse);
		free(fileName);
		return;
	}
	FILE* fp = fopen(fileName, "w+");
	if(fp==NULL){	//file already exists
		perror_exit("fopen");
	}

	char* line = strtok (tempResponse,"\n");
	int lineCounter=0;
	int OKFlag=0;
	while (line != NULL){

		if(lineCounter==0  && strcmp(line,"HTTP/1.1 200 OK")==0){
			OKFlag=1;
			pthread_mutex_lock(&(pool->mtxStats));
			stats->pagesServed++;
			pthread_mutex_unlock(&(pool->mtxStats));
		}
		if(OKFlag==1){
			char* str1=strstr(line, "Content-Length:");
			char* str2=strstr(line, "Content-­Length:");	//uad
			if(str1!=NULL || str2!=NULL){
				char* bytesString=strstr(line, ":");
				int bytes = atoi(bytesString+1);		//+1 to avoid :
				pthread_mutex_lock(&(pool->mtxStats));
				stats->bytes+=bytes;
				pthread_mutex_unlock(&(pool->mtxStats));
			}
		}

		if((strlen(line)>5 && line[0]=='<' && line[1]=='h' && line[2]=='t' && line[3]=='m' && line[4]=='l' && line[5]=='>') || (strlen(line)>5 && line[0]=='<' && line[1]=='!' && line[2]=='D' && line[3]=='O' && line[4]=='C') ) {
			fprintf(fp, "%s", line);
			char* remainingLine = strtok(NULL,"");
			if(remainingLine!=NULL)
				fprintf(fp, "%*.*s", (int)strlen(remainingLine)-2, (int)strlen(remainingLine)-2, remainingLine);
			break;
		}

		line = strtok (NULL, "\n");
		lineCounter++;
	}

	getLinksIntoQueue(pool, fp);

	fclose(fp);
	free(fileName);

	free(tempResponse2);
}

void createDir(char* pageName, char* save_dir){
	char* tempPageName=malloc((strlen(pageName))*sizeof(char));
	strcpy(tempPageName, pageName+1);	//to avoid '/'

	char* line=strtok(tempPageName, "/");

	char* dirName=malloc((strlen(line) + strlen(save_dir) +2)*sizeof(char));

	if(save_dir[strlen(save_dir)-1]!='/')
		sprintf(dirName, "%s/%s", save_dir,line);
	else
		sprintf(dirName, "%s%s", save_dir,line);

	struct stat st = {0};

	if (stat(dirName, &st) == -1) {
	    mkdir(dirName, 0700);
	}

	free(dirName);
	if(line)
		free(line);

}


bool file_exists(const char * filename)
{
	FILE* file=fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return true;
    }
    return false;
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