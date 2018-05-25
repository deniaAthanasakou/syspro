#ifndef _SOCKET_HANDLER_H_
#define _SOCKET_HANDLER_H_

void createSocket(int servingPort, int commandPort);
void readFromSocket(int newSocket);
char* getResponce(char* firstFline, int contentLength, char* content);

#endif