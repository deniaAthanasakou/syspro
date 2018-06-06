#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>  // for open
#include <unistd.h> // for close
#include "printLog.h"


void printSystemTimeAndQuery(int fileDescr, char* queryType){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	char time[50];
	sprintf(time,"%d-%d-%d %d:%d:%d : ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	write(fileDescr, time, strlen(time));
	if(queryType[0]=='/' || queryType[0]=='\\'){
		memmove(queryType, queryType+1, strlen(queryType));
	}
	write(fileDescr, queryType, strlen(queryType));
}

void printString(int fileDescr, char* string){		//for query string or pathnames
	write(fileDescr, " : ", strlen(" : "));
	write(fileDescr, string, strlen(string));
}

void printPathsFromMap(int fileDescr, Map* map){		//for wc
	for(int i=0; i<map->position; i++){
		write(fileDescr, " : ", strlen(" : "));
		write(fileDescr, map->array[i].fileName, strlen(map->array[i].fileName));
	}
}

void printPathsFromInfo(int fileDescr, SearchStruct* info){			//for search
	for(int i=0; i<info->position; i++){
		printString(fileDescr, info->array[i].fileName);
	}
}
