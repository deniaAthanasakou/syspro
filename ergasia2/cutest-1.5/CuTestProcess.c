#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTestProcess.h"


void TestInsertIdIntoProcessStruct(CuTest *tc){
	ProcessStruct* pStruct = createProcessStruct();
	
	insertIdIntoProcessStruct(pStruct, 0);
	CuAssertIntEquals(tc,5,pStruct->length);
	CuAssertIntEquals(tc,1,pStruct->position);
	CuAssertIntEquals(tc,0,pStruct->processes[0].pid);
	
	insertIdIntoProcessStruct(pStruct, 2);
	CuAssertIntEquals(tc,5,pStruct->length);
	CuAssertIntEquals(tc,2,pStruct->position);
	CuAssertIntEquals(tc,0,pStruct->processes[0].pid);
	CuAssertIntEquals(tc,2,pStruct->processes[1].pid);
	
	insertIdIntoProcessStruct(pStruct, 3);
	CuAssertIntEquals(tc,5,pStruct->length);
	CuAssertIntEquals(tc,3,pStruct->position);
	CuAssertIntEquals(tc,0,pStruct->processes[0].pid);
	CuAssertIntEquals(tc,2,pStruct->processes[1].pid);
	CuAssertIntEquals(tc,3,pStruct->processes[2].pid);
	
	insertIdIntoProcessStruct(pStruct, 1);
	CuAssertIntEquals(tc,5,pStruct->length);
	CuAssertIntEquals(tc,4,pStruct->position);
	CuAssertIntEquals(tc,0,pStruct->processes[0].pid);
	CuAssertIntEquals(tc,1,pStruct->processes[1].pid);
	CuAssertIntEquals(tc,2,pStruct->processes[2].pid);
	CuAssertIntEquals(tc,3,pStruct->processes[3].pid);
	
	insertIdIntoProcessStruct(pStruct, 3);
	CuAssertIntEquals(tc,5,pStruct->length);
	CuAssertIntEquals(tc,4,pStruct->position);
	CuAssertIntEquals(tc,0,pStruct->processes[0].pid);
	CuAssertIntEquals(tc,1,pStruct->processes[1].pid);
	CuAssertIntEquals(tc,2,pStruct->processes[2].pid);
	CuAssertIntEquals(tc,3,pStruct->processes[3].pid);
	
	insertIdIntoProcessStruct(pStruct, 4);
	CuAssertIntEquals(tc,5,pStruct->length);
	CuAssertIntEquals(tc,5,pStruct->position);
	CuAssertIntEquals(tc,0,pStruct->processes[0].pid);
	CuAssertIntEquals(tc,1,pStruct->processes[1].pid);
	CuAssertIntEquals(tc,2,pStruct->processes[2].pid);
	CuAssertIntEquals(tc,3,pStruct->processes[3].pid);
	CuAssertIntEquals(tc,4,pStruct->processes[4].pid);
	
	insertIdIntoProcessStruct(pStruct, -1);
	CuAssertIntEquals(tc,10,pStruct->length);
	CuAssertIntEquals(tc,6,pStruct->position);
	CuAssertIntEquals(tc,-1,pStruct->processes[0].pid);
	CuAssertIntEquals(tc,0,pStruct->processes[1].pid);
	CuAssertIntEquals(tc,1,pStruct->processes[2].pid);
	CuAssertIntEquals(tc,2,pStruct->processes[3].pid);
	CuAssertIntEquals(tc,3,pStruct->processes[4].pid);
	CuAssertIntEquals(tc,4,pStruct->processes[5].pid);
	
	reduceProcessArrayLength(pStruct);
	CuAssertIntEquals(tc,6,pStruct->length);
	CuAssertIntEquals(tc,6,pStruct->position);
	
	destroyProcessStruct(pStruct);
	
}

