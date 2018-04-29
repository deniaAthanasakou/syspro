#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "CuTestPathStruct.h"
#include "CuTestTrie.h"
#include "CuTestPostingList.h"
#include "CuTestList.h"
#include "CuTestInstructions.h"
#include "CuTestBytesWordsLinesInfo.h"
#include "CuTestMap.h"

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite();


void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
	
	//pathStruct	
	CuSuite* pathStructSuite =  PathStructGetSuite();
	CuSuiteAddSuite(suite, pathStructSuite);
	free(pathStructSuite);
	pathStructSuite=NULL;
	
	//trie	
	CuSuite* trieSuite =  TrieGetSuite();
	CuSuiteAddSuite(suite, trieSuite);
	free(trieSuite);
	trieSuite=NULL;
	
	//postingList	
	CuSuite* postingListSuite =  PostingListGetSuite();
	CuSuiteAddSuite(suite, postingListSuite);
	free(postingListSuite);
	postingListSuite=NULL;
	
	//list	
	CuSuite* listSuite =  ListGetSuite();
	CuSuiteAddSuite(suite, listSuite);
	free(listSuite);
	listSuite=NULL;
	
	//instructions	
	CuSuite* instructionsSuite =  InstructionsGetSuite();
	CuSuiteAddSuite(suite, instructionsSuite);
	free(instructionsSuite);
	instructionsSuite=NULL;
	
	//bytesWordsLinesInfo
	CuSuite* bytesWordsLinesInfoSuite =  BytesWordsLinesInfoGetSuite();
	CuSuiteAddSuite(suite, bytesWordsLinesInfoSuite);
	free(bytesWordsLinesInfoSuite);
	bytesWordsLinesInfoSuite=NULL;
	
	//map
	CuSuite* mapSuite =  MapGetSuite();
	CuSuiteAddSuite(suite, mapSuite);
	free(mapSuite);
	mapSuite=NULL;
	

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
