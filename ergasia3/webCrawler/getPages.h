#ifndef _GET_PAGES_H_
#define _GET_PAGES_H_
#include <stdbool.h>

char* createGetRequest(char* url, char* host);
void connectToServer(int port, int commandPort, char* host_or_IP, char* startingURL, char* save_dir);
void handleResponse(char* response, char* url, char* save_dir);
void createDir(char* pageName, char* save_dir);
bool file_exists(const char * filename);


#endif