#ifndef _PRINT_FOR_SEARCH_H_
#define _PRINT_FOR_SEARCH_H_

typedef struct PrintForSearchNode{
	int textId;
	double score;
	char* text;
}PrintForSearchNode;

typedef struct PrintForSearch{
	int length;	//initially 10
	int position;
	PrintForSearchNode* array;
}PrintForSearch;


void initializePrintForSearch(PrintForSearch* pfs);
void initializePrintForSearchNode(PrintForSearchNode* node);
void doublePrintForSearch(PrintForSearch* pfs);

void insertionSortPrintForSearch(PrintForSearch* pfs, int textId, double score, char* text);
int binaryPrintForSearch(PrintForSearchNode* array, double score, int first, int last, int realLastElement);


void deletePrintForSearch(PrintForSearch* pfs);
void printPrintForSearchElements(PrintForSearch* pfs);

void printKResultsDESC(PrintForSearch* pfs, int topK);


#endif
