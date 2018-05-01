#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <limits.h>
#include <time.h>
#include "process.h"
#include "instructions.h"
#include "printLog.h"

#define BUFFSIZE 50000

int server(FIFOS* fifosUsed, int numWorkers, char* queryLine) {

	//printf("in server strlen(queryLine) %ld\n", strlen(queryLine));
	
	int sumBytes = 0, sumWords = 0, sumLines = 0;
	int wcFlag = 0;
	
	int minCountFlag=0, min = INT_MAX;
	char* minFilename = malloc(1);
	minFilename[0] = '\0';
	
	int maxCountFlag=0, max = 0;
	char* maxFilename = malloc(1);
	maxFilename[0] = '\0';
	
	int exitFlag=0;
	
	int searchFlag=0, searchWorkersReplied = numWorkers;
	clock_t begin = clock();
	
	
	for(int i=0; i<numWorkers; i++){
		if ( write(fifosUsed[i].writefd, queryLine, strlen(queryLine)) != strlen(queryLine)) { 
		    printf("server: error in write\n");
		}
		
		
		char buffer[BUFFSIZE];
		int length;
		 if( (length = read(fifosUsed[i].readfd, buffer, BUFFSIZE) ) > 0) {
		 	buffer[length] = '\0';
		 	
		 	char* instruction = strtok(buffer,"|");
			char* remainingLine = strtok(NULL,"");	
		 	
		 
		 	if(strcmp(instruction,"search")==0){
		 		searchFlag = 1;
		 		int deadLine = atoi(strtok(remainingLine,"|"));
				int numberOfElements = atoi(strtok(NULL,"|"));
				
				printf("deadLine is %d\n", deadLine);
				//if(late){
				//	searchWorkersReplied--;
				//}
				
				double time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
				if(time_spent>deadLine){
					searchWorkersReplied--;
				}
				else{
					for(int counter = 0; counter<numberOfElements; counter++){
						char* fullLine = strtok(NULL,"\n");	
					
						printf("%s\n", fullLine);
					}
				}
				
				
			}
			else if(strcmp(instruction,"maxcount")==0){
				maxCountFlag=1;
				char* fileName = strtok(remainingLine,",");	
				int newMax = atoi(strtok(NULL,"\n"));	
				if(newMax>max){
					max = newMax;
					maxFilename = realloc(maxFilename, (strlen(fileName)+1)*sizeof(char));
					strcpy(maxFilename, fileName);
				}
				else if(newMax == max){ 		//choose alphabetically smaller
					if(strcmp(maxFilename,"\0")==0){
						maxFilename = realloc(maxFilename, (strlen(fileName)+1)*sizeof(char));
					strcpy(maxFilename, fileName);					//initialization
					}
					else if(strcmp(fileName, maxFilename)<0){
						maxFilename = realloc(maxFilename, (strlen(fileName)+1)*sizeof(char));
						strcpy(maxFilename, fileName);
					}
				}
			
			}
			else if(strcmp(instruction,"mincount")==0){
				minCountFlag=1;
				char* fileName = strtok(remainingLine,",");	
				int newMin = atoi(strtok(NULL,"\n"));	
				if(newMin<min){
					min = newMin;
					minFilename = realloc(minFilename, (strlen(fileName)+1)*sizeof(char));
					strcpy(minFilename, fileName);
					//minFilename = fileName;
				}
				else if(newMin == min){ 		//choose alphabetically smaller
					if(strcmp(minFilename,"\0")==0){
						minFilename = realloc(minFilename, (strlen(fileName)+1)*sizeof(char));
						strcpy(minFilename, fileName);		//initialization
					}
					else if(strcmp(fileName, minFilename)<0){
						minFilename = realloc(minFilename, (strlen(fileName)+1)*sizeof(char));
						strcpy(minFilename, fileName);
					}
				}

			}
			else if(strcmp(instruction,"wc")==0){
				wcFlag=1;
				//printf("inside wc, remaining now is %s\n", remainingLine);
				char* bytes = strtok(remainingLine,",");	
				char* words = strtok(NULL,",");	
				char* lines = strtok(NULL,"\n");	
				
				sumBytes+=atoi(bytes);
				sumWords+=atoi(words);
				sumLines+=atoi(lines);
			}
			else if(strcmp(instruction,"exit")==0){
				exitFlag = 1;
			}
		
		}
    }
    if(searchFlag){
    	printf("Server: %d/%d workers replied on time.\n",searchWorkersReplied, numWorkers);
    }
    if(wcFlag){
    	printf("Server: Total number of bytes is: %d. Total number of words is: %d. Total number of lines is: %d.\n",sumBytes, sumWords, sumLines);
    }
    if(minCountFlag){
    	if(min == INT_MAX){
    		printf("Server: No file contains query word.\n");
    	}
    	else
    		printf("Server: Filename with minimum appearances of query is '%s'. Occurrences are '%d'\n",minFilename, min);
    }
     if(maxCountFlag){
    	if(max == 0){
    		printf("Server: No file contains query word.\n");
    	}
    	else
    		printf("Server: Filename with maximum appearances of query is '%s'. Occurrences are '%d'\n",maxFilename, max);
    }
  	free(minFilename);
  	free(maxFilename);
  
   return !exitFlag;
}


