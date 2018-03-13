#ifndef _DOCUMENT_IDS_HANDLER_H_
#define _DOCUMENT_IDS_HANDLER_H_

typedef struct DifferentIds{
	int length;				//length of array of strings (initially 10)
	int* ids;				//array of strings
	int position;			//position of first null element
}DifferentIds;

void createDifferentIds(DifferentIds *diffIds);
void destroyDifferentIds(DifferentIds *diffIds);
void doubleDifferentIds(DifferentIds *diffIds);
void insertionSortDifferentIds(DifferentIds *diffIds, int newId);
int binarySearchForDifferentIds(int* ids, int item,int first, int last, int realLastElement);
void printDifferentIds(DifferentIds* diffIds);

#endif
