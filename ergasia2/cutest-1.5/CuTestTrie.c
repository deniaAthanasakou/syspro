#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestTrie.h"


void TestInsert(CuTest *tc){
	
	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));

	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "a", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "This" , "a", 0, 0);
	
	
	//The
	assert(trie->letter=='T');
	assert(trie->verticalNext->letter=='h');
	assert(trie->verticalNext->verticalNext->letter=='e');
	
	CuAssertPtrEquals(tc,NULL,trie->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->verticalNext->verticalNext->verticalNext);
	
	//brown
	assert(trie->horizontalNext->letter=='b');
	assert(trie->horizontalNext->verticalNext->letter=='r');
	assert(trie->horizontalNext->verticalNext->verticalNext->letter=='o');
	assert(trie->horizontalNext->verticalNext->verticalNext->verticalNext->letter=='w');
	assert(trie->horizontalNext->verticalNext->verticalNext->verticalNext->verticalNext->letter=='n');
	
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->verticalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->verticalNext->verticalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->verticalNext->verticalNext->verticalNext->verticalNext->verticalNext);
	
	
	//(Th)is
	assert(trie->verticalNext->verticalNext->horizontalNext->letter=='i');
	assert(trie->verticalNext->verticalNext->horizontalNext->verticalNext->letter=='s');
	
	
	destroyContainsTrie(containsTrie);
	
}

void TestSearchWord(CuTest *tc){
	
	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));
	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "a", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "This" , "a", 0, 0);


	//CuAssertPtrNotNull(tc,searchPathInTrie(trie, "This"));
	//CuAssertPtrNotNull(tc,searchPathInTrie(trie, "brown"));
	//CuAssertPtrNotNull(tc,searchPathInTrie(trie, "The"));
	
	//CuAssertPtrEquals(tc,NULL,searchPathInTrie(trie, "hello"));
	//CuAssertPtrEquals(tc,NULL,searchPathInTrie(trie, "That"));
	//CuAssertPtrEquals(tc,NULL,searchPathInTrie(trie, "-what"));
	
	
	destroyContainsTrie(containsTrie);
}

