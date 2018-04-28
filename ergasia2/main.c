#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include  <sys/stat.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include "pathStruct.h"
#include "process.h"
#include "trie.h"

#define MAXBUFF 1024
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
	
	//ProcessStruct* procStr = createProcessStruct(numWorkers);
	
	
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

	for(int i=0; i<numWorkers; i++){		//for each worker create 2 FIFO
 		//create stringNames for fifos
 		printf("in  main\n");
 		char FIFO1[50];
 		char FIFO2[50];
 		
		sprintf(FIFO1, "./tmp/FIFOW_%d", i+1);
		sprintf(FIFO2, "./tmp/FIFOR_%d", i+1);
	 
		// Print the string stored in buffer and
		// character count
		printf("%s %s\n",FIFO1,FIFO2);
		
		
		if ( (mkfifo(FIFO1, PERMS) < 0) && (errno != EEXIST) ) {		//create fifo1
		   perror("Error! Can't create fifo.");
		}
		if ((mkfifo(FIFO2, PERMS) < 0) && (errno != EEXIST)) {			//create fifo2
		   unlink(FIFO1);
		   perror("Error! Can't create fifo.");
		}

 	}
	
	
	
	
	
	
	
	for(int i=0; i<numWorkers; i++){
		//process
		
		childpid = fork();
		if (childpid == -1){		//error
			perror("Failed to fork");
			exit(1);
		}
		else if (childpid == 0){			//child
		
			noOfProcess = i+1;
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
			//printProcessStruct(procStr);
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
	int readfd, writefd;
	pid_t currentId = getpid();
	if(mainId==currentId){				//parent process
	
		//char* myString = malloc((strlen("This is a test string")+1)*sizeof(char));
		//strcpy(myString,"This is a test string");
		
		/* Create the FIFOs, then open them -- one for
		* reading and one for writing.
		*/
	 										
		//read user input for queries
		char *line = NULL;
		size_t len = 0;

		char* query = NULL;
		while(1){
	
			if(getline(&query, &len, stdin) != -1){
				char* instruction = strtok(query," \t\n");
				char* remainingLine = strtok(NULL,"\n");
				
	
				if(strcmp(instruction,"/exit")==0 || strcmp(instruction,"\\exit")==0)
					break;
				
				for(int i=0; i<numWorkers; i++){			//call server for each worker
		 	//	printf("int i = %d\n", i);
		 		//create stringNames for fifos
		 		char FIFO1[50];			//write
		 		char FIFO2[50];			//read
		 		
				sprintf(FIFO1, "./tmp/FIFOR_%d", i+1);
				sprintf(FIFO2, "./tmp/FIFOW_%d", i+1);
			 
			
				if ( (readfd = open(FIFO1, 0))  < 0)  {
				  perror("server: can't open read fifo");
				}
			 
			   if ( (writefd = open(FIFO2, 1))  < 0)  {
				  perror("server: can't open write fifo");
			   }
				//printf("calling server for %s %s\n",FIFO1,FIFO2);
				server(readfd, writefd, instruction);
		
				close(readfd);													//close FIFO1
		   		close(writefd);													//close FIFO2
				
	
				}
			}
		}
				
			/*	if(strcmp(instruction,"/search")==0 || strcmp(instruction,"\\search")==0){
					printf("instruction is search\n");
				}
				else if(strcmp(instruction,"/maxcount")==0 || strcmp(instruction,"\\maxcount")==0){
					printf("instruction is maxcount\n");
				}
				else if(strcmp(instruction,"/mincount")==0 || strcmp(instruction,"\\mincount")==0){
					printf("instruction is mincount\n");
				}
				else if(strcmp(instruction,"/wc")==0 || strcmp(instruction,"\\wc")==0){
					printf("instruction is wc\n");
				}
				else if(strcmp(instruction,"/exit")==0 || strcmp(instruction,"\\exit")==0){
					break;
				}
			}
				}
				break;
			}*/
		
	}
	else{	
		//sleep(5);
			//child
		//	printf("in  other\n");
		/* Open the FIFOs.  We assume server has already created them.  */
		char FIFO1[50];
	 	char FIFO2[50];
 		
		sprintf(FIFO1, "./tmp/FIFOR_%d", noOfProcess);
		sprintf(FIFO2, "./tmp/FIFOW_%d", noOfProcess);
	 
		//printf("%s %s\n",FIFO1,FIFO2);
		if ( (writefd = open(FIFO1, 1))  < 0)  {
		  perror("client: can't open write fifo \n");
	   }
	   if ( (readfd = open(FIFO2, 0))  < 0)  {
		  perror("client: can't open read fifo \n");
	   }


		client(readfd, writefd);

		close(readfd);													//close FIFO2
		close(writefd);													//close FIFO1

		/* Delete the FIFOs, now that we're done.  */
		//if exit
		/*if ( unlink(FIFO1) < 0) {
			perror("client: can't unlink \n");
		}
		if ( unlink(FIFO2) < 0) {
			perror("client: can't unlink \n");
		}
		*/
	}
	
	
	while (wait(&status) > 0);
	destroyPathStruct(pathStruct);
	destroyContainsTrie(containsTrie);
	return 0;
	
	
}
