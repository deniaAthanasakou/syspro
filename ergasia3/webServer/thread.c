#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h> /* read, write, close */
#include <netdb.h> /* gethostbyaddr */
#include <string.h>
#include <pthread.h> 
#include "thread.h"
#include "errorHandler.h"
#include "socketHandler.h"



ThreadPool* createThreadPool(int numberOfThreads, char* rootDirectory, Stats* stats){

	ThreadPool* pool = malloc(sizeof(ThreadPool));
	pool->start = 0;
    pool->end = -1;
    pool->count = 0;
	pool->numberOfThreads=numberOfThreads;
	pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * numberOfThreads);
    pool->stats=stats;
    pool->rootDirectory=rootDirectory;

    pthread_mutex_init(&(pool->mtxStats), 0);
	pthread_mutex_init(&(pool->mtx), 0);
    pthread_cond_init(&(pool->cond_nonempty), 0);
    pthread_cond_init(&(pool->cond_nonfull), 0);

	/* Start worker threads */
    for(int i = 0; i < pool->numberOfThreads; i++) {
        if(pthread_create(&(pool->threads[i]), NULL, thread_f, (void*) pool) != 0) {		
            destroyThreadPool(pool);
            return NULL;
        }
    }
	
	return pool;
}

void *thread_f(void *argp){ /* Thread function */
	printf("in thread_f\n");

	ThreadPool* pool = (ThreadPool*) argp;
	printf("I am the newly created thread %ld\n", pthread_self());
	printf("my root Dir is %s\n", pool->rootDirectory);
	while(1){

       

		int fd=getFdToThread(pool);
		printf("fd: %d\n", fd);
		pthread_cond_signal(&(pool->cond_nonfull));
		if(readFromSocket(fd, pool->rootDirectory,pool)==0){
			printf("oupsss no more get requests\n");
		}

        printf("in thread%ld\n", pthread_self());
	}

    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!OUT OF WHILE\n");
}




void destroyThreadPool(ThreadPool *pool){
	if(pool==NULL)
		return;


	//must wait for threads
	 /* Join all worker thread */
   for(int i = 0; i < pool->numberOfThreads; i++) {
       // if(pthread_join(pool->threads[i], NULL) != 0) {
        if(pthread_cancel(pool->threads[i]) != 0) {
            perror_exit("pthread_cancel");
        }
        if(pthread_join(pool->threads[i], NULL) != 0) {
            perror_exit("pthread_join");
        }

    }


    pthread_cond_destroy(&(pool->cond_nonempty));
    pthread_cond_destroy(&(pool->cond_nonfull));
    pthread_mutex_destroy(&(pool->mtx));



	free(pool->threads);
    free(pool);
}


void insertFd(ThreadPool* pool, int fd){

	pthread_mutex_lock(&(pool->mtx));
	while (pool->count >= POOL_SIZE) {
	    printf(">> Found Buffer Full \n");
	    pthread_cond_wait(&(pool->cond_nonfull), &(pool->mtx));
    }
    pool->end = (pool->end + 1) % POOL_SIZE;
    pool->fds[pool->end] = fd;

    pool->count++;
    pthread_mutex_unlock(&(pool->mtx));    

}

void printFds(ThreadPool* pool){
	printf("printing fds\n");
	for(int i=0; i<pool->end; i++){
		printf("fd = %d | ", pool->fds[i]);
	}
	printf("\n");
}


int getFdToThread(ThreadPool* pool){

	int fd = 0;
    pthread_mutex_lock(&(pool->mtx));
    while (pool->count <= 0) {
    	printf(">> Found Buffer Empty \n");
    	pthread_cond_wait(&(pool->cond_nonempty), &(pool->mtx));
    }
    fd = pool->fds[pool->start];
    pool->start = (pool->start + 1) % POOL_SIZE;
    pool->count--;
    pthread_mutex_unlock(&(pool->mtx));
    return fd;


}

