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
void binarySearchForDifferentIds(int* ids, int first, int last);
void printDifferentIds(DifferentIds* diffIds);

#endif
