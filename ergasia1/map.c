#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"


Map* createMap(){
	Map* map = malloc(sizeof(Map));
	map->length = 0;
	map->array = malloc(map->length*sizeof(MapNode));
	return map;
}
void insertIntoMap(Map* map, int id, char* text){
	MapNode node;
	node.id = id;
	node.text = text;
	
	map->length++;
	map->array = (MapNode*)realloc(map->array, map->length*sizeof(MapNode));
	map->array[map->length-1] = node;
	
	
}


void printMap(Map* map){
	printf("Length of map-array is '%d'\n", map->length);
	for(int i=0; i<map->length; i++){
		printf("id '%d', text '%s'\n", map->array[i].id,map->array[i].text);
	}
}
