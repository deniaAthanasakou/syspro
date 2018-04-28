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
	
	char* line = malloc((strlen("brown red")+1)*sizeof(char));
	strcpy(line, "brown red");
	FileInfoMinMax* info = maxCount(line, trie);	
	CuAssertPtrEquals(tc,NULL,info);
	
	free(line);
	line=NULL;

	line = malloc((strlen("brown")+1)*sizeof(char));
	strcpy(line, "brown");
	info = maxCount(line, trie);
	CuAssertStrEquals(tc,"max",info->type);
	CuAssertStrEquals(tc,"d",info->fileName);
	CuAssertIntEquals(tc,3,info->minOrMax);
	free(info);
	free(line);
	line=NULL;

	
	line = malloc((strlen("This")+1)*sizeof(char));
	strcpy(line, "This");
	info = maxCount(line, trie);
	CuAssertStrEquals(tc,"max",info->type);
	CuAssertStrEquals(tc,"c",info->fileName);
	CuAssertIntEquals(tc,1,info->minOrMax);
	free(info);
	free(line);
	line=NULL;
	
	line = malloc((strlen("oups")+1)*sizeof(char));
	strcpy(line, "oups");
	info = maxCount(line, trie);
	CuAssertPtrEquals(tc,NULL,info);
	free(line);
	line=NULL;
	
	line = malloc((strlen("The")+1)*sizeof(char));
	strcpy(line, "The");
	info = maxCount(line, trie);
	CuAssertStrEquals(tc,"max",info->type);
	CuAssertStrEquals(tc,"a",info->fileName);
	CuAssertIntEquals(tc,2,info->minOrMax);
	free(info);
	free(line);
	line=NULL;
	
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
	
	char* word = malloc(sizeof(char)*(strlen("brown red")+1));
	strcpy(word,"brown red");
	FileInfoMinMax* info = minCount(word, trie);	
	CuAssertPtrEquals(tc,NULL,info);
	free(word);
	word = NULL;
	
	word = malloc(sizeof(char)*(strlen("brown")+1));
	strcpy(word,"brown");
	info = minCount(word, trie);	
	CuAssertStrEquals(tc,"min",info->type);
	CuAssertStrEquals(tc,"a",info->fileName);
	CuAssertIntEquals(tc,1,info->minOrMax);
	free(info);
	free(word);
	word = NULL;
	free(word);
	word = NULL;
	
	word = malloc(sizeof(char)*(strlen("This")+1));
	strcpy(word,"This");
	info = minCount(word, trie);		
	CuAssertStrEquals(tc,"min",info->type);
	CuAssertStrEquals(tc,"c",info->fileName);
	CuAssertIntEquals(tc,1,info->minOrMax);
	free(info);
	free(word);
	word = NULL;
	
	word = malloc(sizeof(char)*(strlen("oups")+1));
	strcpy(word,"oups");
	info = minCount(word, trie);
	CuAssertPtrEquals(tc,NULL,info);
	free(word);
	word = NULL;
	
	word = malloc(sizeof(char)*(strlen("The")+1));
	strcpy(word,"The");
	info = minCount(word, trie);
	CuAssertStrEquals(tc,"min",info->type);
	CuAssertStrEquals(tc,"a",info->fileName);
	CuAssertIntEquals(tc,2,info->minOrMax);
	free(info);
	free(word);
	word = NULL;

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

void TestSearch(CuTest *tc){


	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));
	initializeContainsTrie(&containsTrie);
	Trie* trie = containsTrie->firstNode;
	
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "b", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "This" , "c", 0, 0);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a", 1, 4);
	insertFullWordIntoTrie(containsTrie, trie, "brown" , "d", 2, 3);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "g", 4, 0);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "g", 4, 0);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "d", 3, 6);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a", 3, 6);
	insertFullWordIntoTrie(containsTrie, trie, "The" , "a", 0, 6);
	
	
	//create map
	char* fileName = (char*)malloc((strlen("a")+1)*sizeof(char));
	strcpy(fileName, "a");
	MapNode* node = insertIntoMap(containsTrie->mapOfFiles, fileName);
	insertIntoMapNode(node, "The wonderful life");
	insertIntoMapNode(node, " hello The life");
	insertIntoMapNode(node, " whatr");
	insertIntoMapNode(node, " up The The");
	
	fileName = (char*)malloc((strlen("g")+1)*sizeof(char));
	strcpy(fileName, "g");
	node = insertIntoMap(containsTrie->mapOfFiles, fileName);
	insertIntoMapNode(node, " what0");
	insertIntoMapNode(node, " what1");
	insertIntoMapNode(node, " what2");
	insertIntoMapNode(node, " what3");
	insertIntoMapNode(node, "The up life");
	
	fileName = (char*)malloc((strlen("d")+1)*sizeof(char));
	strcpy(fileName, "d");
	node = insertIntoMap(containsTrie->mapOfFiles, fileName);
	insertIntoMapNode(node, " what01");
	insertIntoMapNode(node, " what12");
	insertIntoMapNode(node, " brown brownnnnnnnnnnn");
	insertIntoMapNode(node, " uuuuuu The ");
	
	
	
	char* query = malloc((strlen("The what is brown This what The brown")+1)*sizeof(char));
	strcpy(query, "The what is brown This what The brown");
	printf("\n\nExecuting test for search\n\n");
	search(query, containsTrie);
	printf("\nTest for search ended\n\n");
	
	free(query);
	destroyContainsTrie(containsTrie);
	
}

CuSuite* InstructionsGetSuite(){	//adding TestInstructions Functions into suite
	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestMaxCount);
    SUITE_ADD_TEST(suite, TestMinCount);
    SUITE_ADD_TEST(suite, TestWc);
    SUITE_ADD_TEST(suite, TestSearch); 
    
    return suite;
}

