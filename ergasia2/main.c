#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pathStruct.h"
#include "process.h"
#include "trie.h"

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

			/*int id = getpid();
			insertIdIntoProcessStruct(procStr, id);	
			*/
			int dirs = dirsPerWorker;
			if(i<numOfExtraDirs){
				dirs++;
			}
			for(int j=0; j<dirs; j++){			//for each directory
				printf("path %s\n",pathStruct->arrayOfPaths[counterForPaths]);
				//must get filenames
				//for each filename
					//open file
					//for each word
						//insert word and path into trie
				
				
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
	
	pid_t currentId = getpid();
	if(mainId==currentId){
		//read user input for queries
		/*char *line = NULL;
		size_t len = 0;

		char* query = NULL;
		while(1){
	
			if(getline(&query, &len, stdin) != -1){
				char* instruction = strtok(query," \t\n");
				char* remainingLine = strtok(NULL,"\n");
				//arrayWords* array = stringToArray(remainingLine);
				if(strcmp(instruction,"/search")==0 || strcmp(instruction,"\\search")==0){
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
					if (query){
						free(query);
						query=NULL;
					}
					//deleteArrayWords(array);
					break;
				}
				//deleteArrayWords(array);
			}
			else{
				if (query){
					free(query);
					query=NULL;
				}
				break;
			}
		}*/
	}
	
	
	while (wait(&status) > 0);
	//printProcessStruct(procStr);
	//destroyProcessStruct(procStr);
	//destroyPathStruct(pathStruct);
	//destroyContainsTrie(containsTrie)
	return 0;
	
	
}
