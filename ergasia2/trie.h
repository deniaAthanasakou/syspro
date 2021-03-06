#ifndef _TRIE_H_
#define _TRIE_H_
#include <stdbool.h>
#include "postingList.h"
#include "bytesWordsLinesInfo.h"
#include "map.h"

typedef struct Trie Trie;

struct Trie{
	char letter; 
	Trie* verticalNext;
	Trie* horizontalNext;
	postingList* pL;
};

typedef struct ContainsTrie{
	int noOfTrieWords;
	Trie* firstNode;
	BytesWordsLinesStruct* info;			//array
	Map* mapOfFiles;
}ContainsTrie;


void initializeContainsTrie(ContainsTrie** containsTrie);
void initializeTrie(Trie** trie);
Trie* insertLetterIntoTrie(ContainsTrie* containsTrie, Trie* trie, char charForInsert, bool setPostingList, char* path,  int lineOfWord, int wordOffset);		//returns node where element was inserted
void insertFullWordIntoTrie(ContainsTrie* containsTrie, Trie* trie, char* word, char* path, int lineOfWord, int wordOffset);
bool letterExists(Trie* trie, char charForInsert);
Trie* getSameLetterNode(Trie* trie, char charForInsert);	//goes through trie horrizontally and if charForInsert is not found returns first Null node 

Trie* horizontalTraversal(Trie* trie, char charForInsert);
postingList* searchWordInTrie(Trie* trie, char* word);	

void destroyContainsTrie(ContainsTrie* containsTrie);
void destroyTrie(Trie* trie);
void destroySingleNode(Trie* trie);

int createTrieFromFile(ContainsTrie* containsTrie, char* fullPath);
int createTrieFromDir(ContainsTrie* containsTrie, char* pathofDir);
#endif
