#ifndef _THREAD_H_
#define _THREAD_H_
#include "queue.h"

#define POOL_SIZE 10

typedef struct Stats{
	int pagesServed;
	long int bytes;
}Stats;

typedef struct ThreadPool{
	pthread_t *threads;					//array of threads	
	int numberOfThreads;
	pthread_cond_t cond_nonemptyQueue;
	pthread_mutex_t mtxQueue;
	Queue* queue;
	pthread_mutex_t mtxContinueWorking;
	int continueWorking;
	pthread_mutex_t mtxStats;
	char* save_dir;
	Stats* stats;
	char* host_or_IP;
	struct sockaddr *serverptr;
}ThreadPool;


ThreadPool* createThreadPool(int numberOfThread, char* save_dir, Stats* stats, char* host_or_IP, Queue* queue, char* startingUrl, struct sockaddr *serverptr);
void *thread_f(void *argp);

void destroyThreadPool(ThreadPool *pool);

#endif
