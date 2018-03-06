#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestPostingList.h"

void TestInsertPostingList(CuTest *tc){
	postingList* pL = malloc(sizeof(postingList));
	createPostingList(pL);
	
	CuAssertIntEquals(tc,0,pL->documentFreq);
	insertIntoPostingList(pL, 0);
	CuAssertIntEquals(tc,1,pL->documentFreq);
	CuAssertIntEquals(tc,0,pL->firstNode->textId);
	CuAssertIntEquals(tc,1,pL->firstNode->occurrences);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next);
	
	insertIntoPostingList(pL, 1);
	CuAssertIntEquals(tc,2,pL->documentFreq);
	CuAssertIntEquals(tc,1,pL->firstNode->next->textId);
	CuAssertIntEquals(tc,1,pL->firstNode->next->occurrences);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next->next);
	
	insertIntoPostingList(pL, 2);
	CuAssertIntEquals(tc,3,pL->documentFreq);
	CuAssertIntEquals(tc,2,pL->firstNode->next->next->textId);
	CuAssertIntEquals(tc,1,pL->firstNode->next->next->occurrences);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next->next->next);
	
	
	insertIntoPostingList(pL, 1);
	CuAssertIntEquals(tc,3,pL->documentFreq);
	CuAssertIntEquals(tc,1,pL->firstNode->next->textId);
	CuAssertIntEquals(tc,2,pL->firstNode->next->occurrences);
	CuAssertPtrNotNull(tc,pL->firstNode->next->next);
	
	
	
	insertIntoPostingList(pL, 0);
	CuAssertIntEquals(tc,3,pL->documentFreq);
	CuAssertIntEquals(tc,0,pL->firstNode->textId);
	CuAssertIntEquals(tc,2,pL->firstNode->occurrences);
	CuAssertPtrNotNull(tc,pL->firstNode->next);
	
	insertIntoPostingList(pL, 1);
	CuAssertIntEquals(tc,3,pL->documentFreq);
	CuAssertIntEquals(tc,1,pL->firstNode->next->textId);
	CuAssertIntEquals(tc,3,pL->firstNode->next->occurrences);
	CuAssertPtrNotNull(tc,pL->firstNode->next->next);
	
	insertIntoPostingList(pL, 3);
	CuAssertIntEquals(tc,4,pL->documentFreq);
	CuAssertIntEquals(tc,3,pL->firstNode->next->next->next->textId);
	CuAssertIntEquals(tc,1,pL->firstNode->next->next->next->occurrences);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next->next->next->next);
	
}





CuSuite* PostingListGetSuite(){		//adding TestPostingList Functions into suite
	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsertPostingList);
    
    return suite;
}


