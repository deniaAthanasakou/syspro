#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"


ProcessStruct* createProcessStruct(){
	ProcessStruct* procStr = malloc(sizeof(ProcessStruct));
	procStr->length = 5;
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
	ProcessNode* node = binarySearchIdfForInsertProcessPath(procStr->processes, id, 0, procStr->position-1, procStr->position-1);
	if(node==NULL)		//id does not exist in array
		return;		
	if(node->paths == NULL){
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

	if(procStr->position==procStr->length){
		doubleProcessArray(procStr);
	}
	
	int j = procStr->position-1;	//position of last element
	// Move all elements after location to create space
	while (j >= loc)
	{
	    procStr->processes[j+1] =  procStr->processes[j];
	    j--;
	}
	procStr->processes[j+1].pid = id;
	procStr->position++;
}

void printProcessStruct(ProcessStruct* procStr){
	printf("Printing processes: length = %d\n", procStr->length);
	for(int i=0; i<procStr->length; i++){
		printf("pid: '%d'\n",procStr->processes[i].pid);
		if(procStr->processes[i].paths->position!=0)
			printPathStruct(procStr->processes[i].paths);
	}
}

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

void destroyProcessStruct(ProcessStruct* procStr){
	if(procStr!=NULL){
		for(int i=0; i<procStr->position; i++){
		printf("i %d\n", i);
			destroyPathStruct(procStr->processes[i].paths);
		}
		free(procStr->processes);
		free(procStr);
	}
}

