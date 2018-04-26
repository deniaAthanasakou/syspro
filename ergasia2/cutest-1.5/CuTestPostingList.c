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
	CuAssertIntEquals(tc,0,pL->firstNode->line);
	CuAssertIntEquals(tc,0,pL->firstNode->wordOffset);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next);
	
	insertIntoPostingList(pL, "Wonderful", 3, 2);					//1
	CuAssertIntEquals(tc,2,pL->listSize);
	CuAssertStrEquals(tc,"Wonderful",pL->firstNode->next->filePath);
	CuAssertIntEquals(tc,1,pL->firstNode->next->occurrences);
	CuAssertIntEquals(tc,3,pL->firstNode->next->line);
	CuAssertIntEquals(tc,2,pL->firstNode->next->wordOffset);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next->next);
	
	insertIntoPostingList(pL, "World", 4, 5);						//2
	CuAssertIntEquals(tc,3,pL->listSize);
	CuAssertStrEquals(tc,"World",pL->firstNode->next->next->filePath);
	CuAssertIntEquals(tc,1,pL->firstNode->next->next->occurrences);
	CuAssertIntEquals(tc,4,pL->firstNode->next->next->line);
	CuAssertIntEquals(tc,5,pL->firstNode->next->next->wordOffset);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next->next->next);
	
	
	insertIntoPostingList(pL, "Wonderful", 3, 2);					//1
	CuAssertIntEquals(tc,3,pL->listSize);
	CuAssertStrEquals(tc,"Wonderful",pL->firstNode->next->filePath);
	CuAssertIntEquals(tc,2,pL->firstNode->next->occurrences);
	CuAssertIntEquals(tc,3,pL->firstNode->next->line);
	CuAssertIntEquals(tc,2,pL->firstNode->next->wordOffset);
	CuAssertPtrNotNull(tc,pL->firstNode->next->next);
	
	
	
	insertIntoPostingList(pL, "Hello", 0, 0);						//0
	CuAssertIntEquals(tc,3,pL->listSize);
	CuAssertStrEquals(tc,"Hello", pL->firstNode->filePath);
	CuAssertIntEquals(tc,2,pL->firstNode->occurrences);
	CuAssertIntEquals(tc,0,pL->firstNode->line);
	CuAssertIntEquals(tc,0,pL->firstNode->wordOffset);
	CuAssertPtrNotNull(tc,pL->firstNode->next);
	
	insertIntoPostingList(pL, "Wonderful", 3, 2);					//1
	CuAssertIntEquals(tc,3,pL->listSize);
	CuAssertStrEquals(tc,"Wonderful",pL->firstNode->next->filePath);
	CuAssertIntEquals(tc,3,pL->firstNode->next->occurrences);
	CuAssertIntEquals(tc,3,pL->firstNode->next->line);
	CuAssertIntEquals(tc,2,pL->firstNode->next->wordOffset);
	CuAssertPtrNotNull(tc,pL->firstNode->next->next);
	
	insertIntoPostingList(pL, "!!!", 5, 5);							//3
	CuAssertIntEquals(tc,4,pL->listSize);
	CuAssertStrEquals(tc,"!!!",pL->firstNode->next->next->next->filePath);
	CuAssertIntEquals(tc,1,pL->firstNode->next->next->next->occurrences);
	CuAssertIntEquals(tc,5,pL->firstNode->next->next->next->line);
	CuAssertIntEquals(tc,5,pL->firstNode->next->next->next->wordOffset);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next->next->next->next);
	
	destroyPostingList(pL);
}





CuSuite* PostingListGetSuite(){		//adding TestPostingList Functions into suite
	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsertPostingList);
    
    return suite;
}


