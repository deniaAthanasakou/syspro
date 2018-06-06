#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* internet sockets */
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h> /* read, write, close */
#include <netdb.h> /* gethostbyaddr */
#include <unistd.h>
#include "thread.h"
#include "errorHandler.h"
#include "errorHandler.h"
#include "getPages.h"

ThreadPool* createThreadPool(int numberOfThreads, char* save_dir, Stats* stats, char* host_or_IP, Queue* queue, char* startingUrl, struct sockaddr *serverptr){

    ThreadPool* pool = malloc(sizeof(ThreadPool));
    pool->numberOfThreads=numberOfThreads;
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * numberOfThreads);
    pool->queue=queue;

    pool->stats=stats;
    pool->save_dir=save_dir;
    pool->host_or_IP=host_or_IP;
    pool->serverptr = serverptr;
    pool->continueWorking = 1;

    pthread_mutex_init(&(pool->mtxQueue), 0);
    pthread_cond_init(&(pool->cond_nonemptyQueue), 0);
    pthread_mutex_init(&(pool->mtxStats), 0);
    pthread_mutex_init(&(pool->mtxContinueWorking), 0);
    
    pthread_mutex_lock(&(pool->mtxQueue));
    insertInQueue(pool->queue, startingUrl);
    pthread_cond_signal(&(pool->cond_nonemptyQueue));
    pthread_mutex_unlock(&(pool->mtxQueue));
    

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
    ThreadPool* pool = (ThreadPool*) argp;
    while(pool->continueWorking){

        int fd=0;
         /* Create socket */
        if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            perror_exit("socket");

        /* Initiate connection */
        if (connect(fd, pool->serverptr, sizeof(struct sockaddr_in)) < 0)
            perror_exit("connect to server");


        pthread_mutex_lock(&(pool->mtxQueue));
        while (pool->queue->firstNode == NULL && pool->continueWorking) {
            pthread_cond_wait(&(pool->cond_nonemptyQueue), &(pool->mtxQueue));
        }
        if(!pool->continueWorking)
             break;
        char* pageName = deleteFromQueue(pool->queue, 1);
        if(pageName == NULL){
            printf("Error! Null page name.\n");
            exit(1);
        }
        pthread_mutex_unlock(&(pool->mtxQueue));


        readWriteInSocket(fd, pool->save_dir, pool->stats, pageName, pool->host_or_IP, pool,0);


    }
    pthread_exit(0);
}

void destroyThreadPool(ThreadPool *pool){
    if(pool==NULL){
        return;
    }

    //must wait for threads
     /* Join all worker thread */
    for(int i = 0; i < pool->numberOfThreads; i++) {
       if(pthread_kill(pool->threads[i], 0) != 0) {
            perror_exit("pthread_kill");
        }
    }
    pthread_cond_destroy(&(pool->cond_nonemptyQueue));
    pthread_mutex_destroy(&(pool->mtxQueue));
    pthread_mutex_destroy(&(pool->mtxStats));
    pthread_mutex_destroy(&(pool->mtxContinueWorking));


    destroyQueue(pool->queue);
    free(pool->threads);
    free(pool);
}
