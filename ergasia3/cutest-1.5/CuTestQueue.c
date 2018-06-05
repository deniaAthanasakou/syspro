#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestQueue.h"



void TestInsert(CuTest *tc){
	Queue* queue=createQueue();
	CuAssertPtrNotNull(tc,queue);
	CuAssertPtrEquals(tc,NULL,queue->firstNode);
	CuAssertPtrEquals(tc,NULL,queue->lastNode);
	CuAssertIntEquals(tc,0,queue->size);

	insertInQueue(queue, "http://linux01.di.uoa:8080/site2/a");
	CuAssertIntEquals(tc,1,queue->size);
	CuAssertPtrEquals(tc,queue->lastNode,queue->firstNode);
	CuAssertStrEquals(tc,queue->lastNode->pageName,queue->firstNode->pageName);
	CuAssertStrEquals(tc,"/site2/a",queue->firstNode->pageName);

	insertInQueue(queue, "http://linux01.di.uoa:8080/site2/b");
	CuAssertIntEquals(tc,2,queue->size);
	CuAssertStrEquals(tc,"/site2/a",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"/site2/b",queue->lastNode->pageName);

	insertInQueue(queue, "http://linux01.di.uoa:8080/site2/c");
	CuAssertIntEquals(tc,3,queue->size);
	CuAssertStrEquals(tc,"/site2/a",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"/site2/b",queue->firstNode->next->pageName);
	CuAssertStrEquals(tc,"/site2/c",queue->lastNode->pageName);

	insertInQueue(queue, "http://linux01.di.uoa:8080/site2/d");
	CuAssertIntEquals(tc,4,queue->size);
	CuAssertStrEquals(tc,"/site2/a",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"/site2/b",queue->firstNode->next->pageName);
	CuAssertStrEquals(tc,"/site2/c",queue->firstNode->next->next->pageName);
	CuAssertStrEquals(tc,"/site2/d",queue->lastNode->pageName);

	insertInQueue(queue, "http://linux01.di.uoa:8080/site2/c");
	CuAssertIntEquals(tc,4,queue->size);
	CuAssertStrEquals(tc,"/site2/a",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"/site2/b",queue->firstNode->next->pageName);
	CuAssertStrEquals(tc,"/site2/c",queue->firstNode->next->next->pageName);
	CuAssertStrEquals(tc,"/site2/d",queue->lastNode->pageName);

	//printQueue(queue);
	//printf("full\n");
	//printFullQueue(queue);

	destroyQueue(queue);

}

void TestDelete(CuTest *tc){
	Queue* queue=createQueue();
	insertInQueue(queue, "http://linux01.di.uoa:8080/site2/a");
	insertInQueue(queue, "http://linux01.di.uoa:8080/site2/b");
	insertInQueue(queue, "http://linux01.di.uoa:8080/site2/c");
	insertInQueue(queue, "http://linux01.di.uoa:8080/site2/d");
	insertInQueue(queue, "http://linux01.di.uoa:8080/site2/b");

	deleteFromQueue(queue, 0);
	CuAssertIntEquals(tc,3,queue->size);
	CuAssertStrEquals(tc,"/site2/b",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"/site2/c",queue->firstNode->next->pageName);
	CuAssertStrEquals(tc,"/site2/d",queue->firstNode->next->next->pageName);
	CuAssertStrEquals(tc,"/site2/d",queue->lastNode->pageName);

	deleteFromQueue(queue, 0);
	CuAssertIntEquals(tc,2,queue->size);
	CuAssertStrEquals(tc,"/site2/c",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"/site2/d",queue->firstNode->next->pageName);
	CuAssertStrEquals(tc,"/site2/d",queue->lastNode->pageName);

	printQueue(queue);
	printf("full\n");
	printFullQueue(queue);

	destroyQueue(queue);
}



void TestGetFixedPageName(CuTest *tc){
	char* correctPageName=getFixedPageName("http://linux01.di.uoa:8080/site1/page0_1234.html");
	CuAssertStrEquals(tc,"/site1/page0_1234.html",correctPageName);

	correctPageName=getFixedPageName("/site1/page0_1234.html");
	CuAssertStrEquals(tc,"/site1/page0_1234.html",correctPageName);

	char* pageName=malloc((strlen("a/b/c/d/e/f/g/sit/site1/page0_1234.html")+1)*sizeof(char));
	strcpy(pageName, "a/b/c/d/e/f/g/sit/site1/page0_1234.html");
	correctPageName=getFixedPageName(pageName);
	CuAssertStrEquals(tc,"/site1/page0_1234.html",correctPageName);	

	free(pageName);
	
}

CuSuite* QueueGetSuite(){	//adding TestQueue Functions into suite

	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsert);
    SUITE_ADD_TEST(suite, TestDelete);
    SUITE_ADD_TEST(suite, TestGetFixedPageName);
    
    return suite;
}