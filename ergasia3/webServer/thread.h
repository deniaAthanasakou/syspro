#ifndef _THREAD_H_
#define _THREAD_H_

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
	pthread_mutex_t mtx;
	pthread_cond_t cond_nonempty;
	pthread_cond_t cond_nonfull;
	pthread_mutex_t mtxStats;
	Stats* stats;
	char* rootDirectory;
}ThreadPool;



ThreadPool* createThreadPool(int numberOfThreads, char* rootDirectory, Stats* stats);
void *thread_f(void *argp);

void destroyThreadPool(ThreadPool *pool);
void insertFd(ThreadPool* pool, int fd);
void printFds(ThreadPool* pool);
int getFdToThread(ThreadPool* pool);

#endif
