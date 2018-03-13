#ifndef _MAP_H_
#define _MAP_H_

typedef struct MapNode{
	int id; 
	char* text;
}MapNode;

typedef struct Map{
	int length;					//initially is 5
	MapNode* array; 
	int position;				//position of first empty element
}Map;

Map* createMap();
void insertIntoMap(Map* map, int id, char* text);
void printMap(Map* map);
void doubleMap(Map* map);
void reduceMapLength(Map* map);
int getNoOfWordsOfMapText(Map* map);
int getNoOfAllWords(Map* map);
MapNode* getMapNode(Map* map, int id, int first, int last);
void destroyMap(Map* map);

#endif
