#ifndef CU_TEST_QUEUE_H
#define CU_TEST_QUEUE_H
#include "CuTest.h"
#include "../webCrawler/queue.h"

void TestInsert(CuTest *tc);
void TestDelete(CuTest *tc);

CuSuite* QueueGetSuite();

#endif
