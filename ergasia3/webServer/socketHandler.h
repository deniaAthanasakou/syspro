#ifndef _SOCKET_HANDLER_H_
#define _SOCKET_HANDLER_H_

void createSocket(int servingPort, int commandPort, char* rootDirectory);
int readFromSocket(int newSocket, char* rootDirectory);
char* getResponse(char* firstFline, int contentLength, char* content);
char* handleRequest(char* req, char* rootDirectory);
char* checkGETLine(char* GETLine);
int checkHostLine(char* HostLine);
char* getResponseForBadRequest();

#endif