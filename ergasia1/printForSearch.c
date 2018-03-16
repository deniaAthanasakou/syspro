#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printForSearch.h"

void initializePrintForSearch(PrintForSearch* pfs){
	pfs->length = 10;
	pfs->position = 0;
	pfs->array = malloc(pfs->length * sizeof(PrintForSearchNode));
	for(int i=0; i<pfs->length ; i++){
		initializePrintForSearchNode(&(pfs->array[i]));
	}
}

void initializePrintForSearchNode(PrintForSearchNode* node){
	node->textId = -1;
	node->score = -1.0;
	node->text = NULL;
	
}

void doublePrintForSearch(PrintForSearch* pfs){
	int oldLength = pfs->length;
	pfs->length*=2;
	pfs->array = realloc(pfs->array,sizeof(PrintForSearchNode)*pfs->length);
	for(int i=oldLength; i<pfs->length ; i++){
		initializePrintForSearchNode(&(pfs->array[i]));
	} 
}

int binaryPrintForSearch(PrintForSearchNode* array, double score, int first, int last, int realLastElement){
	if(realLastElement==-1)	//there are no elements in array
		return 0;
	if (last <= first){
		if(score == array[first].score)		//item already exists
			return -1;	
        return (score >array[first].score)?  (first + 1): first;
    }
 
    int mid = (first + last)/2;
 
    if(score == array[mid].score)		//item already exists
    	return -1;
        // mid+1;
 
    if(score > array[mid].score)
        return binaryPrintForSearch(array, score, mid+1, last, realLastElement);
    return binaryPrintForSearch(array, score, first, mid-1, realLastElement);
}

void insertionSortPrintForSearch(PrintForSearch* pfs, int textId, double score, char* text){
	if(pfs->position==pfs->length){	//double array
		doublePrintForSearch(pfs);
	}
	
	

	// find location where selected sould be inseretd
	int loc = binaryPrintForSearch(pfs->array, score, 0, pfs->position-1, pfs->position-1);
	if(loc==-1)		//item already exists in array
		return;		


	int j = pfs->position-1;	//position of last element
	// Move all elements after location to create space
	while (j >= loc)
	{
	   pfs->array[j+1] = pfs->array[j];
	    j--;
	}
    
	pfs->array[j+1].textId = textId;
	pfs->array[j+1].score = score;
	pfs->array[j+1].text = text;		//must not be deleted
	pfs->position++;
}

void deletePrintForSearch(PrintForSearch* pfs){
	free(pfs->array);
	free(pfs);
	pfs = NULL;
}
void printPrintForSearchElements(PrintForSearch* pfs){
	printf("Printing PrintForSearch\n");
	for(int i=0; i<pfs->position; i++){
		printf("TEXT ID '%d', SCORE '%f', TEXT '%s'\n", pfs->array[i].textId, pfs->array[i].score, pfs->array[i].text);
	}
}
