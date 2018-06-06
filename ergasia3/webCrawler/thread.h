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
int fds[POOL_SIZE];					//array of fds
int start;				
int end;
int count;			
int numberOfThreads;
pthread_mutex_t mtxFd;
pthread_cond_t cond_nonempty;
pthread_cond_t cond_nonfull;
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
void insertFd(ThreadPool* pool, int fd);
void printFds(ThreadPool* pool);
int getFdToThread(ThreadPool* pool);

#endif
