#ifndef _POSTING_LIST_H_
#define _POSTING_LIST_H_
#include <stdbool.h>
#include "list.h"


typedef struct postingListNode postingListNode;

struct postingListNode{	//listNode
	char* filePath;
	int occurrences;			//number of occurrences of word in filePath
	List* info;					//lines and offsets of word existance
	postingListNode* next;
};

typedef struct postingList{	
	int listSize;				//size
	postingListNode* firstNode;	
}postingList;

void createPostingList(postingList* pL);
void insertIntoPostingList(postingList* pL, char* path,  int lineOfWord, int wordOffset);
postingListNode* searchForPath(postingList* pL,char* path);

void printPostingList(postingList* pL);
void destroyPostingList(postingList* pL);

#endif
