#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathStruct.h"

PathStruct* createPathStruct(){
	PathStruct* paths = malloc(sizeof(PathStruct));
	paths->length = 5;
	paths->position = 0;
	paths->arrayOfPaths = malloc(paths->length*sizeof(char*));
	return paths;
}
 
int initializeFromFile(FILE* file, PathStruct* paths){
	char *line = NULL;
	size_t len = 0;
	int read;
	if (file == NULL){
		printf("Error! Null file was given\n");
		return 0;
	}
	while ((read = getline(&line, &len, file)) != -1) {
		if(!strcmp(line, "\n")){	
			continue;
		}
		char* tempLine = strtok(line,"\n");
		
		
		//inserting lines into PathStruct
		char* text = malloc((strlen(tempLine)+1)* sizeof(char));
		strcpy(text, tempLine);
		insertIntoPathStruct(paths, text);
	}
	reducePathArrayLength(paths);

	if (line){
		free(line);
		line=NULL;
	}
	return 1;
}
 
void insertIntoPathStruct(PathStruct* paths, char* path){
	if(paths->position==paths->length){
		doublePathArray(paths);
	}
	paths->arrayOfPaths[paths->position] = malloc((strlen(path)+1)*sizeof(char));
	strcpy(paths->arrayOfPaths[paths->position], path);
	paths->position++;
}
 
void printPathStruct(PathStruct* paths){
	printf("Printing paths: length = %d\n", paths->length);
	for(int i=0; i<paths->length; i++){
		printf("path: '%s'\n",paths->arrayOfPaths[i]);
	}
}
 
void doublePathArray(PathStruct* paths){
	paths->length*=2;
	paths->arrayOfPaths = (char**)realloc(paths->arrayOfPaths, paths->length*sizeof(char*));
}
 
void reducePathArrayLength(PathStruct* paths){
	paths->arrayOfPaths = (char**)realloc(paths->arrayOfPaths, paths->position*sizeof(char*));
	paths->length = paths->position;
}
 
void destroyPathStruct(PathStruct* paths){
	if(paths!=NULL){
		printf("position %d\n", paths->position);
		for(int i=0; i<paths->position; i++){
			printf("path i %d\n", i);
			free(paths->arrayOfPaths[i]);
			printf("after\n");
		}
		printf("before paths->arrayOfPaths\n");
		if(paths->position>0)
			free(paths->arrayOfPaths);
		printf("after paths->arrayOfPaths\n");
		free(paths);
	}
}

