#ifndef _MAP_H_
#define _MAP_H_

typedef struct MapNode{
	char* fileName; 
	char** lineContents;
	int position;				//position of first empty element
	int length;					//initially is 5
}MapNode;

typedef struct Map{		
	int length;					//initially is 5
	MapNode* array; 
	int position;				//position of first empty element
}Map;

//functions for MapNode
void insertIntoMapNode(MapNode* node, char* text);
void initializeMapNode(MapNode* node);
void doubleMapNode(MapNode* node);
void destroyMapNode(MapNode* node);
void reduceMapNodeArrayLength(MapNode* node);
void printMapNode(MapNode* node);


//functions for Map
Map* createMap();
MapNode* insertIntoMap(Map* map, char* fileName);
void printMap(Map* map);
void doubleMap(Map* map);
void destroyMap(Map* map);
char* getLineOfFile(Map* map, char* fileName, int line);
MapNode* getNodeBasedOnFileName(Map* map, char* fileName);


#endif
