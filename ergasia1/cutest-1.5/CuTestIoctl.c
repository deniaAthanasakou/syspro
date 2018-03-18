#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/ioctl.h>
#include "CuTestIoctl.h"


void TestIoctl(CuTest *tc){
	struct winsize w;
	int result = ioctl(0, TIOCGWINSZ, &w);
	printf("result = %d\n", result);
	printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
    
    for(int j=0; j<w.ws_col; j++){
		printf("^");
	}
	printf("\n");
    
}


CuSuite* IoctlGetSuite(){		//adding TestIoctl Functions into suite
	CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, TestIoctl);
    
    return suite;
}

