#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestPostingList.h"
#include "../documentIdsHandler.h"

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
	
	destroyPostingList(pL);
}


void TestGetDifferentIds(CuTest *tc){
	postingList* pL = malloc(sizeof(postingList));
	createPostingList(pL);
	
	insertIntoPostingList(pL, 0);
	insertIntoPostingList(pL, 1);
	insertIntoPostingList(pL, 2);
	insertIntoPostingList(pL, 0);
	insertIntoPostingList(pL, 3);
	insertIntoPostingList(pL, 1);
	
	DifferentIds *diffIds = malloc(sizeof(DifferentIds));
	createDifferentIds(diffIds);
	
	getDifferentIds(pL,diffIds);
	destroyPostingList(pL);
	
	CuAssertIntEquals(tc,10,diffIds->length);
	CuAssertIntEquals(tc,4,diffIds->position);
	CuAssertIntEquals(tc,0,diffIds->ids[0]);
	CuAssertIntEquals(tc,1,diffIds->ids[1]);
	CuAssertIntEquals(tc,2,diffIds->ids[2]);
	CuAssertIntEquals(tc,3,diffIds->ids[3]);
	
	pL = malloc(sizeof(postingList));
	createPostingList(pL);
	
	insertIntoPostingList(pL, 0);
	insertIntoPostingList(pL, 5);
	insertIntoPostingList(pL, 6);
	insertIntoPostingList(pL, 7);
	insertIntoPostingList(pL, 4);
	insertIntoPostingList(pL, 1);
	insertIntoPostingList(pL, 10);
	insertIntoPostingList(pL, 13);
	insertIntoPostingList(pL, 18);
	
	getDifferentIds(pL,diffIds);
	destroyPostingList(pL);
	
	CuAssertIntEquals(tc,20,diffIds->length);
	CuAssertIntEquals(tc,11,diffIds->position);
	CuAssertIntEquals(tc,4,diffIds->ids[4]);
	CuAssertIntEquals(tc,5,diffIds->ids[5]);
	CuAssertIntEquals(tc,6,diffIds->ids[6]);
	CuAssertIntEquals(tc,7,diffIds->ids[7]);
	CuAssertIntEquals(tc,10,diffIds->ids[8]);
	CuAssertIntEquals(tc,13,diffIds->ids[9]);
	CuAssertIntEquals(tc,18,diffIds->ids[10]);
	
	destroyDifferentIds(diffIds);
}




CuSuite* PostingListGetSuite(){		//adding TestPostingList Functions into suite
	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsertPostingList);
    SUITE_ADD_TEST(suite, TestGetDifferentIds);
    
    return suite;
}


