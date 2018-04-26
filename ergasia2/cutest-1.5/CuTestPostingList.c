#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestPostingList.h"

void TestInsertPostingList(CuTest *tc){		//without checking lines
	postingList* pL = malloc(sizeof(postingList));
	createPostingList(pL);
	
	CuAssertIntEquals(tc,0,pL->listSize);
	
	insertIntoPostingList(pL, "Hello", 0, 0);						//0
	CuAssertIntEquals(tc,1,pL->listSize);
	CuAssertStrEquals(tc,"Hello",pL->firstNode->filePath);
	CuAssertIntEquals(tc,1,pL->firstNode->occurrences);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next);
	
	List* l = pL->firstNode->info;
	//checking info
	CuAssertIntEquals(tc, 1, l->listSize);
	CuAssertIntEquals(tc, 0, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 0, l->firstNode->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next);
	
	
	
	insertIntoPostingList(pL, "Wonderful", 3, 2);					//1
	CuAssertIntEquals(tc,2,pL->listSize);
	CuAssertStrEquals(tc,"Wonderful",pL->firstNode->next->filePath);
	CuAssertIntEquals(tc,1,pL->firstNode->next->occurrences);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next->next);
	
	
	l = pL->firstNode->next->info;
	//checking info
	CuAssertIntEquals(tc, 1, l->listSize);
	CuAssertIntEquals(tc, 3, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 2, l->firstNode->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next);
	
	
	insertIntoPostingList(pL, "World", 4, 5);						//2
	CuAssertIntEquals(tc,3,pL->listSize);
	CuAssertStrEquals(tc,"World",pL->firstNode->next->next->filePath);
	CuAssertIntEquals(tc,1,pL->firstNode->next->next->occurrences);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next->next->next);
	
	
	insertIntoPostingList(pL, "Wonderful", 5, 7);					//1
	CuAssertIntEquals(tc,3,pL->listSize);
	CuAssertStrEquals(tc,"Wonderful",pL->firstNode->next->filePath);
	CuAssertIntEquals(tc,2,pL->firstNode->next->occurrences);
	CuAssertPtrNotNull(tc,pL->firstNode->next->next);
	
	l = pL->firstNode->next->info;
	//checking info
	CuAssertIntEquals(tc, 2, l->listSize);
	CuAssertIntEquals(tc, 3, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 2, l->firstNode->wordOffset);
	CuAssertIntEquals(tc, 5, l->firstNode->next->lineOfText);
	CuAssertIntEquals(tc, 7, l->firstNode->next->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next->next);
	
	
	
	insertIntoPostingList(pL, "Hello", 0, 0);						//0
	CuAssertIntEquals(tc,3,pL->listSize);
	CuAssertStrEquals(tc,"Hello", pL->firstNode->filePath);
	CuAssertIntEquals(tc,2,pL->firstNode->occurrences);
	CuAssertPtrNotNull(tc,pL->firstNode->next);
	
	l = pL->firstNode->info;
	//checking info
	CuAssertIntEquals(tc, 2, l->listSize);
	CuAssertIntEquals(tc, 0, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 0, l->firstNode->wordOffset);
	CuAssertIntEquals(tc, 0, l->firstNode->next->lineOfText);
	CuAssertIntEquals(tc, 0, l->firstNode->next->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next->next);
	
	insertIntoPostingList(pL, "Wonderful", 3, 2);					//1
	CuAssertIntEquals(tc,3,pL->listSize);
	CuAssertStrEquals(tc,"Wonderful",pL->firstNode->next->filePath);
	CuAssertIntEquals(tc,3,pL->firstNode->next->occurrences);
	CuAssertPtrNotNull(tc,pL->firstNode->next->next);
	
	insertIntoPostingList(pL, "!!!", 5, 5);							//3
	CuAssertIntEquals(tc,4,pL->listSize);
	CuAssertStrEquals(tc,"!!!",pL->firstNode->next->next->next->filePath);
	CuAssertIntEquals(tc,1,pL->firstNode->next->next->next->occurrences);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next->next->next->next);
	
	destroyPostingList(pL);
}





CuSuite* PostingListGetSuite(){		//adding TestPostingList Functions into suite
	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsertPostingList);
    
    return suite;
}