void TestInsertPathIntoProcessStruct(CuTest *tc){
	ProcessStruct* pStruct = createProcessStruct();
	
	insertIdIntoProcessStruct(pStruct, 0);
	insertIdIntoProcessStruct(pStruct, 2);
	
	insertPathIntoProcessStruct(pStruct, 0, "hello");
	CuAssertIntEquals(tc,5,pStruct->processes[0].paths->length);
	CuAssertIntEquals(tc,1,pStruct->processes[0].paths->position);
	CuAssertStrEquals(tc,"hello",pStruct->processes[0].paths->arrayOfPaths[0]);
	
	insertPathIntoProcessStruct(pStruct, 0, "world");
	CuAssertIntEquals(tc,5,pStruct->processes[0].paths->length);
	CuAssertIntEquals(tc,2,pStruct->processes[0].paths->position);
	CuAssertStrEquals(tc,"world",pStruct->processes[0].paths->arrayOfPaths[1]);
	
	
	insertIdIntoProcessStruct(pStruct, 3);
	insertIdIntoProcessStruct(pStruct, 1);
	insertIdIntoProcessStruct(pStruct, 3);
	insertIdIntoProcessStruct(pStruct, 4);
	
	insertPathIntoProcessStruct(pStruct, 3, "this");
	CuAssertIntEquals(tc,5,pStruct->processes[3].paths->length);
	CuAssertIntEquals(tc,1,pStruct->processes[3].paths->position);
	CuAssertStrEquals(tc,"this", pStruct->processes[3].paths->arrayOfPaths[0]);
	
	insertPathIntoProcessStruct(pStruct, 1, "cat");
	CuAssertIntEquals(tc,5,pStruct->processes[1].paths->length);
	CuAssertIntEquals(tc,1,pStruct->processes[1].paths->position);
	CuAssertStrEquals(tc,"cat",pStruct->processes[1].paths->arrayOfPaths[0]);
	
	//insertIdIntoProcessStruct(pStruct, -1);
	/*CuAssertIntEquals(tc,10,pStruct->length);
	CuAssertIntEquals(tc,6,pStruct->position);
	CuAssertIntEquals(tc,-1,pStruct->processes[0].pid);
	CuAssertIntEquals(tc,0,pStruct->processes[1].pid);
	CuAssertIntEquals(tc,1,pStruct->processes[2].pid);
	CuAssertIntEquals(tc,2,pStruct->processes[3].pid);
	CuAssertIntEquals(tc,3,pStruct->processes[4].pid);
	CuAssertIntEquals(tc,4,pStruct->processes[5].pid);
	
	CuAssertIntEquals(tc,5,pStruct->processes[1].paths->length);
	CuAssertIntEquals(tc,2,pStruct->processes[1].paths->position);
	CuAssertStrEquals(tc,"hello",pStruct->processes[1].paths->arrayOfPaths[0]);
	CuAssertStrEquals(tc,"world",pStruct->processes[1].paths->arrayOfPaths[1]);
	
	CuAssertIntEquals(tc,5,pStruct->processes[4].paths->length);
	CuAssertIntEquals(tc,1,pStruct->processes[4].paths->position);
	CuAssertStrEquals(tc,"this", pStruct->processes[4].paths->arrayOfPaths[0]);
	
	CuAssertIntEquals(tc,5,pStruct->processes[2].paths->length);
	CuAssertIntEquals(tc,1,pStruct->processes[2].paths->position);
	CuAssertStrEquals(tc,"cat",pStruct->processes[2].paths->arrayOfPaths[0]);
	
	reduceProcessArrayLength(pStruct);
	CuAssertIntEquals(tc,6,pStruct->length);
	CuAssertIntEquals(tc,6,pStruct->position);
	*/
	destroyProcessStruct(pStruct);
}


CuSuite* ProcessGetSuite() {		//adding TestProcess Functions into suite
    CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestInsertIdIntoProcessStruct);
    SUITE_ADD_TEST(suite, TestInsertPathIntoProcessStruct); 
    
    return suite;
}
