#ifndef _GET_PAGES_H_
#define _GET_PAGES_H_
#include <stdbool.h>
#include <sys/timeb.h>

#include "queue.h"

typedef struct Stats{
	int pagesServed;
	long int bytes;
}Stats;


void connectToServer(int port, int commandPort, char* host_or_IP, char* startingURL, char* save_dir, struct timeb* begin);
char* createGetRequest(char* url, char* host);
void handleResponse(char* response, char* url, char* save_dir, Queue* queue, Stats* stats);
void createDir(char* pageName, char* save_dir);
bool file_exists(const char * filename);

void initializeStats(Stats* stats);

char* timeToString(struct timeb* begin,  struct timeb* end);

#endif