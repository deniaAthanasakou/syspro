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
    pool->start = 0;
    pool->end = -1;
    pool->count = 0;
    pool->numberOfThreads=numberOfThreads;
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * numberOfThreads);
    pool->queue=queue;

    pool->stats=stats;
    pool->save_dir=save_dir;
    pool->host_or_IP=host_or_IP;
    pool->serverptr = serverptr;


    pthread_mutex_init(&(pool->mtxFd), 0);
    pthread_cond_init(&(pool->cond_nonempty), 0);
    pthread_cond_init(&(pool->cond_nonfull), 0);
    pthread_mutex_init(&(pool->mtxQueue), 0);
    pthread_cond_init(&(pool->cond_nonemptyQueue), 0);


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
    printf("in thread_f\n");
    ThreadPool* pool = (ThreadPool*) argp;
    printf("I am the newly created thread %ld\n", pthread_self());
    printf("my save_dir is %s\n", pool->save_dir);
    while(1){

        int fd=0;
         /* Create socket */
        if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            perror_exit("socket");

        //int fd=getFdToThread(pool);
        printf("fd: %d\n", fd);
        pthread_cond_signal(&(pool->cond_nonfull));

        /* Initiate connection */
        if (connect(fd, pool->serverptr, sizeof(struct sockaddr_in)) < 0)
            perror_exit("connect");


        pthread_mutex_lock(&(pool->mtxQueue));
        while (pool->queue->firstNode == NULL) {
            printf(">> Found Queue Empty \n");
            pthread_cond_wait(&(pool->cond_nonemptyQueue), &(pool->mtxQueue));
        }
        char* pageName = deleteFromQueue(pool->queue, 1);
        if(pageName == NULL){
            printf("Error! Null page name.\n");
            exit(1);
        }
        pthread_mutex_unlock(&(pool->mtxQueue));


        readWriteInSocket(fd, pool->save_dir, pool->stats, pageName, pool->host_or_IP, pool,0);


    }
}


void destroyThreadPool(ThreadPool *pool){
    if(pool==NULL)
        return;


    //must wait for threads
     /* Join all worker thread */
   for(int i = 0; i < pool->numberOfThreads; i++) {
       // if(pthread_join(pool->threads[i], NULL) != 0) {
    printf("in for\n");
        if(pthread_cancel(pool->threads[i]) != 0) {
            perror_exit("pthread_cancel");
        }
         printf("after if 1\n");

    }
    printf("after for1\n");
    for(int i = 0; i < pool->numberOfThreads; i++) {
       // if(pthread_join(pool->threads[i], NULL) != 0) {
        printf("in for\n");
        if(pthread_kill(pool->threads[i], 0) != 0) {
            perror_exit("pthread_kill");
        }
        printf("after if 2\n");

    }
    printf("after for2\n");
    pthread_cond_destroy(&(pool->cond_nonempty));
    pthread_cond_destroy(&(pool->cond_nonfull));
    pthread_cond_destroy(&(pool->cond_nonemptyQueue));
    pthread_mutex_destroy(&(pool->mtxFd));
    pthread_mutex_destroy(&(pool->mtxQueue));
    pthread_mutex_destroy(&(pool->mtxStats));


    
    free(pool->threads);
    free(pool);
}


void insertFd(ThreadPool* pool, int fd){

    pthread_mutex_lock(&(pool->mtxFd));
    while (pool->count >= POOL_SIZE) {
        printf(">> Found Buffer Full \n");
        pthread_cond_wait(&(pool->cond_nonfull), &(pool->mtxFd));
    }
    pool->end = (pool->end + 1) % POOL_SIZE;
    pool->fds[pool->end] = fd;

    pool->count++;
    pthread_mutex_unlock(&(pool->mtxFd));    

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
    pthread_mutex_lock(&(pool->mtxFd));
    while (pool->count <= 0) {
        printf(">> Found Buffer Empty \n");
        pthread_cond_wait(&(pool->cond_nonempty), &(pool->mtxFd));
    }
    fd = pool->fds[pool->start];
    pool->start = (pool->start + 1) % POOL_SIZE;
    pool->count--;
    pthread_mutex_unlock(&(pool->mtxFd));
    return fd;


}
