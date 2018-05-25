#ifndef _GET_PAGES_H_
#define _GET_PAGES_H_

char* createGetRequest(char* url, char* host);
void connectToServer(int port, int commandPort, char* host_or_IP, char* startingURL);


#endif