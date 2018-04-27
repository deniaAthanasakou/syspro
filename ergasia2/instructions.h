#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_
#include "arrayWords.h"
#include "trie.h"

typedef struct FileInfoMinMax{
	char* fileName;
	int minOrMax;
	char* type;		//value is "min" or "max"
}FileInfoMinMax;




FileInfoMinMax* maxCount(arrayWords* array, Trie* trie);
FileInfoMinMax* minCount(arrayWords* array, Trie* trie);

BytesWordsLinesNode* wc(ContainsTrie* trie);

#endif
