#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathStruct.h"

PathStruct* createPathStruct(){
	PathStruct* paths = malloc(sizeof(PathStruct));
	paths->length = 5;
	paths->position = 0;
	paths->arrayOfPaths = malloc(paths->length*sizeof(char*));
	for(int i=0; i<paths->length; i++){
		paths->arrayOfPaths[i] = NULL;
	}
	return paths;
}
 
int initializeFromFile(FILE* file, PathStruct* paths){
	char *line = NULL;
	size_t len = 0;
	int read;
	if (file == NULL){
		printf("Error! Null file was given.\n");
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
		free(text);
		text=NULL;
	}
	reducePathArrayLength(paths);

	if (line){
		free(line);
		line=NULL;
	}
	return 1;
}
 
void insertIntoPathStruct(PathStruct* paths, char* path){
	if(pathAlreadyExists(paths, path)){					//don't insert
		return;
	}
	if(paths->position==paths->length){
		doublePathArray(paths);
	}
	paths->arrayOfPaths[paths->position] = malloc((strlen(path)+1)*sizeof(char));
	strcpy(paths->arrayOfPaths[paths->position], path);
	paths->position++;
}
 
void printPathStruct(PathStruct* paths){
	printf("Printing paths: pos = %d\n", paths->position);
	for(int i=0; i<paths->position; i++){
		printf("path: '%s'\n",paths->arrayOfPaths[i]);
	}

}
 
void doublePathArray(PathStruct* paths){
	int oldLength = paths->length;
	paths->length*=2;
	paths->arrayOfPaths = (char**)realloc(paths->arrayOfPaths, paths->length*sizeof(char*));
	for(int i=oldLength; i<paths->length; i++){
		paths->arrayOfPaths[i] = NULL;
	}
}
 
void reducePathArrayLength(PathStruct* paths){				
	paths->arrayOfPaths = (char**)realloc(paths->arrayOfPaths, paths->position*sizeof(char*));
	paths->length = paths->position;
}

 
bool pathAlreadyExists(PathStruct* paths, char* path){
	for(int i=0; i<paths->position; i++){
		if(strcmp(path, paths->arrayOfPaths[i])==0)
			return true;
	}
	return false;
} 
 
void destroyPathStruct(PathStruct* paths){
	if(paths!=NULL){
		for(int i=0; i<paths->position; i++){
			free(paths->arrayOfPaths[i]);
		}
		if(paths->position>0)
			free(paths->arrayOfPaths);
		free(paths);
	}
}

