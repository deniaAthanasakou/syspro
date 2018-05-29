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
	int size;

}Queue;

Queue* createQueue();
void initializeQueueNode(QueueNode* node, char* pageName);
void insertInQueue(Queue* queue, char* pageName);
void deleteFromQueue(Queue* queue);
bool checkIfPageExists(Queue* queue, char* pageName);
void printQueue(Queue* queue);
void destroyQueueNode(QueueNode* node);
void destroyQueue(Queue* queue);



#endif