#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

List* createList(){
	List* l = malloc(sizeof(List));
	l->listSize = 0;
	l->firstNode = NULL;
	return l;
}

void insertIntoList(List* l,  int lineOfWord, int wordOffset){

	ListNode* nodeToInsert = malloc(sizeof(ListNode));
	nodeToInsert->lineOfText = lineOfWord;
	nodeToInsert->wordOffset = wordOffset;

	ListNode* tempNode = l->firstNode;
	if(l->firstNode==NULL){
		l->firstNode = nodeToInsert;
		l->firstNode->next = NULL;
	}
	else{
		while(tempNode->next!=NULL){
			tempNode = tempNode->next;			
		}
		tempNode->next = nodeToInsert;			//insert into first Null Element
		tempNode->next->next = NULL;
	}
	
	l->listSize++;
	
}


void printList(List* l){
	printf("Printing List\n");
	ListNode* tempNode = l->firstNode;
	while(tempNode!=NULL){

		printf("line %d offset %d\n", tempNode->lineOfText, tempNode->wordOffset);
		tempNode = tempNode->next;
	}
}

void destroyList(List* l){
	if(l!=NULL){
		l->listSize = 0;
		ListNode* node = l->firstNode;
		while(node!=NULL){
			ListNode* tempNode = node;
			node = node->next;
			free(tempNode);
		}
		free(l);
	}
}

