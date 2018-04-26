#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postingList.h"

void createPostingList(postingList* pL){
	pL->listSize = 0;
	pL->firstNode = NULL;
}

void insertIntoPostingList(postingList* pL, char* path,  int lineOfWord, int wordOffset){
	postingListNode* node = searchForPath(pL, path);
	if(node==NULL)
		return;
	if(node->filePath==NULL){		//item does not exist
		node->filePath = malloc(sizeof(char)*(strlen(path)+1));
		strcpy(node->filePath, path);
		node->next = NULL;
		pL->listSize++;
	}
	node->occurrences++;
	node->line = lineOfWord;
	node->wordOffset = wordOffset;
}

postingListNode* searchForPath(postingList* pL, char* path){		//is used by function insertIntoPostingList, so that node with same id will not be added twice
	if(pL==NULL)
		return NULL;
	postingListNode* node = pL->firstNode;
	postingListNode* prevNode = pL->firstNode;
	while(node!=NULL){
		if(strcmp(node->filePath, path)==0)
			return node;
		prevNode = node;
		node = node->next;	
	}
	node = malloc(sizeof(postingListNode));
	node->filePath = NULL;
	node->occurrences = 0;
	node->line = -1;
	node->wordOffset = -1;
	node->next = NULL;
	if(prevNode!=NULL){
		prevNode->next = node;
	}
	else
		pL->firstNode = node;
	return node;		
}
/*
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
}*/
/*
void getDifferentIds(postingList* pL, DifferentIds* diffIds){
	OccurrencesInText* tempNode = pL->firstNode;
	while(tempNode!=NULL){
		insertionSortDifferentIds(diffIds, tempNode->textId);
		tempNode = tempNode->next;
	}
}

*/

void printPostingList(postingList* pL){
	printf("Printing Posting List\n");
	postingListNode* tempNode = pL->firstNode;
	int counter=0;
	while(tempNode!=NULL){
		counter++;
		printf("path: %s, occurrences %d line %d offset %d\n", tempNode->filePath, tempNode->occurrences, tempNode->line, tempNode->wordOffset);
		tempNode = tempNode->next;
	}
}

void destroyPostingList(postingList* pL){
	if(pL!=NULL){
		pL->listSize = 0;
		postingListNode* node = pL->firstNode;
		while(node!=NULL){
			postingListNode* tempNode = node;
			free(node->filePath);
			node = node->next;
			free(tempNode);
		}
		free(pL);
		pL=NULL;
	}
}
























