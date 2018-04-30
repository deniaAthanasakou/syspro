#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include "process.h"
#include <limits.h>
#include "instructions.h"

#define BUFFSIZE 1024

int server(FIFOS* fifosUsed, int numWorkers, char* queryLine) {

	printf("in server strlen(queryLine) %ld\n", strlen(queryLine));
	
	int sumBytes = 0, sumWords = 0, sumLines = 0;
	int wcFlag = 0;
	
	int minCountFlag=0, min = INT_MAX;
	char* minFilename = malloc(1);
	
	int maxCountFlag=0, max = 0;
	char* maxFilename = malloc(1);
	
	
	for(int i=0; i<numWorkers; i++){
		if ( write(fifosUsed[i].writefd, queryLine, strlen(queryLine)) != strlen(queryLine)) { 
		    printf("server: error in write\n");
		}
	//	printf("ended server\n");
		
		
		char buffer[BUFFSIZE];
		int length;
		//buffer[0] = '\0';
		//printf("server: before read from fileDescr\n");
		 if( (length = read(fifosUsed[i].readfd, buffer, BUFFSIZE) ) > 0) {
		 	buffer[length] = '\0';
		 	
		 	char* instruction = strtok(buffer,"|");
			char* remainingLine = strtok(NULL,"\n");	
		 	
		 	printf("BUFFER IS '%s' %d\n", buffer, length);
		 	if(strcmp(instruction,"search")==0){
			
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
			else{
				return 1;
			}
		
		}
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
  
  
   return 1;
}


int client(int readfd, int writefd, ContainsTrie* containsTrie) {

  	char line[MAXBUFF];
   	int length;
	printf("in client\n");
	line[0] = '\0';
    while( (length = read(readfd, line, MAXBUFF) ) > 0) {
 	//	printf("client: BUFFER length  %d\n", length);
		line[length] = '\0';

		
		char* instruction = strtok(line," \t\n");
		char* remainingLine = strtok(NULL,"\n");	
		
		if(strcmp(instruction,"/search")==0 || strcmp(instruction,"\\search")==0){
			SearchStruct* info = search(remainingLine, containsTrie);
			if(info!=NULL){
				printSearchStruct(info);
				
				
				
				destroySearchStruct(info);
			}
			
		}
		else if(strcmp(instruction,"/maxcount")==0 || strcmp(instruction,"\\maxcount")==0){
			//printf("instruction is maxcount\n");
			FileInfoMinMax* info =  maxCount(remainingLine, containsTrie->firstNode);
			if(info!=NULL){
				printf("%s %s %d\n", info->type, info->fileName, info->minOrMax);
				
				char* sendString = malloc((strlen(info->fileName)+1 + 20)*sizeof(char));
				sprintf(sendString, "maxcount|%s,%d", info->fileName, info->minOrMax);
				printf("sendString=%s\n",sendString);
				
				if ( write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
				    exit(1);
				}
				

				free(info->fileName);
				free(info);
				
			}
			else{
				char sendString[30];
				sprintf(sendString, "maxcount|%s,%d", "a", 0);
				printf("sendString=%s\n",sendString);
				
				if ( write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
				    exit(1);
				}
			}
		}
		else if(strcmp(instruction,"/mincount")==0 || strcmp(instruction,"\\mincount")==0){
			FileInfoMinMax* info =  minCount(remainingLine, containsTrie->firstNode);
			if(info!=NULL){
				printf("%s %s %d\n", info->type, info->fileName, info->minOrMax);
				
				char* sendString = malloc((strlen(info->fileName)+1 + 20)*sizeof(char));
				sprintf(sendString, "mincount|%s,%d", info->fileName, info->minOrMax);
				printf("sendString=%s\n",sendString);
				
				if ( write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
				    exit(1);
				}
				

				free(info->fileName);
				free(info);
				
			}
			else{
				char sendString[30];
				sprintf(sendString, "mincount|%s,%d", "noFile", INT_MAX);
				printf("sendString=%s\n",sendString);
				
				if (write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
				    exit(1);
				}
			}
		}
		else if(strcmp(instruction,"/wc")==0 || strcmp(instruction,"\\wc")==0){
			//printf("instruction is wc\n");
			BytesWordsLinesNode* info = wc(containsTrie);
			char sendString[50];
			if(info!=NULL){
				printf("Total Number of bytes is: %d. Total Number of words is: %d. Total Number of lines is: %d.\n",info->bytes, info->words, info->lines);
				
				
				sprintf(sendString, "wc|%d,%d,%d", info->bytes, info->words, info->lines);
				printf("sendString=%s\n",sendString);
				
				
				
				free(info);
				
			}
			else{
				sprintf(sendString, "wc|%d,%d,%d", 0, 0, 0);
			}
			if ( write(writefd, sendString, strlen(sendString)) != strlen(sendString)) { 
			    exit(1);
			}
		}
		else if(strcmp(instruction,"/exit")==0 || strcmp(instruction,"\\exit")==0){
			printf("return 0\n");
        	return 0;
		}
		else{			//wrong input
			return 1;
		}
		
		//if ( write(STDOUT_FILENO, "Thanks", 6) != 6) { 
        //    exit(1);
       // }
       
    }
   
   return 1;

}


