#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

#include "queue.h"

Queue* createQueue(){
	Queue* queue=malloc(sizeof(Queue));
	queue->firstNode = NULL;
	queue->lastNode = NULL;

	queue->firstNodeFullQueue = NULL;
	queue->lastNodeFullQueue = NULL;

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
	

	 
	 if(!checkIfPageExists(queue, fixedPageName)){	//must insert page

	 	if(queue->firstNode==NULL){
		 	queue->firstNode=malloc(sizeof(QueueNode));
		 	initializeQueueNode(queue->firstNode, fixedPageName);
		 	queue->lastNode=queue->firstNode;
		 }
		 else{

		 	queue->lastNode->next=malloc(sizeof(QueueNode));
		 	initializeQueueNode(queue->lastNode->next, fixedPageName);
		 	queue->lastNode=queue->lastNode->next;
	 	}
	 	queue->size++;

	 	/*insert in full queue*/
	 	if(queue->firstNodeFullQueue==NULL){
		 	queue->firstNodeFullQueue=malloc(sizeof(QueueNode));
		 	initializeQueueNode(queue->firstNodeFullQueue, fixedPageName);
		 	queue->lastNodeFullQueue=queue->firstNodeFullQueue;
		 }
		 else{
		 	queue->lastNodeFullQueue->next=malloc(sizeof(QueueNode));
		 	initializeQueueNode(queue->lastNodeFullQueue->next, fixedPageName);
	 		queue->lastNodeFullQueue=queue->lastNodeFullQueue->next;
		 }

	 }

}

char* deleteFromQueue(Queue* queue, int returnPage){
	if(queue->firstNode==NULL)
		return NULL;

	QueueNode* tempNode=queue->firstNode;
	char* pageName = NULL;
	if(returnPage){
		pageName=malloc((strlen(tempNode->pageName)+1)*sizeof(char));
		strcpy(pageName, tempNode->pageName);
	}

	queue->firstNode=queue->firstNode->next;
	destroyQueueNode(tempNode); 
	queue->size--;
	return pageName;
}

bool checkIfPageExists(Queue* queue, char* pageName){
	QueueNode* tempNode=queue->firstNodeFullQueue;
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

void printFullQueue(Queue* queue){
	QueueNode* tempNode=queue->firstNodeFullQueue;
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
		deleteFromQueue(queue, 0);
		tempNode=queue->firstNode;
	}

	QueueNode* tempNodeFromFull=queue->firstNodeFullQueue;
	while(tempNodeFromFull!=NULL){
		deleteFromFullQueue(queue);
		tempNodeFromFull=queue->firstNodeFullQueue;
	}
	free(queue);
}

void deleteFromFullQueue(Queue* queue){
	if(queue->firstNodeFullQueue==NULL)
		return;

	QueueNode* tempNode=queue->firstNodeFullQueue;
	queue->firstNodeFullQueue=queue->firstNodeFullQueue->next;
	destroyQueueNode(tempNode); 
}

