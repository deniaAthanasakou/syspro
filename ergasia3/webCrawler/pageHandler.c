#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

#include "pageHandler.h"

void getLinksIntoQueue(Queue* queue, FILE* fp){
	//printf("get Links into queue\n");
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
        	//printf("link '%s'\n" , link);

        	insertInQueue(queue, link);

        	free(linkLineCopyForFree);

        }
    }
    if(line)
    	free(line);
  //  printQueue(queue);
	
}