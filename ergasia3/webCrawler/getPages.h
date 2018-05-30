#ifndef _GET_PAGES_H_
#define _GET_PAGES_H_
#include <stdbool.h>
#include "queue.h"


char* createGetRequest(char* url, char* host);
void connectToServer(int port, int commandPort, char* host_or_IP, char* startingURL, char* save_dir);
void handleResponse(char* response, char* url, char* save_dir, Queue* queue);
void createDir(char* pageName, char* save_dir);
bool file_exists(const char * filename);


#endif