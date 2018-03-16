#ifndef _IDF_H_
#define _IDF_H_

typedef struct IdfForWordNode{
	double idf;
	char* word;
}IdfForWordNode;

typedef struct IdfForWords{
	int length;	//initially 10
	int position;
	IdfForWordNode* array;
}IdfForWords;


void initializeIdfForWords(IdfForWords* idfForWords, int length);
void initializeIdfForWordNode(IdfForWordNode* node);


IdfForWordNode* binarySearchIdfForWord(IdfForWordNode* array, char* word, int first, int last, int realLast); 	//returns NULL if not found
int binaryIdfForWord(IdfForWordNode* array, char* word, int first, int last, int realLast);
void insertionSortIdfForWords(IdfForWords* idfForWords, double idf, char* word);

void deleteIdfForWords(IdfForWords* idfForWords);
void printIdfForWordsElements(IdfForWords* idfForWords);


#endif
