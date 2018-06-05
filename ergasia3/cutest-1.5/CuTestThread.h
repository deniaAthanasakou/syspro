#ifndef CU_TEST_THREAD_H
#define CU_TEST_THREAD_H
#include "CuTest.h"
#include "../webServer/thread.h"

void TestCreateThreadPool(CuTest *tc);
void TestInsertFds(CuTest *tc);
void TestGetFdToThread(CuTest *tc);


CuSuite* ThreadGetSuite();

#endif
