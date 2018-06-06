#ifndef _GET_PAGES_H_
#define _GET_PAGES_H_
#include <stdbool.h>
#include <sys/timeb.h>
#include "thread.h"

#include "queue.h"

void connectToServer(int port, int commandPort, char* host_or_IP, char* startingURL, char* save_dir, int numThreads, struct timeb* begin);
void readWriteInSocket(int sock, char* save_dir, Stats* stats, char* pageName, char* host_or_IP, ThreadPool* pool, int endFlag);
char* createGetRequest(char* url, char* host);
void handleResponse(char* response, char* url, char* save_dir, ThreadPool* pool, Stats* stats);
void createDir(char* pageName, char* save_dir);
bool file_exists(const char * filename);

void initializeStats(Stats* stats);
char* timeToString(struct timeb* begin,  struct timeb* end);

#endif