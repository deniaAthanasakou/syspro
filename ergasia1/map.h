#ifndef _MAP_H_
#define _MAP_H_

typedef struct MapNode{
	int id; 
	char* text;
	int noOfWords;
}MapNode;

typedef struct Map{		
	int length;					//initially is 5
	MapNode* array; 
	int position;				//position of first empty element
	int noOfWordsFull;			// number of words that all map nodes contains
}Map;



Map* createMap();
int getMapFromFile(FILE* file, Map* map);
void insertIntoMap(Map* map, int id, char* text);
void printMap(Map* map);
void doubleMap(Map* map);
void reduceMapLength(Map* map);
int getNoOfWordsOfMapText(MapNode* node);
int getNoOfAllWords(Map* map);
void destroyMap(Map* map);

#endif
