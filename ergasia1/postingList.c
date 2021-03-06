#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postingList.h"

void createPostingList(postingList* pL){
	pL->documentFreq = 0;
	pL->firstNode = NULL;
}

void insertIntoPostingList(postingList* pL, int textId){
	OccurrencesInText* node = searchForId(pL, textId);
	if(node==NULL)
		return;
	if(node->textId==-1){		//item does not exist
		node->textId = textId;
		node->next = NULL;
		pL->documentFreq++;
	}
	node->occurrences++;
}

OccurrencesInText* searchForId(postingList* pL, int id){		//is used by function insertIntoPostingList, so that node with same id will not be added twice
	if(pL==NULL)
		return NULL;
	OccurrencesInText* node = pL->firstNode;
	OccurrencesInText* prevNode = pL->firstNode;
	while(node!=NULL){
		if(node->textId == id)
			return node;
		prevNode = node;
		node = node->next;	
	}
	node = malloc(sizeof(OccurrencesInText));
	node->textId = -1;
	node->occurrences = 0;
	node->next = NULL;
	if(prevNode!=NULL){
		prevNode->next = node;
	}
	else
		pL->firstNode = node;
	return node;		
}

OccurrencesInText* getNodeById(postingList* pL,int id){
	if(pL==NULL)
		return NULL;
	OccurrencesInText* node = pL->firstNode;
	while(node!=NULL){
		if(node->textId == id)
			return node;
	
		node = node->next;	
	}
	
	return NULL;		
}

void getDifferentIds(postingList* pL, DifferentIds* diffIds){
	OccurrencesInText* tempNode = pL->firstNode;
	while(tempNode!=NULL){
		insertionSortDifferentIds(diffIds, tempNode->textId);
		tempNode = tempNode->next;
	}
}



void printPostingList(postingList* pL){
	printf("Printing Posting List\n");
	OccurrencesInText* tempNode = pL->firstNode;
	int counter=0;
	while(tempNode!=NULL){
		counter++;
		printf("id: %d, occurrences %d\n", tempNode->textId, tempNode->occurrences);
		tempNode = tempNode->next;
	}
}

void destroyPostingList(postingList* pL){
	if(pL!=NULL){
		pL->documentFreq = 0;
		OccurrencesInText* node = pL->firstNode;
		while(node!=NULL){
			OccurrencesInText* tempNode = node;
			node = node->next;
			free(tempNode);
		}
		free(pL);
		pL=NULL;
	}
}
























