#ifndef _SOCKET_HANDLER_H_
#define _SOCKET_HANDLER_H_

typedef struct Stats{
	int pagesServed;
	long int bytes;
}Stats;


void createSocket(int servingPort, int commandPort, char* rootDirectory, int numOfThreads, struct timeval* begin);
int readFromSocket(int newSocket, char* rootDirectory, Stats* stats);
char* getResponse(char* firstFline, int contentLength, char* content);
char* handleRequest(char* req, char* rootDirectory, Stats* stats);
char* checkGETLine(char* GETLine);
int checkHostLine(char* HostLine);
char* getResponseForBadRequest();
void initializeStats(Stats* stats);

#endif