#ifndef _PATH_STRUCT_H_
#define _PATH_STRUCT_H_
#include <stdbool.h>


typedef struct PathStruct{		
	int length;					//initially is 5
	char** arrayOfPaths; 		//array of strings
	int position;				//position of first empty element
}PathStruct;



PathStruct* createPathStruct();
int initializeFromFile(FILE* file, PathStruct* paths);
void insertIntoPathStruct(PathStruct* paths, char* path);
void printPathStruct(PathStruct* paths);
void doublePathArray(PathStruct* paths);
void reducePathArrayLength(PathStruct* paths);
void destroyPathStruct(PathStruct* paths);
bool pathAlreadyExists(PathStruct* paths, char* path);
#endif
