#ifndef CU_TEST_MAP_H
#define CU_TEST_MAP_H
#include "CuTest.h"
#include "../map.h"

void TestInsertIntoMap(CuTest *tc);
void TestInsertIntoMapNode(CuTest *tc);

CuSuite* MapGetSuite();

#endif

