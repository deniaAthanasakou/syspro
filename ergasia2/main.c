#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "pathStruct.h"
#include "process.h"

int main (int argc,char* argv[]){
	if(argc<3 || argc>5 || argc==4){
		printf("Error! Wrong Number of Arguments.\n");
		exit(1);
	}
	char* fileName=NULL;
	int numWorkers=5;		//default
	for(int i=0; i<argc; i++){
		if(!strcmp(argv[i],"-d"))
			fileName=argv[i+1];							//argument before initialize file should be -d
		else if(!strcmp(argv[i],"-w"))
			numWorkers=atoi(argv[i+1]);						//argument before top-K results should be -w
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
	
	ProcessStruct* procStr = createProcessStruct(numWorkers);
	
	int dirsPerWorker = pathStruct->length / numWorkers;
	int numOfExtraDirs = pathStruct->length % numWorkers;
	int counterForExtraDirs = 0;
	printf("dirsPerWorker = %d, numOfExtraDirs = %d\n",dirsPerWorker,numOfExtraDirs);
	
	pid_t childpid,*ids;
	int status = 0;
	int counterForPaths = 0;
	
	
	ids = malloc(sizeof(pid_t)*numWorkers);
	int mainId = getpid();
	
	for(int i=0; i<numWorkers; i++){
		//process
		
		childpid = fork();
		if (childpid == -1){		//error
			perror("Failed to fork");
			exit(1);
		}
		else if (childpid == 0){			//child
			printf("I am the child process with ID: %ld\n", (long)getpid());
			//do job for child
			ids[i] = getpid();
			break;
		}
		else{						//parent
			counterForPaths+=dirsPerWorker;
			printf("I am the parent process with ID: %ld\n", (long)getpid());
			//printProcessStruct(procStr);
		}

	}
	
	int currentId = getpid();
	
	if(currentId == mainId){		//we are inside jobExecutor
		
		int i=0;
		while (ids[i] = waitpid(-1, NULL, 0)) {
   			if (errno == ECHILD) 
    	  		break;	
   			i++;	
		}
		printf("printing ids\n");
		for(int j=0; j<numWorkers; j++){
			printf("Id is %ld\n", (long)ids[j]);
			
			insertIdIntoProcessStruct(procStr, ids[j]);
		}
		
		
	}
	else{		//inside child
		printProcessStruct(procStr);
	}
	
	//printProcessStruct(procStr);
	//destroyProcessStruct(procStr);
	//destroyPathStruct(pathStruct);
	return 0;
	
	
}
