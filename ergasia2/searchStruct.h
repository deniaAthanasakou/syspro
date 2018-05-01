#ifndef _SEARCH_STRUCT_H_
#define _SEARCH_STRUCT_H_
#include <stdbool.h>

typedef struct SearchNode{		
	char* fileName;
	int lineNo;
	char* content;
}SearchNode;


typedef struct SearchStruct{		
	int length;					//initially is 5
	SearchNode* array; 		
	int position;				//position of first empty element
}SearchStruct;


SearchStruct* createSearchStruct();
int initializeSearchNode(SearchNode* node);
void insertIntoSearchStruct(SearchStruct* searchStruct, char* fileName, int line, char* content);
void printSearchStruct(SearchStruct* searchStruct);
void doubleSearchStruct(SearchStruct* searchStruct);
void destroySearchStruct(SearchStruct* searchStruct);
char* getStringForPrint(SearchStruct* searchStruct, int deadLine);

#endif
