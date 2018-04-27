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
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "b", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "This" , "c", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a", 1, 4);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "d", 5, 3);


	postingList* pL1 = searchWordInTrie(trie, "This");
	postingList* pL2 = searchWordInTrie(trie, "brown");
	postingList* pL3 = searchWordInTrie(trie, "The");


	CuAssertPtrNotNull(tc,pL1);
	CuAssertPtrNotNull(tc,pL2);
	CuAssertPtrNotNull(tc,pL3);
	
	
	//checking postingLists
	CuAssertIntEquals(tc, 1, pL1->listSize); 			//This
	CuAssertStrEquals(tc,"c",pL1->firstNode->filePath);
	CuAssertIntEquals(tc,1,pL1->firstNode->occurrences);
	CuAssertPtrEquals(tc,NULL,pL1->firstNode->next);
	
	List* l = pL1->firstNode->info;
	//checking info
	CuAssertIntEquals(tc, 1, l->listSize);
	CuAssertIntEquals(tc, 0, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 0, l->firstNode->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next);
	
	
	//checking postingLists
	CuAssertIntEquals(tc, 2, pL2->listSize); 			//brown
	CuAssertStrEquals(tc,"b",pL2->firstNode->filePath);
	CuAssertIntEquals(tc,1,pL2->firstNode->occurrences);
	CuAssertStrEquals(tc,"d",pL2->firstNode->next->filePath);
	CuAssertPtrEquals(tc,NULL,pL2->firstNode->next->next);
	
	
	l = pL2->firstNode->info;			//firstnode list
	//checking info
	CuAssertIntEquals(tc, 1, l->listSize);
	CuAssertIntEquals(tc, 0, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 0, l->firstNode->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next);
	
	l = pL2->firstNode->next->info;			//next node list
	//checking info
	CuAssertIntEquals(tc, 1, l->listSize);
	CuAssertIntEquals(tc, 5, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 3, l->firstNode->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next);
	
	
	//checking postingLists
	CuAssertIntEquals(tc, 1, pL3->listSize); 			//The
	CuAssertStrEquals(tc,"a",pL3->firstNode->filePath);
	CuAssertIntEquals(tc,2,pL3->firstNode->occurrences);
	CuAssertPtrEquals(tc,NULL,pL3->firstNode->next);
	
	l = pL3->firstNode->info;		
	//checking info
	CuAssertIntEquals(tc, 2, l->listSize);
	CuAssertIntEquals(tc, 0, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 0, l->firstNode->wordOffset);
	CuAssertIntEquals(tc, 1, l->firstNode->next->lineOfText);
	CuAssertIntEquals(tc, 4, l->firstNode->next->wordOffset);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next->next);
	
	
	
	CuAssertPtrEquals(tc,NULL,searchWordInTrie(trie, "hello"));
	CuAssertPtrEquals(tc,NULL,searchWordInTrie(trie, "That"));
	CuAssertPtrEquals(tc,NULL,searchWordInTrie(trie, "-what"));
	
	
	destroyContainsTrie(containsTrie);
}

void TestCreateTrieFromFile(CuTest *tc){
	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));

	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	CuAssertIntEquals(tc, 0, createTrieFromFile(containsTrie, "wrongInput"));
	
	CuAssertIntEquals(tc, 1, createTrieFromFile(containsTrie, "./inputFiles/inputForTrie"));
	
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
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie", pL->firstNode->filePath);
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
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie", pL->firstNode->filePath);
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
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie", pL->firstNode->filePath);
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
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie", pL->firstNode->filePath);
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
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie", pL->firstNode->filePath);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next);
	
	l = pL->firstNode->info;
	//checking list
	CuAssertIntEquals(tc, 1, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 18, l->firstNode->wordOffset);
	CuAssertIntEquals(tc, 4, l->firstNode->next->lineOfText);
	CuAssertIntEquals(tc, 3, l->firstNode->next->wordOffset);
	CuAssertIntEquals(tc, 2, l->listSize);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next->next);
	
	
	CuAssertIntEquals(tc, 1, createTrieFromFile(containsTrie, "./inputFiles/inputForTrie2"));
	CuAssertIntEquals(tc, 1, createTrieFromFile(containsTrie, "./inputFiles/inputForTrie3"));
	
	CuAssertIntEquals(tc,11,containsTrie->noOfTrieWords);
	
	
	
	//checking if dog was inserted
	pL = trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->verticalNext->pL;
	//check postingList
	CuAssertIntEquals(tc, 2, pL->listSize);
	CuAssertIntEquals(tc, 2, pL->firstNode->occurrences);
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie", pL->firstNode->filePath);
	CuAssertIntEquals(tc, 1, pL->firstNode->next->occurrences);
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie2", pL->firstNode->next->filePath);
	CuAssertPtrEquals(tc,NULL,pL->firstNode->next->next);
	
	
	//check for nexts
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->verticalNext->horizontalNext);
	CuAssertPtrEquals(tc,NULL,trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->verticalNext->verticalNext);
	
	l = pL->firstNode->info;
	//checking list
	CuAssertIntEquals(tc, 1, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 18, l->firstNode->wordOffset);
	CuAssertIntEquals(tc, 4, l->firstNode->next->lineOfText);
	CuAssertIntEquals(tc, 3, l->firstNode->next->wordOffset);
	CuAssertIntEquals(tc, 2, l->listSize);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next->next);
	
	l = pL->firstNode->next->info;
	//checking list
	CuAssertIntEquals(tc, 2, l->firstNode->lineOfText);
	CuAssertIntEquals(tc, 0, l->firstNode->wordOffset);
	CuAssertIntEquals(tc, 1, l->listSize);
	CuAssertPtrEquals(tc, NULL, l->firstNode->next);
	
	
	//kow
	assert(trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->horizontalNext->letter=='k');
	assert(trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->letter=='o');
	assert(trie->horizontalNext->horizontalNext->horizontalNext->horizontalNext->horizontalNext->verticalNext->verticalNext->letter=='w');
	
	
	
	
	BytesWordsLinesStruct* info = containsTrie->info;
	//checking containsTrie->info
	CuAssertIntEquals(tc, 5, info->length);
	CuAssertIntEquals(tc, 3, info->position);
	
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie", info->array[0].fileName);
	CuAssertIntEquals(tc, 58, info->array[0].bytes);
	CuAssertIntEquals(tc, 7, info->array[0].words);
	CuAssertIntEquals(tc, 6, info->array[0].lines);	
	
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie2", info->array[1].fileName);
	CuAssertIntEquals(tc, 24, info->array[1].bytes);
	CuAssertIntEquals(tc, 4, info->array[1].words);
	CuAssertIntEquals(tc, 4, info->array[1].lines);	
	
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie3", info->array[2].fileName);
	CuAssertIntEquals(tc, 22, info->array[2].bytes);
	CuAssertIntEquals(tc, 3, info->array[2].words);
	CuAssertIntEquals(tc, 5, info->array[2].lines);	
	
	
	
	
	destroyContainsTrie(containsTrie);

}


CuSuite* TrieGetSuite() {		//adding TestTrie Functions into suite
    CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsert);
    SUITE_ADD_TEST(suite, TestSearchWord);
    SUITE_ADD_TEST(suite, TestCreateTrieFromFile);
    
    return suite;
}


