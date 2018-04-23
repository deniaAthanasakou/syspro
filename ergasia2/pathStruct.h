#ifndef _PATH_STRUCT_H_
#define _PATH_STRUCT_H_


typedef struct PathStruct{		
	int length;					//initially is 5
	char** arrayOfPaths; 		//array of strings
	int position;				//position of first empty element
	int lastNotRead;			//position of last element that has not been read (for fifo)		//na to vgalw
}PathStruct;



PathStruct* createPathStruct();
int initializeFromFile(FILE* file, PathStruct* paths);
void insertIntoPathStruct(PathStruct* paths, char* path);
void printPathStruct(PathStruct* paths);
void doublePathArray(PathStruct* paths);
void reducePathArrayLength(PathStruct* paths);
void destroyPathStruct(PathStruct* paths);
char* getLastPath(PathStruct* paths);	//like pop in lifo											//na to vgalw
#endif
