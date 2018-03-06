#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestTrie.h"


void TestInsert(CuTest *tc){
	char* line = malloc((strlen("The brown This")+1)*sizeof(char));
	strcpy(line,"The brown This");
	
	Trie* trie = malloc(sizeof(Trie));
	initializeTrie(&trie);
	
	insertLineTextIntoTrie(trie, line);
	
	free(line);
	line = NULL;
	
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
	
	destroyTrie(trie);
	
}


CuSuite* TrieGetSuite() {		//adding TestTrie Functions into suite
    CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsert);
    
    return suite;
}


