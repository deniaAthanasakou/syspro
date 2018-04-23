#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"


ProcessStruct* createProcessStruct(int numOfProcesses){
	ProcessStruct* procStr = malloc(sizeof(ProcessStruct));
	procStr->length = numOfProcesses;
	procStr->position = 0;
	procStr->processes = malloc(procStr->length*sizeof(ProcessNode));
	for(int i=0; i<procStr->length; i++){
		initializeProcessNode(&procStr->processes[i]);
	}
	return procStr;
}

void initializeProcessNode(ProcessNode* node){
	node->pid = -1;
	node->paths = NULL;//createPathStruct();
}

ProcessNode* binarySearchIdfForInsertProcessPath(ProcessNode* array, int id, int first, int last, int realLast){
	if(realLast==-1)	//there are no elements in array
		return NULL;
	if (last <= first){
		if(array[first].pid == id){		//item found
			return &array[first];	
		}
        else 
        	return NULL;
    }
    int mid = (first + last)/2;
 
    if(array[mid].pid == id)		//item found
    	return &array[mid];
 
    if(array[mid].pid < id)
        return binarySearchIdfForInsertProcessPath(array, id, mid+1, last, realLast);
    return binarySearchIdfForInsertProcessPath(array, id, first, mid-1, realLast);
}

void insertPathIntoProcessStruct(ProcessStruct* procStr, pid_t id, char* path){
	// find location where path sould be inserted
	//printf("id = %d\n", id);
	ProcessNode* node = binarySearchIdfForInsertProcessPath(procStr->processes, id, 0, procStr->position-1, procStr->position-1);
	if(node==NULL){		//id does not exist in array
	//	printf("null node\n");
		return;		
	}
	//printf("id2 = %d\n", node->pid);
	if(node->paths == NULL){
		//printf("paths were null word is %s\n", path);
		node->paths = createPathStruct();
	}
	insertIntoPathStruct(node->paths, path);
}

int binarySearchForInsertProcessId(ProcessNode* array, int id, int first, int last, int realLast){
	if(realLast==-1)	//there are no elements in array
		return 0;
	if (last <= first){
		if(array[first].pid == id)		//item already exists
			return -1;	
        return (array[first].pid < id)?  (first + 1): first;
    }
 
    int mid = (first + last)/2;
 
    if(array[mid].pid == id)		//item already exists
    	return -1;
 
    if(array[mid].pid < id)
        return binarySearchForInsertProcessId(array, id, mid+1, last, realLast);
    return binarySearchForInsertProcessId(array, id, first, mid-1, realLast);
}

void insertIdIntoProcessStruct(ProcessStruct* procStr, pid_t id){
	// find location where element sould be inserted
	int loc = binarySearchForInsertProcessId(procStr->processes, id, 0, procStr->position-1, procStr->position-1);
	if(loc==-1)		//item already exists in array
		return;		
	
	int j = procStr->position-1;	//position of last element
	// Move all elements after location to create space
	/*while (j >= loc)
	{
	    procStr->processes[j+1] =  procStr->processes[j];
	    j--;
	}
	procStr->processes[j+1].pid = id;
	procStr->processes[j+1].paths = NULL;
	
	*/
	
	int lastElement = procStr->position;
	ProcessNode* itemForInsert = malloc(sizeof(ProcessNode));
	itemForInsert->pid = id;
	itemForInsert->paths = NULL;
	
	
	int fullMoveSize=0;
	int startingPoint = loc;	
	if( j>=loc){
	
		fullMoveSize = (lastElement -loc)*sizeof(procStr->processes[lastElement - 1]);
		memmove(&(procStr->processes[startingPoint+1]), &(procStr->processes[startingPoint]), fullMoveSize);
		memmove(&(procStr->processes[loc]), itemForInsert, sizeof(*itemForInsert));
	}
	else{
		memmove(&(procStr->processes[lastElement]), itemForInsert, sizeof(*itemForInsert));
	}	
	
	free(itemForInsert);
	
	procStr->position++;
	
	
	
}

void printProcessStruct(ProcessStruct* procStr){
	printf("Printing processes: pos = %d\n", procStr->position);
	for(int i=0; i<procStr->position; i++){
		printf("pid: '%d'\n",procStr->processes[i].pid);
		if(procStr->processes[i].paths!=NULL)
			printPathStruct(procStr->processes[i].paths);
	}
}
/*
void doubleProcessArray(ProcessStruct* procStr){
	int oldLength = procStr->length;
	procStr->length*=2;
	procStr->processes = (ProcessNode*)realloc(procStr->processes, procStr->length*sizeof(ProcessNode));
	for(int i=oldLength; i<procStr->length; i++){
		initializeProcessNode(&procStr->processes[i]);
	}
}

void reduceProcessArrayLength(ProcessStruct* procStr){
	procStr->processes = (ProcessNode*)realloc(procStr->processes, procStr->position*sizeof(ProcessNode));
	procStr->length = procStr->position;
}
*/
void destroyProcessStruct(ProcessStruct* procStr){
	if(procStr!=NULL){
		for(int i=0; i<procStr->length; i++){
			//printf("i %d\n", i);
			destroyPathStruct(procStr->processes[i].paths);
		}
		free(procStr->processes);
		free(procStr);
	}
}

