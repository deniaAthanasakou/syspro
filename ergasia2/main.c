#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include  <sys/stat.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <fcntl.h>  // for open
#include <unistd.h> // for close
#include "pathStruct.h"
#include "process.h"
#include "trie.h"

#define PERMS   0666
extern int errno;


char *mystring = "This is a test only";

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
			numWorkers=atoi(argv[i+1]);						//argument before number of workers should be -w
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
	

	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));
	initializeContainsTrie(&containsTrie);
	

	int dirsPerWorker = pathStruct->length / numWorkers;
	int numOfExtraDirs = pathStruct->length % numWorkers;
	int counterForExtraDirs = 0;
	printf("dirsPerWorker = %d, numOfExtraDirs = %d\n",dirsPerWorker,numOfExtraDirs);
	
	pid_t childpid, mainId = getpid();
	int status = 0;
	int counterForPaths = 0;
	
	int noOfProcess = 0;
	
	int readfd=0, writefd=0;
	FIFOS fifosUsed[numWorkers];
	for(int i=0; i<numWorkers; i++){
		//create stringNames for fifos
 		char FIFO1[50];
 		char FIFO2[50];
 		
		sprintf(FIFO1, "./tmp/FIFOW_%d", i+1);
		sprintf(FIFO2, "./tmp/FIFOR_%d", i+1);
	 
		// Print the string stored in buffer and
		// character count
		printf("%s %s\n",FIFO1,FIFO2);
	
	
		if ( (mkfifo(FIFO1, PERMS) < 0) && (errno != EEXIST) ) {		//create fifo1
		   perror("Error! Can't create fifo.");
		   exit(1);
		}
		if ((mkfifo(FIFO2, PERMS) < 0) && (errno != EEXIST)) {			//create fifo2
		   unlink(FIFO1);
		   perror("Error! Can't create fifo.");
		   exit(1);
		}
	
		if ( (readfd = open(FIFO1, O_RDWR))  < 0)  {
			  perror("server: can't open read fifo");
			  exit(1);
		}
	 
	   if ( (writefd = open(FIFO2, O_RDWR))  < 0)  {
		  perror("server: can't open write fifo");
		  exit(1);
		}
	
		fifosUsed[i].readfd=readfd;
		fifosUsed[i].writefd=writefd;
	}
	
	
	

	
	
	
	for(int i=0; i<numWorkers; i++){
		//process
		
		childpid = fork();
		if (childpid == -1){		//error
			perror("Failed to fork");
			exit(1);
		}
		else if (childpid == 0){			//child
		
		
		
			
		
			//printf("else writefd %d readfd %d\n", writefd, readfd);
		
		
			noOfProcess = i;
			printf("I am the child process with ID: %ld\n", (long)getpid());
			//do job for child

			/*int id = getpid();
			insertIdIntoProcessStruct(procStr, id);	
			*/
			int dirs = dirsPerWorker;
			if(i<numOfExtraDirs){
				dirs++;
			}
			for(int j=0; j<dirs; j++){			//for each directory
				
				if(createTrieFromDir(containsTrie, pathStruct->arrayOfPaths[counterForPaths])==0)
					exit(1);
	
				counterForPaths++;
			}
			counterForExtraDirs++;
			break;
		}
		else{						//parent
			counterForPaths+=dirsPerWorker;
			if(i<numOfExtraDirs){
				counterForPaths++;
				counterForExtraDirs++;
			}
			printf("I am the parent process with ID: %ld\n", (long)getpid());
		}

	}
	pid_t currentId = getpid();
	if(mainId==currentId){				//parent process
								
		//read user input for queries
		char *line = NULL;
		size_t len = 0;
		int continueLoop = 1;
		while(continueLoop==1 && getline(&line, &len, stdin) != -1){
			if(strcmp(line,"\n")==0)
				continue;
			continueLoop = server(fifosUsed, numWorkers, line);			//must give fullLine
			
		}
		if(line){
			free(line);
			line = NULL;
		}
		
		
		for(int i=0; i<numWorkers; i++){			//close fifos
			close(fifosUsed[i].readfd);													
			close(fifosUsed[i].writefd);	

		}
		
	}
	else{	//child
	
		char nameOfFile[20];
		sprintf(nameOfFile, "log/Worker_%ld", (long)getpid());
		printf("nameOfFile '%s'\n",nameOfFile );
		FILE *workerFile = fopen(nameOfFile, "w");
		if(workerFile==NULL){
			perror("Error! Log file could not be opened");
			exit(1);
		}
	 	while(client(fifosUsed[noOfProcess].writefd, fifosUsed[noOfProcess].readfd, containsTrie, workerFile)){
		}
		fclose(workerFile);
		

		
	}
	
	
	//while (wait(&status) > 0){
	//	printf("waiting in while\n");	
	//}
	destroyPathStruct(pathStruct);
	destroyContainsTrie(containsTrie);
	return 0;
	
	
}
