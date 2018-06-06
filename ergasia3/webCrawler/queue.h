#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>

typedef struct QueueNode QueueNode;

struct QueueNode{
	char* pageName;
	QueueNode* next;

};

typedef struct Queue{
	QueueNode* firstNode;
	QueueNode* lastNode;

	QueueNode* firstNodeFullQueue;			//no links will be deleted from here
	QueueNode* lastNodeFullQueue;

	int size;

}Queue;

Queue* createQueue();
void initializeQueueNode(QueueNode* node, char* pageName);
char* getFixedPageName(char* fullPageName);
void insertInQueue(Queue* queue, char* pageName);
char* deleteFromQueue(Queue* queue, int returnPage);
bool checkIfPageExists(Queue* queue, char* pageName);
void printQueue(Queue* queue);
void printFullQueue(Queue* queue);
void destroyQueueNode(QueueNode* node);
void destroyQueue(Queue* queue);
void deleteFromFullQueue(Queue* queue);


#endif