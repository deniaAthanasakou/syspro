#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"


Map* createMap(){
	Map* map = malloc(sizeof(Map));
	map->length = 5;
	map->position = 0;
	map->array = malloc(map->length*sizeof(MapNode));
	return map;
}
void insertIntoMap(Map* map, int id, char* text){
	MapNode node;
	node.id = id;
	node.text = text;
	
	
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
	
}

void reduceMapLength(Map* map){
	map->array = (MapNode*)realloc(map->array, map->position*sizeof(MapNode));
	map->length = map->position;
}



void printMap(Map* map){
	printf("Length of map-array is '%d'\n", map->length);
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
