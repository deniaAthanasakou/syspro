#ifndef _PROCESS_H_
#define _PROCESS_H_
#include "pathStruct.h"

typedef struct ProcessNode{		
	pid_t pid;				//process id		
	PathStruct* paths;		//paths of input files	
}ProcessNode;

typedef struct ProcessStruct{		
	int length;					//is given
	ProcessNode* processes; 
	int position;				//position of first empty element
}ProcessStruct;



ProcessStruct* createProcessStruct(int numOfProcesses);
void initializeProcessNode(ProcessNode* node);

ProcessNode* binarySearchIdfForInsertProcessPath(ProcessNode* array, int id, int first, int last, int realLast);
void insertPathIntoProcessStruct(ProcessStruct* procStr, pid_t id, char* path);

int binarySearchForInsertProcessId(ProcessNode* array, int id, int first, int last, int realLast);
void insertIdIntoProcessStruct(ProcessStruct* procStr, pid_t id);

void printProcessStruct(ProcessStruct* procStr);
//void doubleProcessArray(ProcessStruct* procStr);
//void reduceProcessArrayLength(ProcessStruct* procStr);
void destroyProcessStruct(ProcessStruct* procStr);





#endif
