#include <stdio.h>
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* internet sockets */
#include <unistd.h> /* read, write, close */
#include <netdb.h> /* gethostbyaddr */
#include <stdlib.h> 
#include <string.h> 
#include <sys/stat.h>


#include "errorHandler.h"
#include "pageHandler.h"
#include "getPages.h"
#define BUFFSIZE 4096

void connectToServer(int servingPort, int commandPort, char* host_or_IP, char* startingURL, char* save_dir){

	int sock, i;
	char buffer[BUFFSIZE];
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

	Queue* queue=createQueue();
	insertInQueue(queue, startingURL);
	QueueNode* tempNode = queue->firstNode;

	while(tempNode!=NULL) {
		int lengthOfBuffer=0;
		char* req = createGetRequest(tempNode->pageName, host_or_IP);
		if (write(sock,req, strlen(req)) < 0)				//write in socket
			perror_exit("write");
		free(req);

		long lengthOfResponse=0;
		if ((lengthOfBuffer=read(sock, buffer, 20)) < 0)					//read from socket header
			perror_exit("read");
		
		buffer[lengthOfBuffer] = '\0';
		lengthOfResponse=atoi(buffer);
		printf("lengthOfResponse %ld\n", lengthOfResponse);

		
		char* response=malloc((lengthOfResponse+1)*sizeof(char));
		int charsRead=0;

		int charsToRead;
		if(lengthOfResponse<BUFFSIZE)
			charsToRead=lengthOfResponse;
		else
			charsToRead=BUFFSIZE;

		response[0]='\0';
		while(charsRead<lengthOfResponse){

			if ((lengthOfBuffer=read(sock, buffer, charsToRead)) < 0)					//read from socket response
				perror_exit("read");

			buffer[lengthOfBuffer]='\0';
			strcat(response, buffer);
			charsRead+=charsToRead;


			if(lengthOfResponse-charsRead<BUFFSIZE)
				charsToRead=lengthOfResponse-charsRead;
			else
				charsToRead=BUFFSIZE;
		}



		//printf("Received string: '%s'\n", response);
		handleResponse(response, tempNode->pageName, save_dir, queue);


		free(response);

		//printf("charsRead %d, lengthOfResponse %d\n", charsRead, lengthOfResponse);
		tempNode = tempNode->next;
		//break;


	} //queue is empty

	if (write(sock,"Connection Ended", strlen("Connection Ended")) < 0)				//write in socket to close connection
			perror_exit("write");


	close(sock); /* Close socket and exit */
	destroyQueue(queue);
}



char* createGetRequest(char* url, char* host){
	char* getReq = malloc((strlen(url)+strlen(host)+200)*sizeof(char));
	//strcpy(getReq, "hello");
	sprintf(getReq, "GET %s HTTP/1.1\nUser-­Agent: Mozilla/4.0 (compatible;; MSIE5.01;; Windows NT)\nHost: %s\nAccept-­Language: en-­us\nAccept-­Encoding: gzip, deflate\nConnection: Keep-­Alive\n\n", url, host);

	//printf("sizeof req %ld\n",strlen(getReq));
	//printf("str = %s", getReq);

	return getReq;
	
}

void handleResponse(char* response, char* url, char* save_dir, Queue* queue){
	//gets first line for OK
	//gets line for content will start with <!DOCTYPE html>
	//saves it in saveDir
	char* tempResponse= malloc((strlen(response)+1)*sizeof(char));
	strcpy(tempResponse, response);
	char* tempResponse2=tempResponse;

	char* fileName=malloc((strlen(url)+strlen(save_dir)+1)*sizeof(char));
	sprintf(fileName, "%s%s",save_dir, url);
	//printf("fileName %s\n", fileName);
	//printf("in handle Response\n");
	
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
	//printf("PAGE CREATED\n");

	//printf("response '%s'\n", response);
	char* line = strtok (tempResponse,"\n");
	int lineCounter=0;
	while (line != NULL){


		
		/*if(lineCounter==0){
			printf("LINE '%s'\n", line);
			if(strcmp(line,"HTTP/1.1 200 OK")==0){
				printf("ok\n");
			}
			else if(strcmp(line,"HTTP/1.1 404 Not Found")==0){
				printf("Not Found\n");
			}
			else if(strcmp(line,"HTTP/1.1 403 Forbidden")==0){
				printf("Forbidden\n");
			}
			else{
				printf("line '%s'\n", line);
				//free(fileName);
				//perror_exit("what just happened\n");
			}
		}
*/



		//printf("line is '%s'\n",line );

		if((strlen(line)>5 && line[0]=='<' && line[1]=='h' && line[2]=='t' && line[3]=='m' && line[4]=='l' && line[5]=='>') || (strlen(line)>5 && line[0]=='<' && line[1]=='!' && line[2]=='D' && line[3]=='O' && line[4]=='C') ) {
			//printf("line2 is '%s'\n",line );
			fprintf(fp, "%s", line);
			char* remainingLine = strtok(NULL,"");
			//printf("remainingLine '%s'\n", remainingLine);
			if(remainingLine!=NULL)
				fprintf(fp, "%*.*s", (int)strlen(remainingLine)-2, (int)strlen(remainingLine)-2, remainingLine);
			break;
		}

		line = strtok (NULL, "\n");
		lineCounter++;
	}
	//if(line)
	//	free(line);

	getLinksIntoQueue(queue, fp);


	fclose(fp);
	free(fileName);

	free(tempResponse2);
	//exit(1);

}

void createDir(char* pageName, char* save_dir){
	char* tempPageName=malloc((strlen(pageName))*sizeof(char));
	strcpy(tempPageName, pageName+1);	//to avoid '/'

	//printf("tempPageName %s\n", tempPageName);
	char* line=strtok(tempPageName, "/");

	char* dirName=malloc((strlen(line) + strlen(save_dir) +2)*sizeof(char));

	if(save_dir[strlen(save_dir)-1]!='/')
		sprintf(dirName, "%s/%s", save_dir,line);
	else
		sprintf(dirName, "%s%s", save_dir,line);

	//printf("dirName %s\n", dirName);

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