#ifndef _POSTING_LIST_H_
#define _POSTING_LIST_H_
#include <stdbool.h>
#include "documentIdsHandler.h"

typedef struct OccurrencesInText OccurrencesInText;

struct OccurrencesInText{	//listNode
	int textId;
	int occurrences;
	OccurrencesInText* next;
};

typedef struct postingList{
	int documentFreq;		//size
	OccurrencesInText* firstNode;
}postingList;

void createPostingList(postingList* pL);
void insertIntoPostingList(postingList* pL, int textId);
OccurrencesInText* searchForId(postingList* pL,int id);
OccurrencesInText* getNodeById(postingList* pL,int id);

void printPostingList(postingList* pL);
void destroyPostingList(postingList* pL);

void getDifferentIds(postingList* pL, DifferentIds* diffIds);
#endif
