#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_
#include "arrayWords.h"
#include "trie.h"

typedef struct FileInfoMinMax{
	char* fileName;
	int minOrMax;
	char* type;		//value is "min" or "max"
}FileInfoMinMax;




FileInfoMinMax* maxCount(char* text, Trie* trie);
FileInfoMinMax* minCount(char* text, Trie* trie);

BytesWordsLinesNode* wc(ContainsTrie* trie);

#endif
