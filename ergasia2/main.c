#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "pathStruct.h"

int main (int argc,char* argv[]){
	if(argc<3 || argc>5 || argc==4){
		printf("Error! Wrong Number of Arguments.\n");
		exit(1);
	}
	char* fileName=NULL;
	int numWorkers=5;		//default
	for(int i=0; i<argc; i++){
		if(!strcmp(argv[i],"-d"))
			fileName=argv[i+1];							//argument before initialize file should be -i
		else if(!strcmp(argv[i],"-w"))
			numWorkers=atoi(argv[i+1]);						//argument before top-K results should be -k
	}
	
	if(fileName==NULL){
		printf("Error! No file was given.\n");
		exit(1);
	}
	if(numWorkers<=0){
		printf("Error! Invalid value for number of processes.\n");
		exit(1);
	}
	printf("NumWorkers = %d\n", numWorkers);
	
	//initialize
	FILE *docFile;
	docFile = fopen (fileName,"r");
	PathStruct* pathStruct = NULL;
	int init = 0;
	if (docFile!=NULL)
	{
		pathStruct = createPathStruct();
		init = initializeFromFile(docFile, pathStruct);
		fclose (docFile);
	}
	if (init==0){
		printf("Error! Null file was given.\n");
		exit(1);
	}
	
	//printPathStruct(pathStruct);
	if(pathStruct->length < numWorkers){
		numWorkers = pathStruct->length;
	}
	printf("after initialization NumWorkers = %d\n", numWorkers);
	
	pid_t childpid;
	for(int i=0; i<numWorkers; i++){
	
		childpid = fork();
		if (childpid == -1){
			perror("Failed to fork");
			return 1;
		}
		if (childpid == 0){
			printf("I am the child process\n");
			break;
		}
		else{
			printf("I am the parent process with ID: %lu \n", (long)getpid());
		}
	}
	
	
	destroyPathStruct(pathStruct);
	return 0;
	
	
}
