#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestMap.h"


/*
void TestInsertIntoMap(CuTest *tc){		//oldVersion

	Map* map = createMap();
	char* fileName = (char*)malloc((strlen("./inputFiles/inputForTrie")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie");
	insertIntoMap(map, fileName);
	
	fileName = (char*)malloc((strlen("./inputFiles/inputForTrie2")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie2");
	insertIntoMap(map, fileName);
	
	fileName = (char*)malloc((strlen("./inputFiles/inputForTrie3")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie3");
	insertIntoMap(map, fileName);
	
	CuAssertIntEquals(tc, 5, map->length);
	CuAssertIntEquals(tc, 3, map->position);
	
	CuAssertIntEquals(tc, 6, map->array[0].length);
	CuAssertIntEquals(tc, 6, map->array[0].position);
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie", map->array[0].fileName);
	CuAssertStrEquals(tc, "hello world", map->array[0].lineContents[0]);
	CuAssertStrEquals(tc, "     this    is   dog", map->array[0].lineContents[1]);
	CuAssertStrEquals(tc, "     ", map->array[0].lineContents[2]);
	CuAssertStrEquals(tc, "\0", map->array[0].lineContents[3]);
	CuAssertStrEquals(tc, "   dog  ", map->array[0].lineContents[4]);
	CuAssertStrEquals(tc, "  hello", map->array[0].lineContents[5]);
	
	CuAssertIntEquals(tc, 4, map->array[1].length);
	CuAssertIntEquals(tc, 4, map->array[1].position);
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie2", map->array[1].fileName);
	CuAssertStrEquals(tc, "kow", map->array[1].lineContents[0]);
	CuAssertStrEquals(tc, "you", map->array[1].lineContents[1]);
	CuAssertStrEquals(tc, "dog", map->array[1].lineContents[2]);
	CuAssertStrEquals(tc, "    amazing", map->array[1].lineContents[3]);
	
	CuAssertIntEquals(tc, 5, map->array[2].length);
	CuAssertIntEquals(tc, 5, map->array[2].position);
	CuAssertStrEquals(tc, "./inputFiles/inputForTrie3", map->array[2].fileName);
	CuAssertStrEquals(tc, "love", map->array[2].lineContents[0]);
	CuAssertStrEquals(tc, "	me", map->array[2].lineContents[1]);
	CuAssertStrEquals(tc, "	", map->array[2].lineContents[2]);
	CuAssertStrEquals(tc, "	", map->array[2].lineContents[3]);
	CuAssertStrEquals(tc, " parder	", map->array[2].lineContents[4]);

	fileName = (char*)malloc((strlen("./inputFiles/inputForTrie2")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie2");
	insertIntoMap(map, fileName);
	
	fileName = (char*)malloc((strlen("./inputFiles/inputForTrie2")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie2");
	insertIntoMap(map, fileName);
	
	fileName = (char*)malloc((strlen("./inputFiles/inputForTrie2")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie2");
	insertIntoMap(map, fileName);
	
	CuAssertIntEquals(tc, 10, map->length);
	CuAssertIntEquals(tc, 6, map->position);
	
	destroyMap(map);
	
}*/

void TestInsertIntoMap(CuTest *tc){

	Map* map = createMap();
	char* fileName = (char*)malloc((strlen("./inputFiles/inputForTrie")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie");
	CuAssertPtrNotNull(tc,insertIntoMap(map, fileName));
	
	
	fileName = (char*)malloc((strlen("./inputFiles/inputForTrie2")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie2");
	CuAssertPtrNotNull(tc,insertIntoMap(map, fileName));
	
	fileName = (char*)malloc((strlen("./inputFiles/inputForTrie3")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie3");
	CuAssertPtrNotNull(tc,insertIntoMap(map, fileName));
	
	CuAssertIntEquals(tc, 5, map->length);
	CuAssertIntEquals(tc, 3, map->position);
	
	fileName = (char*)malloc((strlen("./inputFiles/inputForTrie2")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie2");
	CuAssertPtrNotNull(tc,insertIntoMap(map, fileName));
	
	fileName = (char*)malloc((strlen("./inputFiles/inputForTrie2")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie2");
	CuAssertPtrNotNull(tc,insertIntoMap(map, fileName));
	
	fileName = (char*)malloc((strlen("./inputFiles/inputForTrie2")+1)*sizeof(char));
	strcpy(fileName, "./inputFiles/inputForTrie2");
	CuAssertPtrNotNull(tc,insertIntoMap(map, fileName));
	
	CuAssertIntEquals(tc, 10, map->length);
	CuAssertIntEquals(tc, 6, map->position);
	
	destroyMap(map);

}

void TestInsertIntoMapNode(CuTest *tc){
	MapNode* node = malloc(sizeof(MapNode));
	initializeMapNode(node);
	
	char* text = malloc((strlen("Hello")+1)*sizeof(char));
	strcpy(text, "Hello");
	
	insertIntoMapNode(node, text);
	free(text);
	
	CuAssertIntEquals(tc, 5, node->length);
	CuAssertIntEquals(tc, 1, node->position);
	CuAssertStrEquals(tc, "Hello", node->lineContents[0]);
	
	text = malloc((strlen("world")+1)*sizeof(char));
	strcpy(text, "world");
	
	insertIntoMapNode(node, text);
	free(text);
	
	CuAssertIntEquals(tc, 5, node->length);
	CuAssertIntEquals(tc, 2, node->position);
	CuAssertStrEquals(tc, "world", node->lineContents[1]);
	
	text = malloc((strlen("this")+1)*sizeof(char));
	strcpy(text, "this");
	
	insertIntoMapNode(node, text);
	free(text);
	
	CuAssertIntEquals(tc, 5, node->length);
	CuAssertIntEquals(tc, 3, node->position);
	CuAssertStrEquals(tc, "this", node->lineContents[2]);
	
	text = malloc((strlen("is")+1)*sizeof(char));
	strcpy(text, "is");
	
	insertIntoMapNode(node, text);
	free(text);
	
	CuAssertIntEquals(tc, 5, node->length);
	CuAssertIntEquals(tc, 4, node->position);
	CuAssertStrEquals(tc, "is", node->lineContents[3]);
	
	text = malloc((strlen("Denia")+1)*sizeof(char));
	strcpy(text, "Denia");
	
	insertIntoMapNode(node, text);
	free(text);
	
	CuAssertIntEquals(tc, 5, node->length);
	CuAssertIntEquals(tc, 5, node->position);
	CuAssertStrEquals(tc, "Denia", node->lineContents[4]);
	
	text = malloc((strlen("bye")+1)*sizeof(char));
	strcpy(text, "bye");
	
	insertIntoMapNode(node, text);
	free(text);
	
	CuAssertIntEquals(tc, 10, node->length);
	CuAssertIntEquals(tc, 6, node->position);
	CuAssertStrEquals(tc, "bye", node->lineContents[5]);
	
	destroyMapNode(node);
	free(node);
	node=NULL;
	
}


CuSuite* MapGetSuite(){				//adding TestMap Functions into suite
	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsertIntoMap);
    SUITE_ADD_TEST(suite, TestInsertIntoMapNode);
    
    return suite;
}

