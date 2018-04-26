#ifndef CU_TEST_TRIE_H
#define CU_TEST_TRIE_H
#include "CuTest.h"
#include "../trie.h"

void TestInsert(CuTest *tc);
void TestSearchWord(CuTest *tc);
void TestCreateTrieFromFile(CuTest *tc);


CuSuite* TrieGetSuite();

#endif

