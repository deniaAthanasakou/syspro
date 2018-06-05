#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include "CuTestThread.h"


void TestCreateThreadPool(CuTest *tc){

	/*//printf("I am original thread %ld and I will create other threads\n", pthread_self());
	ThreadPool* pool = createThreadPool(5);
	CuAssertIntEquals(tc,0,pool->start);
	CuAssertIntEquals(tc,0,pool->count);
	CuAssertIntEquals(tc,-1,pool->end);
	CuAssertIntEquals(tc,5,pool->numberOfThreads);


	destroyThreadPool(pool);*/
}

void TestInsertFds(CuTest *tc){

/*	ThreadPool* pool = createThreadPool(5);

	insertFd(pool, 1);
	CuAssertIntEquals(tc,0,pool->start);
	CuAssertIntEquals(tc,1,pool->count);
	CuAssertIntEquals(tc,0,pool->end);
	CuAssertIntEquals(tc,1,pool->fds[pool->start]);

	insertFd(pool, 2);
	CuAssertIntEquals(tc,0,pool->start);
	CuAssertIntEquals(tc,2,pool->count);
	CuAssertIntEquals(tc,1,pool->end);
	CuAssertIntEquals(tc,1,pool->fds[pool->start]);
	CuAssertIntEquals(tc,2,pool->fds[pool->start+1]);

	for(int i=3; i<=10; i++){
		insertFd(pool, i);
	}

	CuAssertIntEquals(tc,0,pool->start);
	CuAssertIntEquals(tc,10,pool->count);
	CuAssertIntEquals(tc,9,pool->end);

	for(int i=0; i<=9; i++){
		CuAssertIntEquals(tc,i+1,pool->fds[i]);
	}
	CuAssertIntEquals(tc,10,pool->fds[pool->end]);

	//insertFd(pool, 11);
	
/*
	printf("must remove\n");
	CuAssertIntEquals(tc,1,getFdToThread(pool));
	pthread_cond_signal(&(pool->cond_nonfull));

	CuAssertIntEquals(tc,10,pool->fds[pool->end]);*/

	//destroyThreadPool(pool);

}

void TestGetFdToThread(CuTest *tc){
/*	ThreadPool* pool = createThreadPool(5);
	
	for(int i=0; i<10; i++){
		insertFd(pool, i);
	}

	CuAssertIntEquals(tc,0,getFdToThread(pool));
	CuAssertIntEquals(tc,0,pool->start);
	CuAssertIntEquals(tc,9,pool->count);
	CuAssertIntEquals(tc,8,pool->end);

	destroyThreadPool(pool);*/

}


CuSuite* ThreadGetSuite(){	//adding TestThread Functions into suite

	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestCreateThreadPool);
    SUITE_ADD_TEST(suite, TestInsertFds);

    
    return suite;
}