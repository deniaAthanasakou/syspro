#ifndef _PRINT_LOG_H_
#define _PRINT_LOG_H_
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "searchStruct.h"

void printSystemTimeAndQuery(int fileDescr, char* queryType);
void printString(int fileDescr, char* string);
void printPathsFromMap(int fileDescr, Map* map);				//for wc
void printPathsFromInfo(int fileDescr, SearchStruct* info);		//for search

#endif