void TestCreateTrieFromFile(CuTest *tc){
	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));

	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	CuAssertIntEquals(tc, 0, createTrieFromFile(containsTrie, "wrongInput"));
	
	CuAssertIntEquals(tc, 1, createTrieFromFile(containsTrie, "inputForTrie"));
	
	CuAssertIntEquals(tc,5,containsTrie->noOfTrieWords);
	
	//hello
	assert(trie->letter=='h');
	assert(trie->verticalNext->letter=='e');
	assert(trie->verticalNext->verticalNext->letter=='l');
	assert(trie->verticalNext->verticalNext->verticalNext->letter=='l');
	assert(trie->verticalNext->verticalNext->verticalNext->verticalNext->letter=='o');
	
	//check for nexts
	CuAssertPtrEquals(tc,NULL,trie->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->verticalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->verticalNext->verticalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->verticalNext->verticalNext->verticalNext->verticalNext->verticalNext);
	
	postingList* pL = trie->verticalNext->verticalNext->verticalNext->verticalNext->pL;
	//check postingList
	CuAssertIntEquals(tc, 1, pL->listSize);
	CuAssertIntEquals(tc, 2, pL->firstNode->occurrences);
	CuAssertStrEquals(tc, "inputForTrie", pL->firstNode->filePath);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next);
	
	List* l = pL->firstNode->info;
	//checking list
	CuAssertIntEquals(tc, 0, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 0, l->firstNode->wordOffset);
	CuAssertIntEquals(tc, 5, l->firstNode->next->lineOfText);
	CuAssertIntEquals(tc, 2, l->firstNode->next->wordOffset);
	CuAssertIntEquals(tc, 2, l->listSize);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next->next);
	
	
	
	//world
	assert(trie->horizontalNext->letter=='w');
	assert(trie->horizontalNext->verticalNext->letter=='o');
	assert(trie->horizontalNext->verticalNext->verticalNext->letter=='r');
	assert(trie->horizontalNext->verticalNext->verticalNext->verticalNext->letter=='l');
	assert(trie->horizontalNext->verticalNext->verticalNext->verticalNext->verticalNext->letter=='d');
	
	//check for nexts
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->verticalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->verticalNext->verticalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->verticalNext->verticalNext->verticalNext->verticalNext->verticalNext);
	
	pL = trie->horizontalNext->verticalNext->verticalNext->verticalNext->verticalNext->pL;
	//check postingList
	CuAssertIntEquals(tc, 1, pL->listSize);
	CuAssertIntEquals(tc, 1, pL->firstNode->occurrences);
	CuAssertStrEquals(tc, "inputForTrie", pL->firstNode->filePath);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next);
	
	l = pL->firstNode->info;
	//checking list
	CuAssertIntEquals(tc, 0, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 6, l->firstNode->wordOffset);
	CuAssertIntEquals(tc, 1, l->listSize);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next);
	
	//this
	assert(trie->horizontalNext->horizontalNext->letter=='t');
	assert(trie->horizontalNext->horizontalNext->verticalNext->letter=='h');
	assert(trie->horizontalNext->horizontalNext->verticalNext->verticalNext->letter=='i');
	assert(trie->horizontalNext->horizontalNext->verticalNext->verticalNext->verticalNext->letter=='s');
	
	//check for nexts
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->verticalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->verticalNext->verticalNext->verticalNext->verticalNext);
	
	pL = trie->horizontalNext->horizontalNext->verticalNext->verticalNext->verticalNext->pL;
	//check postingList
	CuAssertIntEquals(tc, 1, pL->listSize);
	CuAssertIntEquals(tc, 1, pL->firstNode->occurrences);
	CuAssertStrEquals(tc, "inputForTrie", pL->firstNode->filePath);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next);
	
	l = pL->firstNode->info;
	//checking list
	CuAssertIntEquals(tc, 1, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 5, l->firstNode->wordOffset);
	CuAssertIntEquals(tc, 1, l->listSize);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next);
	
	//is
	assert(trie->horizontalNext->horizontalNext->horizontalNext->letter=='i');
	assert(trie->horizontalNext->horizontalNext->horizontalNext->verticalNext->letter=='s');
	
	
	
	//check for nexts
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->horizontalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->horizontalNext->verticalNext->verticalNext);
	
	pL = trie->horizontalNext->horizontalNext->horizontalNext->verticalNext->pL;
	//check postingList
	CuAssertIntEquals(tc, 1, pL->listSize);
	CuAssertIntEquals(tc, 1, pL->firstNode->occurrences);
	CuAssertStrEquals(tc, "inputForTrie", pL->firstNode->filePath);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next);
	
	l = pL->firstNode->info;
	//checking list
	CuAssertIntEquals(tc, 1, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 13, l->firstNode->wordOffset);
	CuAssertIntEquals(tc, 1, l->listSize);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next);
	
	//dog
	assert(trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->letter=='d');
	assert(trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->letter=='o');
	assert(trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->verticalNext->letter=='g');
	
	//check for nexts
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->verticalNext->verticalNext);

	pL = trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->verticalNext->pL;
	//check postingList
	CuAssertIntEquals(tc, 1, pL->listSize);
	CuAssertIntEquals(tc, 2, pL->firstNode->occurrences);
	CuAssertStrEquals(tc, "inputForTrie", pL->firstNode->filePath);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next);
	
	l = pL->firstNode->info;
	//checking list
	CuAssertIntEquals(tc, 1, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 18, l->firstNode->wordOffset);
	CuAssertIntEquals(tc, 4, l->firstNode->next->lineOfText);
	CuAssertIntEquals(tc, 3, l->firstNode->next->wordOffset);
	CuAssertIntEquals(tc, 2, l->listSize);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next->next);
	
	
	destroyContainsTrie(containsTrie);

}


CuSuite* TrieGetSuite() {		//adding TestTrie Functions into suite
    CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsert);
    SUITE_ADD_TEST(suite, TestSearchWord);
    SUITE_ADD_TEST(suite, TestCreateTrieFromFile);
    
    return suite;
}


