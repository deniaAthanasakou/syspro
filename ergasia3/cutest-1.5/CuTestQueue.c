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

	insertInQueue(queue, "a");
	CuAssertIntEquals(tc,1,queue->size);
	CuAssertPtrEquals(tc,queue->lastNode,queue->firstNode);
	CuAssertStrEquals(tc,queue->lastNode->pageName,queue->firstNode->pageName);
	CuAssertStrEquals(tc,"a",queue->firstNode->pageName);

	insertInQueue(queue, "b");
	CuAssertIntEquals(tc,2,queue->size);
	CuAssertStrEquals(tc,"a",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"b",queue->lastNode->pageName);

	insertInQueue(queue, "c");
	CuAssertIntEquals(tc,3,queue->size);
	CuAssertStrEquals(tc,"a",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"b",queue->firstNode->next->pageName);
	CuAssertStrEquals(tc,"c",queue->lastNode->pageName);

	insertInQueue(queue, "d");
	CuAssertIntEquals(tc,4,queue->size);
	CuAssertStrEquals(tc,"a",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"b",queue->firstNode->next->pageName);
	CuAssertStrEquals(tc,"c",queue->firstNode->next->next->pageName);
	CuAssertStrEquals(tc,"d",queue->lastNode->pageName);

	insertInQueue(queue, "c");
	CuAssertIntEquals(tc,4,queue->size);
	CuAssertStrEquals(tc,"a",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"b",queue->firstNode->next->pageName);
	CuAssertStrEquals(tc,"c",queue->firstNode->next->next->pageName);
	CuAssertStrEquals(tc,"d",queue->lastNode->pageName);

	//printQueue(queue);

	destroyQueue(queue);

}

void TestDelete(CuTest *tc){
	Queue* queue=createQueue();
	insertInQueue(queue, "a");
	insertInQueue(queue, "b");
	insertInQueue(queue, "c");
	insertInQueue(queue, "d");
	insertInQueue(queue, "b");

	deleteFromQueue(queue);
	CuAssertIntEquals(tc,3,queue->size);
	CuAssertStrEquals(tc,"b",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"c",queue->firstNode->next->pageName);
	CuAssertStrEquals(tc,"d",queue->firstNode->next->next->pageName);
	CuAssertStrEquals(tc,"d",queue->lastNode->pageName);

	deleteFromQueue(queue);
	CuAssertIntEquals(tc,2,queue->size);
	CuAssertStrEquals(tc,"c",queue->firstNode->pageName);
	CuAssertStrEquals(tc,"d",queue->firstNode->next->pageName);
	CuAssertStrEquals(tc,"d",queue->lastNode->pageName);

	destroyQueue(queue);
}

CuSuite* QueueGetSuite(){	//adding TestQueue Functions into suite

	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsert);
    SUITE_ADD_TEST(suite, TestDelete);
    
    return suite;
}