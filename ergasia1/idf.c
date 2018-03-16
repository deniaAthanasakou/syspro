#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "idf.h"

void initializeIdfForWords(IdfForWords* idfForWords, int length){
	idfForWords->length = length;
	idfForWords->position = 0;
	idfForWords->array = malloc(idfForWords->length*sizeof(IdfForWordNode));
	for(int i=0; i<idfForWords->length; i++){
		initializeIdfForWordNode(&(idfForWords->array[i]));
	}
}

void initializeIdfForWordNode(IdfForWordNode* node){
	node->idf = 0.0;
	node->word = NULL;
}

IdfForWordNode* binarySearchIdfForWord(IdfForWordNode* array, char* word, int first, int last, int realLast){
	if(realLast==-1)	//there are no elements in array
		return NULL;
	if (last <= first){
		if(strcmp(word, array[first].word)==0)		//item already exists
			return &array[first];	
        else 
        	return NULL;
    }
 
    int mid = (first + last)/2;
 
    if(strcmp(word, array[mid].word)==0)		//item found
    	return &array[mid];
 
    if(strcmp(word, array[mid].word)>0)
        return binarySearchIdfForWord(array, word, mid+1, last, realLast);
    return binarySearchIdfForWord(array, word, first, mid-1, realLast);
}

int binaryIdfForWord(IdfForWordNode* array, char* word, int first, int last, int realLast){
	if(realLast==-1)	//there are no elements in array
		return 0;
	if (last <= first){
		if(strcmp(word, array[first].word)==0)		//item already exists
			return -1;	
        return (strcmp(word, array[first].word)>0)?  (first + 1): first;
    }
 
    int mid = (first + last)/2;
 
    if(strcmp(word, array[mid].word)==0)		//item already exists
    	return -1;
        // mid+1;
 
    if(strcmp(word, array[mid].word)>0)
        return binaryIdfForWord(array, word, mid+1, last, realLast);
    return binaryIdfForWord(array, word, first, mid-1, realLast);
}


void insertionSortIdfForWords(IdfForWords* idfForWords, double idf, char* word){

	// find location where element sould be inserted
	int loc = binaryIdfForWord(idfForWords->array, word, 0, idfForWords->position-1, idfForWords->position-1);
	if(loc==-1)		//item already exists in array
		return;		


	int j = idfForWords->position-1;	//position of last element
	// Move all elements after location to create space
	while (j >= loc)
	{
	    idfForWords->array[j+1] = idfForWords->array[j];
	    j--;
	}
	idfForWords->array[j+1].idf = idf;
	idfForWords->array[j+1].word = word;

	
	idfForWords->position++;
    
}


void deleteIdfForWords(IdfForWords* idfForWords){
	free(idfForWords->array);
	free(idfForWords);
	idfForWords = NULL;
}

void printIdfForWordsElements(IdfForWords* idfForWords){
	printf("Printing IdfForWords\n");
	for(int i=0; i<idfForWords->position; i++){
		printf("WORD '%s', IDF '%f'\n", idfForWords->array[i].word, idfForWords->array[i].idf);
	}
}

