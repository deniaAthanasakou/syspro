#ifndef _POSTING_LIST_H_
#define _POSTING_LIST_H_
#include <stdbool.h>


typedef struct postingListNode postingListNode;

struct postingListNode{	//listNode
	char* filePath;
	int occurrences;			//isws dn xreiazetai
	int line;				//grammh sthn opoia uparxei h leksh
	int wordOffset;
	postingListNode* next;
};

typedef struct postingList{	
	int listSize;		//size
	postingListNode* firstNode;	
}postingList;

void createPostingList(postingList* pL);
void insertIntoPostingList(postingList* pL, char* path,  int lineOfWord, int wordOffset);
postingListNode* searchForPath(postingList* pL,char* path);
//OccurrencesInText* getNodeById(postingList* pL,int id);

void printPostingList(postingList* pL);
void destroyPostingList(postingList* pL);

//void getDifferentIds(postingList* pL, DifferentIds* diffIds);
#endif
