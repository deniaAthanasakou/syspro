#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestInstructions.h"

void TestMaxCount(CuTest *tc){
	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));
	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "d", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "This" , "c", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "k", 1, 4);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "d", 5, 3);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "b", 5, 3);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "d", 5, 3);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "b", 5, 3);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "k", 3, 3);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "a", 5, 3);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a", 6, 3);
	
	arrayWords* array= malloc(sizeof(arrayWords));		//error
	createArrayWords(array);
	
	char* word = malloc(sizeof(char)*(strlen("brown")+1));
	strcpy(word,"brown");
	insertArrayWords(array, word);
	word = malloc(sizeof(char)*(strlen("red")+1));
	strcpy(word,"red");
	insertArrayWords(array, word);
	
	FileInfoMinMax* info = maxCount(array, trie);	
	CuAssertPtrEquals(tc,NULL,info);
	deleteArrayWords(array);
	
	array = malloc(sizeof(arrayWords));					//correct
	createArrayWords(array);
	word = malloc(sizeof(char)*(strlen("brown")+1));
	strcpy(word,"brown");
	insertArrayWords(array, word);
	
	info = maxCount(array, trie);	
	CuAssertStrEquals(tc,"max",info->type);
	CuAssertStrEquals(tc,"d",info->fileName);
	CuAssertIntEquals(tc,3,info->minOrMax);
	deleteArrayWords(array);
	free(info);
	
	
	array = malloc(sizeof(arrayWords));					//correct
	createArrayWords(array);
	word = malloc(sizeof(char)*(strlen("This")+1));
	strcpy(word,"This");
	insertArrayWords(array, word);
	
	info = maxCount(array, trie);	
	CuAssertStrEquals(tc,"max",info->type);
	CuAssertStrEquals(tc,"c",info->fileName);
	CuAssertIntEquals(tc,1,info->minOrMax);
	deleteArrayWords(array);
	free(info);
	
	array = malloc(sizeof(arrayWords));					//word not found
	createArrayWords(array);
	word = malloc(sizeof(char)*(strlen("oups")+1));
	strcpy(word,"oups");
	insertArrayWords(array, word);
	
	info = maxCount(array, trie);	
	CuAssertPtrEquals(tc,NULL,info);
	deleteArrayWords(array);
	
	
	array = malloc(sizeof(arrayWords));					//correct	//get alphabetically smaller
	createArrayWords(array);
	word = malloc(sizeof(char)*(strlen("The")+1));
	strcpy(word,"The");
	insertArrayWords(array, word);
	
	info = maxCount(array, trie);	
	CuAssertStrEquals(tc,"max",info->type);
	CuAssertStrEquals(tc,"a",info->fileName);
	CuAssertIntEquals(tc,2,info->minOrMax);
	deleteArrayWords(array);
	free(info);
	
	
	
	
	destroyContainsTrie(containsTrie);

}


void TestMinCount(CuTest *tc){
	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));
	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "d", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "This" , "c", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "k", 1, 4);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "d", 5, 3);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "b", 5, 3);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "d", 5, 3);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "b", 5, 3);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "k", 3, 3);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "a", 5, 3);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a", 6, 3);
	
	arrayWords* array= malloc(sizeof(arrayWords));		//error
	createArrayWords(array);
	
	char* word = malloc(sizeof(char)*(strlen("brown")+1));
	strcpy(word,"brown");
	insertArrayWords(array, word);
	word = malloc(sizeof(char)*(strlen("red")+1));
	strcpy(word,"red");
	insertArrayWords(array, word);
	
	FileInfoMinMax* info = minCount(array, trie);	
	CuAssertPtrEquals(tc,NULL,info);
	deleteArrayWords(array);
	
	array = malloc(sizeof(arrayWords));					//correct
	createArrayWords(array);
	word = malloc(sizeof(char)*(strlen("brown")+1));
	strcpy(word,"brown");
	insertArrayWords(array, word);
	
	info = minCount(array, trie);	
	CuAssertStrEquals(tc,"min",info->type);
	CuAssertStrEquals(tc,"a",info->fileName);
	CuAssertIntEquals(tc,1,info->minOrMax);
	deleteArrayWords(array);
	free(info);
	
	
	array = malloc(sizeof(arrayWords));					//correct
	createArrayWords(array);
	word = malloc(sizeof(char)*(strlen("This")+1));
	strcpy(word,"This");
	insertArrayWords(array, word);
	
	info = minCount(array, trie);	
	CuAssertStrEquals(tc,"min",info->type);
	CuAssertStrEquals(tc,"c",info->fileName);
	CuAssertIntEquals(tc,1,info->minOrMax);
	deleteArrayWords(array);
	free(info);
	
	array = malloc(sizeof(arrayWords));					//word not found
	createArrayWords(array);
	word = malloc(sizeof(char)*(strlen("oups")+1));
	strcpy(word,"oups");
	insertArrayWords(array, word);
	
	info = minCount(array, trie);	
	CuAssertPtrEquals(tc,NULL,info);
	deleteArrayWords(array);
	
	array = malloc(sizeof(arrayWords));					//correct	//get alphabetically smaller
	createArrayWords(array);
	word = malloc(sizeof(char)*(strlen("The")+1));
	strcpy(word,"The");
	insertArrayWords(array, word);
	
	info = maxCount(array, trie);	
	CuAssertStrEquals(tc,"max",info->type);
	CuAssertStrEquals(tc,"a",info->fileName);
	CuAssertIntEquals(tc,2,info->minOrMax);
	deleteArrayWords(array);
	free(info);
	
	
	
	
	
	destroyContainsTrie(containsTrie);

}

void TestWc(CuTest *tc){
	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));

	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	CuAssertIntEquals(tc, 0, createTrieFromFile(containsTrie, "wrongInput"));
	
	CuAssertIntEquals(tc, 1, createTrieFromFile(containsTrie, "./inputFiles/inputForTrie"));
	
	
	CuAssertIntEquals(tc, 1, createTrieFromFile(containsTrie, "./inputFiles/inputForTrie2"));
	CuAssertIntEquals(tc, 1, createTrieFromFile(containsTrie, "./inputFiles/inputForTrie3"));
	
	CuAssertIntEquals(tc,11,containsTrie->noOfTrieWords);

	
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
	
	BytesWordsLinesNode* summedUpInfo = wc(containsTrie);
	CuAssertPtrNotNull(tc,summedUpInfo);
	CuAssertStrEquals(tc, NULL, summedUpInfo->fileName);
	CuAssertIntEquals(tc, 104, summedUpInfo->bytes);	
	CuAssertIntEquals(tc, 14, summedUpInfo->words);	
	CuAssertIntEquals(tc, 15, summedUpInfo->lines);	
	
	free(summedUpInfo);
	
	destroyContainsTrie(containsTrie);
}


CuSuite* InstructionsGetSuite(){	//adding TestInstructions Functions into suite
	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestMaxCount);
    SUITE_ADD_TEST(suite, TestMinCount);
    SUITE_ADD_TEST(suite, TestWc);
    
    return suite;
}

