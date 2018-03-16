#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestTrie.h"


void TestInsert(CuTest *tc){
	char* line = malloc((strlen("The brown This")+1)*sizeof(char));
	strcpy(line,"The brown This");
	
	ContainsTrie* containsTrie = malloc(sizeof(containsTrie));
	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	insertLineTextIntoTrie(containsTrie, trie, line, 0);
	
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
	
	
	destroyContainsTrie(containsTrie);
	
}

void TestSearchWord(CuTest *tc){
	char* line = malloc((strlen("The brown This")+1)*sizeof(char));
	strcpy(line,"The brown This");
	
	ContainsTrie* containsTrie = malloc(sizeof(containsTrie));
	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	insertLineTextIntoTrie(containsTrie, trie, line, 0);
	
	free(line);
	line = NULL;
	

	CuAssertPtrNotNull(tc,searchWordInTrie(trie, "This"));
	CuAssertPtrNotNull(tc,searchWordInTrie(trie, "brown"));
	CuAssertPtrNotNull(tc,searchWordInTrie(trie, "The"));
	
	CuAssertPtrEquals(tc,NULL,searchWordInTrie(trie, "hello"));
	CuAssertPtrEquals(tc,NULL,searchWordInTrie(trie, "That"));
	CuAssertPtrEquals(tc,NULL,searchWordInTrie(trie, "-what"));
	
	
	destroyContainsTrie(containsTrie);
}


CuSuite* TrieGetSuite() {		//adding TestTrie Functions into suite
    CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsert);
    SUITE_ADD_TEST(suite, TestSearchWord);
    
    return suite;
}


