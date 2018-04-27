#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

int getMapNodesFromFile(FILE* file, MapNode* mapArray){
	char *line = NULL;
	size_t len = 0;
	int read;
	if (file == NULL){
		printf("Error! Null file was given\n");
		return 0;
	}
	int counter=0;	
	while ((read = getline(&line, &len, file)) != -1) {
		
		
		//inserting lines into map
		char* text = malloc((strlen(line)+1)* sizeof(char));
		strcpy(text, line);
		insertIntoMapNode(mapArray, line);
		counter++;		
	}

	if (line){
		free(line);
		line=NULL;
	}
	return 1;
}

void insertIntoMapNode(MapNode* mapArray, char* text){
	
	if(mapArray->position+1==mapArray->length){
		doubleMapNode(mapArray);
	}
	mapArray->lineContent[mapArray->position] = text;
	mapArray->position++;
	
}

Map* createMap(){
	Map* map = malloc(sizeof(Map));
	map->length = 5;
	map->position = 0;
	map->array = malloc(map->length*sizeof(MapNode));
	for(int i=0; i<map->length; i++){
		initializeMapNode(&(map->array[i]));
	}
	return map;
}

void initializeMapNode(MapNode* node){
	node->length = 5;
	node->position = 0;
	node->lineContent = malloc(node->length*sizeof(char*));
}

void doubleMapNode(MapNode* node){
	node->length*=2;
	node->lineContent = (MapNode*)realloc(node->array, node->length*sizeof(MapNode));
	
}

void insertIntoMap(Map* map, char* fileName, char* text){
	MapNode node;
	node.fileName = fileName;
	
	FILE* fp = fopen(fileName, 'r')'
	getMapNodesFromFile(fp, node);
	if(map->position+1==map->length){
		doubleMap(map);
	}
	map->array[map->position] = node;
	map->position++;
	
}

void doubleMap(Map* map){
	int oldLength = map->length;
	map->length*=2;
	map->array = (MapNode*)realloc(map->array, map->length*sizeof(MapNode));
	for(int i=oldLength; i<map->length; i++){
		initializeMapNode(&(map->array[i]));
	}
	
}

void reduceMapLength(Map* map){
	map->array = (MapNode*)realloc(map->array, map->position*sizeof(MapNode));
	map->length = map->position;
}


int getNoOfWordsOfMapText(MapNode* node){		//returns the number of words that node->text contains
	char* word = malloc(sizeof(char)*(strlen(node->text)+1));
	strcpy(word, node->text); 
	char* pch;
	pch = strtok (word," \t");
	int noOfWords=0;
	while (pch != NULL)
	{	
		noOfWords++;
		pch = strtok (NULL, " \t");
	}
	if(word!=NULL)
		free(word);
	return noOfWords;
}


int getNoOfAllWords(Map* map){
	if(map->noOfWordsFull!=-1)
		return map->noOfWordsFull;
		
	int sum=0;
	for(int i=0; i<map->position; i++){
		sum+=map->array[i].noOfWords;
	}
	map->noOfWordsFull = sum;
	return sum;
}


void printMap(Map* map){
	printf("Printing map:\n");
	for(int i=0; i<map->position; i++){
		printf("id '%d', text '%s'\n", map->array[i].id,map->array[i].text);
	}
}

void destroyMap(Map* map){
	if(map!=NULL){
		for(int i=0; i<map->position; i++){
			free(map->array[i].text);
		}
		free(map->array);
		free(map);
		map=NULL;
	}
}
