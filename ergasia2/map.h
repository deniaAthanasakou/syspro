#ifndef _MAP_H_
#define _MAP_H_

typedef struct MapNode{
	char* fileName; 
	char** lineContent;
	int position;				//position of first empty element
	int length;					//initially is 5
}MapNode;

typedef struct Map{		
	int length;					//initially is 5
	MapNode* array; 
	int position;				//position of first empty element
}Map;

//functions for MapNode
void insertIntoMapNode(MapNode* mapArray, char* text);
void initializeMapNode(MapNode* node);
void doubleMapNode(MapNode* node);
int getMapNodesFromFile(FILE* file, MapNode* mapArray);




Map* createMap();
void insertNewIntoMap(Map* map, char* fileName, char* text);
void printMap(Map* map);
void doubleMap(Map* map);
void reduceMapLength(Map* map);
//int getNoOfWordsOfMapText(MapNode* node);
//int getNoOfAllWords(Map* map);
void destroyMap(Map* map);

#endif
