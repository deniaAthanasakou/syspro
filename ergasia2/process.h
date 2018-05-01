#ifndef _PROCESS_H_
#define _PROCESS_H_
#include  <sys/types.h>
#include  <sys/stat.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

#define MAXBUFF 1024
extern int errno;


typedef struct FIFOS{
	int readfd;			//server reads
	int writefd;		//server writes
}FIFOS;

int server(FIFOS* fifosUsed, int numWorkers, char* queryLine);

int client(int readfd, int writefd, ContainsTrie* containsTrie, int logFile);

#endif
