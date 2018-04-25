#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestTrie.h"


void TestInsert(CuTest *tc){
	
	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));

	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a");
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "a");
	insertFullWordIntoTrie(containsTrie, trie, "This" , "a");
	
	
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

void TestSearchPath(CuTest *tc){
	
	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));
	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a");
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "a");
	insertFullWordIntoTrie(containsTrie, trie, "This" , "a");


	//CuAssertPtrNotNull(tc,searchPathInTrie(trie, "This"));
	//CuAssertPtrNotNull(tc,searchPathInTrie(trie, "brown"));
	//CuAssertPtrNotNull(tc,searchPathInTrie(trie, "The"));
	
	//CuAssertPtrEquals(tc,NULL,searchPathInTrie(trie, "hello"));
	//CuAssertPtrEquals(tc,NULL,searchPathInTrie(trie, "That"));
	//CuAssertPtrEquals(tc,NULL,searchPathInTrie(trie, "-what"));
	
	
	destroyContainsTrie(containsTrie);
}


CuSuite* TrieGetSuite() {		//adding TestTrie Functions into suite
    CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsert);
    SUITE_ADD_TEST(suite, TestSearchPath);
    
    return suite;
}


