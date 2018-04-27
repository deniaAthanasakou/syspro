#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestBytesWordsLinesInfo.h"


void TestInsertBytesWordsLinesInfo(CuTest *tc){
	BytesWordsLinesStruct* info = createBytesWordsLinesStruct();
	
	CuAssertIntEquals(tc, 0, info->position);
	insertBytesWordsLinesStruct(info, "a", 4, 5, 7);
	CuAssertIntEquals(tc, 5, info->length);
	CuAssertIntEquals(tc, 1, info->position);
	CuAssertStrEquals(tc, "a", info->array[0].fileName);
	CuAssertIntEquals(tc, 4, info->array[0].bytes);
	CuAssertIntEquals(tc, 5, info->array[0].words);
	CuAssertIntEquals(tc, 7, info->array[0].lines);	
	
	insertBytesWordsLinesStruct(info, "h", 3, 6, 3);
	CuAssertIntEquals(tc, 5, info->length);
	CuAssertIntEquals(tc, 2, info->position);
	CuAssertStrEquals(tc, "h", info->array[1].fileName);
	CuAssertIntEquals(tc, 3, info->array[1].bytes);
	CuAssertIntEquals(tc, 6, info->array[1].words);
	CuAssertIntEquals(tc, 3, info->array[1].lines);	
	
	insertBytesWordsLinesStruct(info, "6", 9, 5, 4);
	CuAssertIntEquals(tc, 5, info->length);
	CuAssertIntEquals(tc, 3, info->position);
	CuAssertStrEquals(tc, "6", info->array[2].fileName);
	CuAssertIntEquals(tc, 9, info->array[2].bytes);
	CuAssertIntEquals(tc, 5, info->array[2].words);
	CuAssertIntEquals(tc, 4, info->array[2].lines);	
	
	insertBytesWordsLinesStruct(info, "asd", 3, 5, 7);
	CuAssertIntEquals(tc, 5, info->length);
	CuAssertIntEquals(tc, 4, info->position);
	CuAssertStrEquals(tc, "asd", info->array[3].fileName);
	CuAssertIntEquals(tc, 3, info->array[3].bytes);
	CuAssertIntEquals(tc, 5, info->array[3].words);
	CuAssertIntEquals(tc, 7, info->array[3].lines);	
	
	insertBytesWordsLinesStruct(info, "j", 4, 9, 7);
	CuAssertIntEquals(tc, 5, info->length);
	CuAssertIntEquals(tc, 5, info->position);
	CuAssertStrEquals(tc, "j", info->array[4].fileName);
	CuAssertIntEquals(tc, 4, info->array[4].bytes);
	CuAssertIntEquals(tc, 9, info->array[4].words);
	CuAssertIntEquals(tc, 7, info->array[4].lines);	
	
	insertBytesWordsLinesStruct(info, "k", 4, 5, 25);
	CuAssertIntEquals(tc, 10, info->length);
	CuAssertIntEquals(tc, 6, info->position);
	CuAssertStrEquals(tc, "k", info->array[5].fileName);
	CuAssertIntEquals(tc, 4, info->array[5].bytes);
	CuAssertIntEquals(tc, 5, info->array[5].words);
	CuAssertIntEquals(tc, 25, info->array[5].lines);		
	
	deleteBytesWordsLinesStruct(info);
	
}

CuSuite* BytesWordsLinesInfoGetSuite(){		//adding TestBytesWordsLinesInfo Functions into suite
	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsertBytesWordsLinesInfo);
    
    return suite;
}


