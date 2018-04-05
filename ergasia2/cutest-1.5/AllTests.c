#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "CuTestProcess.h"
#include "CuTestPathStruct.h"

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite();


void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
	
	
	//process	
	CuSuite* processSuite =  ProcessGetSuite();
	CuSuiteAddSuite(suite, processSuite);
	free(processSuite);
	processSuite=NULL;
	
	//pathStruct	
	CuSuite* pathStructSuite =  PathStructGetSuite();
	CuSuiteAddSuite(suite, pathStructSuite);
	free(pathStructSuite);
	pathStructSuite=NULL;
	

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
