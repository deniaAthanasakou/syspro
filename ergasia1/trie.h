#ifndef _TRIE_H_
#define _TRIE_H_
#include <stdbool.h>
#include "map.h"
#include "postingList.h"
#include "arrayWords.h"

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
}ContainsTrie;


void initializeContainsTrie(ContainsTrie** containsTrie);
void initializeTrie(Trie** trie);
Trie* insertLetterIntoTrie(ContainsTrie* containsTrie, Trie* trie, char charForInsert, bool setPostingList, int id);		//returns node where element was inserted
void insertFullWordIntoTrie(ContainsTrie* containsTrie, Trie* trie, char* word, int id);
bool letterExists(Trie* trie, char charForInsert);
Trie* getSameLetterNode(Trie* trie, char charForInsert);	//goes through trie horrizontally and if charForInsert is not found returns first Null node 
void insertLineTextIntoTrie(ContainsTrie* containsTrie, Trie* trie, char* line, int id);
void InsertAllLinesIntoTrie(ContainsTrie* containsTrie, Map* map);

Trie* horizontalTraversal(Trie* trie, char charForInsert);
postingList* searchWordInTrie(Trie* trie, char* word);	//for now like bool

void printTrieHorizontally(Trie* trie);
void printTrieVertically(Trie* trie);

void destroyContainsTrie(ContainsTrie* containsTrie);
void destroyTrie(Trie* trie);
void destroySingleNode(Trie* trie);

arrayWords* getAllWordsOfTrie(Trie* trie);
char* recGetWordsFromTrie(Trie* originalTrie, Trie* trie, char* word, arrayWords* array);

double getScoreWithoutSum(Trie* trie, Map* map, double idf, char* word, int textId, int avgdl); 

#endif
