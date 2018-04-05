#ifndef CU_TEST_PROCESS_H
#define CU_TEST_PROCESS_H
#include "CuTest.h"
#include "../process.h"

void TestInsertIdIntoProcessStruct(CuTest *tc);
void TestInsertPathIntoProcessStruct(CuTest *tc);

void TestInsertPathStruct(CuTest *tc);

CuSuite* ProcessGetSuite();

#endif
