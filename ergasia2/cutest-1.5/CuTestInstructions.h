#ifndef CU_TEST_INSTRUCTIONS_H
#define CU_TEST_INSTRUCTIONS_H
#include "CuTest.h"
#include "../instructions.h"

void TestMaxCount(CuTest *tc);
void TestMinCount(CuTest *tc);
void TestWc(CuTest *tc);


CuSuite* InstructionsGetSuite();

#endif

