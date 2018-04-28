#ifndef _PROCESS_H_
#define _PROCESS_H_
#include  <sys/types.h>
#include  <sys/stat.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pathStruct.h"

#define MAXBUFF 1024
#define PERMS   0666
extern int errno;


int server(int readfd, int writefd, char* line);

int client(int readfd, int writefd);

#endif
