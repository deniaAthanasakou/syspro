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
	
	if(diffIds->position==diffIds->length){	//double array
		doubleDifferentIds(diffIds);
	}

	// find location where element sould be inseretd
	int loc = binarySearchForDifferentIds(diffIds->ids, newId, 0, diffIds->position-1, diffIds->position-1);
	if(loc==-1)		//item already exists in array
		return;		


	int j = diffIds->position-1;	//position of last element
	// Move all elements after location to create space
	while (j >= loc)
	{
	    diffIds->ids[j+1] = diffIds->ids[j];
	    j--;
	}
	diffIds->ids[j+1] = newId;

	
	diffIds->position++;
    
}


int binarySearchForDifferentIds(int* ids, int item, int first, int last, int realLastElement){
	if(realLastElement==-1)	//there are no elements in array
		return 0;
	if (last <= first){
		if(item == ids[first])		//item already exists
			return -1;	
        return (item > ids[first])?  (first + 1): first;
    }
 
    int mid = (first + last)/2;
 
    if(item == ids[mid])		//item already exists
    	return -1;
 
    if(item > ids[mid])
        return binarySearchForDifferentIds(ids, item, mid+1, last, realLastElement);
    return binarySearchForDifferentIds(ids, item, first, mid-1, realLastElement);
}

void printDifferentIds(DifferentIds* diffIds){
	printf("Printing different ids\n");
	for(int i=0; i<diffIds->position; i++){
		printf("%d\n", diffIds->ids[i]);
	}
}


