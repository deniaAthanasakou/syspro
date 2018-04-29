#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_
#include <stdbool.h>
#include "arrayWords.h"
#include "trie.h"
#include "searchStruct.h"

typedef struct FileInfoMinMax{
	char* fileName;
	int minOrMax;
	char* type;		//value is "min" or "max"
}FileInfoMinMax;


SearchStruct* search(char* text, ContainsTrie* containsTrie);

FileInfoMinMax* maxCount(char* text, Trie* trie);
FileInfoMinMax* minCount(char* text, Trie* trie);

BytesWordsLinesNode* wc(ContainsTrie* trie);

bool lineAlreadyExists(int* array, int size, int line);

#endif
