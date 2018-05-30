#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

#include "queue.h"

Queue* createQueue(){
	Queue* queue=malloc(sizeof(Queue));
	queue->firstNode = NULL;
	queue->lastNode = NULL;
	queue->size = 0;
    return queue;
}

void initializeQueueNode(QueueNode* node, char* pageName){
	node->pageName=malloc((strlen(pageName)+1)*sizeof(char));
	strcpy(node->pageName, pageName);
	node->next=NULL;

}

char* getFixedPageName(char* fullPageName){
	char* ret = strstr(fullPageName, "/site");

   	return ret;

}

void insertInQueue(Queue* queue, char* pageName){
	 
	 char* fixedPageName=getFixedPageName(pageName);

	 if(queue->firstNode==NULL){
	 	queue->firstNode=malloc(sizeof(QueueNode));
	 	initializeQueueNode(queue->firstNode, fixedPageName);
	 	queue->lastNode=queue->firstNode;
	 	queue->size++;
	 	return;
	 }
	 if(!checkIfPageExists(queue, fixedPageName)){	//must insert page
	 	queue->lastNode->next=malloc(sizeof(QueueNode));
	 	initializeQueueNode(queue->lastNode->next, fixedPageName);
	 	queue->lastNode=queue->lastNode->next;
	 	queue->size++;
	 	return;
	 }

}

void deleteFromQueue(Queue* queue){
	if(queue->firstNode==NULL)
		return;

	QueueNode* tempNode=queue->firstNode;
	queue->firstNode=queue->firstNode->next;
	destroyQueueNode(tempNode); 
	queue->size--;
}

bool checkIfPageExists(Queue* queue, char* pageName){
	QueueNode* tempNode=queue->firstNode;
	while(tempNode!=NULL){
		if(!strcmp(tempNode->pageName, pageName)){
			return true;
		}
		tempNode=tempNode->next;
	}
	return false;
}

void printQueue(Queue* queue){
	QueueNode* tempNode=queue->firstNode;
	while(tempNode!=NULL){
		printf("node page = '%s'\n", tempNode->pageName);
		tempNode=tempNode->next;
	}
}

void destroyQueueNode(QueueNode* node){
	if(node==NULL)
		return;

	free(node->pageName);
	free(node);
}

void destroyQueue(Queue* queue){
	QueueNode* tempNode=queue->firstNode;
	while(tempNode!=NULL){
		deleteFromQueue(queue);
		tempNode=queue->firstNode;
	}
	free(queue);
}
