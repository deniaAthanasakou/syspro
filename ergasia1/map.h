#ifndef _MAP_H_
#define _MAP_H_

typedef struct MapNode{
	int id; 
	char* text; 
}MapNode;

typedef struct Map{
	int length;					//number of elements inside array
	MapNode* array; 
}Map;

Map* createMap();
void insertIntoMap(Map* map, int id, char* text);
void printMap(Map* map);

#endif
