#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "documentIdsHandler.h"


void createDifferentIds(DifferentIds *diffIds){
	diffIds->length=10;
	diffIds->position=0;
	diffIds->ids = malloc(sizeof(int)*diffIds->length);
}

void destroyDifferentIds(DifferentIds *diffIds){
	if(diffIds!=NULL){
		free(diffIds->ids);
		free(diffIds);
		diffIds=NULL;	
	}
}


void doubleDifferentIds(DifferentIds *diffIds){
	diffIds->length*=2;
	diffIds->ids = realloc(diffIds->ids,sizeof(int)*diffIds->length); 
}


void insertionSortDifferentIds(DifferentIds *diffIds, int newId){

}


void binarySearchForDifferentIds(int* ids, int first, int last){

}

void printDifferentIds(DifferentIds* diffIds){
	printf("Printing different ids\n");
	for(int i=0; i<diffIds->position; i++){
		printf("%d\n", diffIds->ids[i]);
	}
}


