#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

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
	node->lineContents = malloc(node->length*sizeof(char*));
}

void destroyMap(Map* map){
	if(map!=NULL){
		for(int i=0; i<map->length; i++){
			if(i<map->position)
				free(map->array[i].fileName);
			destroyMapNode(&(map->array[i]));	
		}
		free(map->array);
		free(map);
		map=NULL;
	}
}

void destroyMapNode(MapNode* node){
	for(int i=0; i<node->position; i++){
		free(node->lineContents[i]);
	}
	free(node->lineContents);
}

void doubleMap(Map* map){
	int oldLength = map->length;
	map->length*=2;
	map->array = (MapNode*)realloc(map->array, map->length*sizeof(MapNode));
	for(int i=oldLength; i<map->length; i++){
		initializeMapNode(&(map->array[i]));
	}
	
}

void doubleMapNode(MapNode* node){
	node->length*=2;
	node->lineContents = (char**)realloc(node->lineContents, node->length*sizeof(char*));
	
}


void reduceMapNodeArrayLength(MapNode* node){
	node->lineContents = (char**)realloc(node->lineContents, node->position*sizeof(char*));
	node->length = node->position;
}

void printMap(Map* map){
	printf("Printing map:\n");
	for(int i=0; i<map->position; i++){
		printMapNode(&(map->array[i]));
	}
}

void printMapNode(MapNode* node){
	printf("Filename : %s\n", node->fileName);
	for(int i=0; i<node->position; i++){
		printf("line no %d : %s\n", i, node->lineContents[i]);
	}
}


MapNode* insertIntoMap(Map* map, char* fileName){


	if(map->position+1==map->length){
		doubleMap(map);
	}
	
	map->array[map->position].fileName = fileName;
	map->position++;
	
	return &(map->array[map->position-1]);
	
}

void insertIntoMapNode(MapNode* node, char* text){
	if(node->position==node->length){
		doubleMapNode(node);
	}
	
	node->lineContents[node->position] = malloc((strlen(text)+1)*sizeof(char));
	strcpy(node->lineContents[node->position], text);	
	node->position++;
}


MapNode* getNodeBasedOnFileName(Map* map, char* fileName){
	for(int i=0; i<map->position; i++){
		if(strcmp(map->array[i].fileName, fileName) == 0){
			return &(map->array[i]);
		}
	}
	return NULL;
}


char* getLineOfFile(Map* map, char* fileName, int line){

	MapNode* node = getNodeBasedOnFileName(map, fileName);
	
	if(node == NULL){					//doesn't exist
		return NULL;
	}
	
	if(line>=node->position){			//out of bounds
		return NULL;
	}
	return node->lineContents[line];


}










