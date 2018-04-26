#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestList.h"

void TestInsertIntoList(CuTest *tc){
	List* l = createList();
	
	CuAssertIntEquals(tc, 0, l->listSize);
	insertIntoList(l, 0, 0);
	CuAssertIntEquals(tc, 1, l->listSize);
	CuAssertIntEquals(tc, 0, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 0, l->firstNode->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next);
	
	insertIntoList(l, 1, 3);
	CuAssertIntEquals(tc, 2, l->listSize);
	CuAssertIntEquals(tc, 1, l->firstNode->next->lineOfText);
	CuAssertIntEquals(tc, 3, l->firstNode->next->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next->next);
	
	insertIntoList(l, -1, 5);
	CuAssertIntEquals(tc, 3, l->listSize);
	CuAssertIntEquals(tc, -1, l->firstNode->next->next->lineOfText);
	CuAssertIntEquals(tc, 5, l->firstNode->next->next->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next->next->next);
	
	insertIntoList(l, 0, 0);
	CuAssertIntEquals(tc, 4, l->listSize);
	CuAssertIntEquals(tc, 0, l->firstNode->next->next->next->lineOfText);
	CuAssertIntEquals(tc, 0, l->firstNode->next->next->next->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next->next->next->next);
	
	//printList(l);
	
	destroyList(l);
	
}


CuSuite* ListGetSuite() {		//adding TestList Functions into suite
    CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsertIntoList);
    
    return suite;
}