int client(int readfd, int writefd, ContainsTrie* containsTrie, int logFile) {
	
  	char line[MAXBUFF];
   	int length;
	//printf("in client\n");
	line[0] = '\0';
    if( (length = read(readfd, line, MAXBUFF) ) > 0) {
 	//	printf("client: BUFFER length  %d\n", length);
		line[length] = '\0';

		
		char* instruction = strtok(line," \t\n");
		char* remainingLine = strtok(NULL,"\n");	
		
		if(strcmp(instruction,"/search")==0 || strcmp(instruction,"\\search")==0){
			int deadLine = -1;
			char* queryLine = strtok(remainingLine,"-");
			char* lineForDeadLine = strtok(NULL,"\n");
			if(lineForDeadLine!=NULL){
				lineForDeadLine = strtok(lineForDeadLine," ");
				if(lineForDeadLine!=NULL && strcmp(lineForDeadLine, "d")==0){			//correct parameter
					char* rest = strtok(NULL," \t\n");
					deadLine = atoi(rest);
				}
			}
			if(deadLine>0){
			//	int late = 0;			//flag late is 1 if worker took more time than deadLine
				printf("queryLine '%s', deadLine '%d'\n", queryLine, deadLine);			
				char* queryLine2 = malloc((strlen(queryLine)+1)*sizeof(char));
				strcpy(queryLine2, queryLine);
				SearchStruct* info = search(queryLine, containsTrie);
				
				if(info!=NULL){
					
					printSystemTimeAndQuery(logFile, instruction);							//logfile
					printString(logFile, queryLine2);
					printPathsFromInfo(logFile, info);
					write(logFile, "\n", strlen("\n"));
					
					char* sendString = getStringForPrint(info, deadLine );

					if ( write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
						free(sendString);
						free(queryLine2);
						return 1;
					}
					free(sendString);
				
					destroySearchStruct(info);
				}
				else{
					if (write(writefd, "no input", strlen("no input")) != strlen("no input")) { 
						free(queryLine2);
						return 1;
					}
				}
				
				free(queryLine2);
				
			}
			else{
				printf("Wrong deadline type was given\n");
				if (write(writefd, "no input", strlen("no input")) != strlen("no input")) { 
					return 1;
				}
			}
			
		}
		else if(strcmp(instruction,"/maxcount")==0 || strcmp(instruction,"\\maxcount")==0){
			//printf("instruction is maxcount\n");
			
			FileInfoMinMax* info =  maxCount(remainingLine, containsTrie->firstNode);
			if(info!=NULL){
				//printf("%s %s %d\n", info->type, info->fileName, info->minOrMax);
				
				printSystemTimeAndQuery(logFile, instruction);							//logfile
				printString(logFile, remainingLine);
				char* winnerFile = malloc((strlen(info->fileName)+50)*sizeof(char));
				sprintf(winnerFile, "winner file %s : occurrences %d\n", info->fileName, info->minOrMax);
				printString(logFile, winnerFile);
				
				free(winnerFile);
				
				char* sendString = malloc((strlen(info->fileName)+1 + 20)*sizeof(char));
				sprintf(sendString, "maxcount|%s,%d", info->fileName, info->minOrMax);
				//printf("sendString=%s\n",sendString);
				
				if ( write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
				    free(sendString);
					return 1;
				}
				
				free(sendString);
				free(info->fileName);
				free(info);
				
			}
			else{
				char sendString[30];
				sprintf(sendString, "maxcount|%s,%d", "a", 0);
				//printf("sendString=%s\n",sendString);
				
				if ( write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
					return 1;
				}
			}
		}
		else if(strcmp(instruction,"/mincount")==0 || strcmp(instruction,"\\mincount")==0){
			FileInfoMinMax* info =  minCount(remainingLine, containsTrie->firstNode);
			if(info!=NULL){
				printSystemTimeAndQuery(logFile, instruction);							//logfile
				printString(logFile, remainingLine);
				char* winnerFile = malloc((strlen(info->fileName)+50)*sizeof(char));
				sprintf(winnerFile, "winner file %s : occurrences %d\n", info->fileName, info->minOrMax);
				printString(logFile, winnerFile);
				
				free(winnerFile);
				
				
				char* sendString = malloc((strlen(info->fileName)+1 + 20)*sizeof(char));
				sprintf(sendString, "mincount|%s,%d", info->fileName, info->minOrMax);
				//printf("sendString=%s\n",sendString);

				if ( write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
				    free(sendString);
					return 1;
				}
				free(sendString);
				free(info->fileName);
				free(info);
				
			}
			else{
				char sendString[30];
				sprintf(sendString, "mincount|%s,%d", "noFile", INT_MAX);
				//printf("sendString=%s\n",sendString);
				if (write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
					return 1;
				}
			}
		}
		else if(strcmp(instruction,"/wc")==0 || strcmp(instruction,"\\wc")==0){
			//printf("instruction is wc\n");
			BytesWordsLinesNode* info = wc(containsTrie);
			
			if(info!=NULL){
				//printf("Total Number of bytes is: %d. Total Number of words is: %d. Total Number of lines is: %d.\n",info->bytes, info->words, info->lines);
				
				
				
				printSystemTimeAndQuery(logFile, instruction);
				printPathsFromMap(logFile, containsTrie->mapOfFiles);
				//fprintf(logFile, "\n");
				char total[70];
				sprintf(total, "Total bytes = %d : Total words = %d : Total lines = %d", info->bytes, info->words, info->lines);
				printString(logFile, total);
				write(logFile, "\n", strlen("\n"));
				
				
				
				char sendString[50];
				sprintf(sendString, "wc|%d,%d,%d", info->bytes, info->words, info->lines);
				//printf("sendString=%s\n",sendString);
				
				if ( write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
					return 1;
				}
				free(info);
				
			}
			else{
				char* sendString = "no input";
				if ( write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
					return 1;
				}
			}
			
		}
		else if(strcmp(instruction,"/exit")==0 || strcmp(instruction,"\\exit")==0){
			if ( write(writefd, "exit", strlen("exit")) != strlen("exit")) { 
			   	return 1;
			}
        	return 0;
		}
		else{			//wrong input
			if (write(writefd, "no input", strlen("no input")) != strlen("no input")) { 
			   return 1;
			}
		}
		
    }
   return 1;

}


