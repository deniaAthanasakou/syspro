#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestPathStruct.h"



void TestInsertPathStruct(CuTest *tc){
	PathStruct* pathStruct = createPathStruct();
	
	insertIntoPathStruct(pathStruct, "a");
	insertIntoPathStruct(pathStruct, "b");
	insertIntoPathStruct(pathStruct, "c");
	insertIntoPathStruct(pathStruct, "d");
	insertIntoPathStruct(pathStruct, "a");
	CuAssertIntEquals(tc,5,pathStruct->length);
	CuAssertIntEquals(tc,5,pathStruct->position);
	CuAssertStrEquals(tc,"a",pathStruct->arrayOfPaths[0]);
	CuAssertStrEquals(tc,"b",pathStruct->arrayOfPaths[1]);
	CuAssertStrEquals(tc,"c",pathStruct->arrayOfPaths[2]);
	CuAssertStrEquals(tc,"d",pathStruct->arrayOfPaths[3]);
	CuAssertStrEquals(tc,"a",pathStruct->arrayOfPaths[4]);
	insertIntoPathStruct(pathStruct, "g");
	CuAssertIntEquals(tc,10,pathStruct->length);
	CuAssertIntEquals(tc,6,pathStruct->position);
	CuAssertStrEquals(tc,"g",pathStruct->arrayOfPaths[5]);
	
	reducePathArrayLength(pathStruct);
	destroyPathStruct(pathStruct);
}



CuSuite* PathStructGetSuite() {		//adding TestPathStructGetSuite Functions into suite
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestInsertPathStruct); 
    
    return suite;
}
