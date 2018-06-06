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
	if(node->info == NULL){
		node->info = createList();
	}
	insertIntoList(node->info, lineOfWord, wordOffset);
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
	node->next = NULL;
	node->info = NULL;
	if(prevNode!=NULL){
		prevNode->next = node;
	}
	else
		pL->firstNode = node;
	return node;		
}

void printPostingList(postingList* pL){
	printf("Printing Posting List\n");
	postingListNode* tempNode = pL->firstNode;
	while(tempNode!=NULL){
		printf("path: %s, occurrences %d\n", tempNode->filePath, tempNode->occurrences);
		printList(tempNode->info);
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
			destroyList(node->info);
			node = node->next;
			free(tempNode);
		}
		free(pL);
	}
}
























