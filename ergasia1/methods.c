#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methods.h"


int initialize(FILE* file, Map* map){
	char *line = NULL;
	size_t len = 0;
	int read;
	if (file == NULL){
		printf("Error! Null file was given\n");
		return 0;
	}
	int counter=0;	
	while ((read = getline(&line, &len, file)) != -1) {
		int lineNumber = atoi(strtok(line," \t"));
		if(lineNumber!=counter){
			printf("Error in numbering file lines\n");
			return 0;
		}
		
		char* remainingLine = strtok(NULL,"\n");
		printf("%d\n", lineNumber);
		printf("'%s'\n", remainingLine);
		
		//inserting lines into map
		char* text = malloc((strlen(remainingLine)+1)* sizeof(char));
		strcpy(text, remainingLine);
		insertIntoMap(map, lineNumber, text);
		
		counter++;		
	}
	printf("map->Length %d, map->position %d\n", map->length, map->position);
	printMap(map);
	reduceMapLength(map);
	printf("map->Length %d, map->position %d\n", map->length, map->position);
	printMap(map);

	if (line){
		free(line);
		line=NULL;
	}
	return 1;
}





