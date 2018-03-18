#ifndef _PRINT_FOR_SEARCH_H_
#define _PRINT_FOR_SEARCH_H_
#include "arrayWords.h"

typedef struct PrintForSearchNode{
	int textId;
	double score;
	char* text;
}PrintForSearchNode;

typedef struct PrintForSearch{
	int length;					//initially 10
	int position;				//position of first empty element
	PrintForSearchNode* array;
	arrayWords* queryWords;		//words that should be checked for underlining
	int screenColumns;			//full screen width
	int spacesBeforeText;
}PrintForSearch;


void initializePrintForSearch(PrintForSearch* pfs, arrayWords* array);
void initializePrintForSearchNode(PrintForSearchNode* node);
void doublePrintForSearch(PrintForSearch* pfs);

void insertionSortPrintForSearch(PrintForSearch* pfs, int textId, double score, char* text);
int binaryPrintForSearch(PrintForSearchNode* array, double score, int first, int last, int realLastElement);

void deletePrintForSearch(PrintForSearch* pfs);
void printPrintForSearchElements(PrintForSearch* pfs);

void printKResultsDESC(PrintForSearch* pfs, int topK);


#endif
