#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "CuTestQueue.h"
//#include "CuTestThread.h"


CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite();


void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
	
	
	//queue	
	CuSuite* queueSuite =  QueueGetSuite();
	CuSuiteAddSuite(suite, queueSuite);
	free(queueSuite);
	queueSuite=NULL;

	//thread	
/*	CuSuite* threadSuite =  ThreadGetSuite();
	CuSuiteAddSuite(suite, threadSuite);
	free(threadSuite);
	threadSuite=NULL;
	
*/
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
	

	CuStringDelete(output);
	
	CuSuiteDelete(suite);
	
}



int main(void)
{
	printf("Beginning of unit testing.\n");
	RunAllTests();
	printf("End of unit testing.\n");
}
