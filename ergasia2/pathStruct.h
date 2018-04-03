#ifndef _PATH_STRUCT_H_
#define _PATH_STRUCT_H_


typedef struct PathStruct{		
	int length;					//initially is 5
	char** arrayOfPaths; 
	int position;				//position of first empty element
}PathStruct;



PathStruct* createPathStruct();
int initializeFromFile(FILE* file, PathStruct* paths);
void insertIntoPathStruct(PathStruct* paths, char* path);
void printPathStruct(PathStruct* paths);
void doubleArray(PathStruct* paths);
void reduceArrayLength(PathStruct* paths);
void destroyPathStruct(PathStruct* paths);

#endif
