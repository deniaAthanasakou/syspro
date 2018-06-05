#ifndef _SOCKET_HANDLER_H_
#define _SOCKET_HANDLER_H_
#include <sys/timeb.h>
#include "thread.h"


void createSocket(int servingPort, int commandPort, char* rootDirectory, struct timeb* begin, int numThreads);
int readFromSocket(int newSocket, char* rootDirectory, ThreadPool* pool);
char* getResponse(char* firstFline, int contentLength, char* content);
char* handleRequest(char* req, char* rootDirectory, ThreadPool* pool);
char* checkGETLine(char* GETLine);
int checkHostLine(char* HostLine);
char* getResponseForBadRequest();

void initializeStats(Stats* stats);

char* timeToString(struct timeb* begin,  struct timeb* end);
#endif