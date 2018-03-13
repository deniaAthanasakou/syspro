#ifndef CU_TEST_POSTING_LIST_H
#define CU_TEST_POSTING_LIST_H
#include "CuTest.h"
#include "../postingList.h"

void TestInsertPostingList(CuTest *tc);
void TestGetDifferentIds(CuTest *tc);

CuSuite* PostingListGetSuite();

#endif
