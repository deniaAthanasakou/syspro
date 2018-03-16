#ifndef _QUERY_H_
#define _QUERY_H_
#include "methods.h"
#include "map.h"
#include "trie.h"


int search(arrayWords* array, Map* map, ContainsTrie* containsTrie);
void documentFrequency(arrayWords* array, Trie* trie);
void termFrequency(arrayWords* array, Trie* trie);




#endif
