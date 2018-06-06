#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <pthread.h>

#include "pageHandler.h"

void getLinksIntoQueue(ThreadPool* pool, FILE* fp){
	rewind(fp); /* for going to start of file. */

	char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
    	char* linkLine=strstr(line,"<a href=");
        if(linkLine){
        	char* linkLineCopy= malloc((strlen(linkLine)+1)*sizeof(char));
        	strcpy(linkLineCopy, linkLine);
        	char* linkLineCopyForFree=linkLineCopy;

        	char* tag = strtok(linkLineCopy, ">");
        	if(tag==NULL)
        		continue;
        	char* link = strstr(tag, "/");

            pthread_mutex_lock(&(pool->mtxQueue));
            insertInQueue(pool->queue, link);
            pthread_cond_signal(&(pool->cond_nonemptyQueue));
            pthread_mutex_unlock(&(pool->mtxQueue));

        	free(linkLineCopyForFree);

        }
    }
    if(line)
    	free(line);	
}