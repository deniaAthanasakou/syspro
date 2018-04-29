#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include "process.h"
#include "instructions.h"



int server(int readfd, int writefd, char* queryLine) {
    if ( write(writefd, queryLine, strlen(queryLine)) != strlen(queryLine)) { 
        printf("server: error in write\n");
    }

   return 1;
}


int client(int readfd, int writefd, ContainsTrie* containsTrie) {

  char line[MAXBUFF];
   int n;

	line[0] = '\0';
    while( (n = read(readfd, line, MAXBUFF) ) > 0) {
 
		line[n] = '\0';

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
				
				
				free(info->fileName);
				free(info);
			}
		}
		else if(strcmp(instruction,"/mincount")==0 || strcmp(instruction,"\\mincount")==0){
			FileInfoMinMax* info =  minCount(remainingLine, containsTrie->firstNode);
			if(info!=NULL){
				printf("%s %s %d\n", info->type, info->fileName, info->minOrMax);
				

				free(info->fileName);
				free(info);
				
			}
		}
		else if(strcmp(instruction,"/wc")==0 || strcmp(instruction,"\\wc")==0){
			//printf("instruction is wc\n");
			BytesWordsLinesNode* info = wc(containsTrie);
			if(info!=NULL){
				printf("Total Number of bytes is: %d. Total Number of words is: %d. Total Number of lines is: %d.\n",info->bytes, info->words, info->lines);
				
				free(info);
				
			}
		}
		else if(strcmp(instruction,"/exit")==0 || strcmp(instruction,"\\exit")==0){
			printf("return 0\n");
        	return 0;
		}
		else{			//wrong input
			return 1;
		}
		
        if (write(STDOUT_FILENO, line, n) != n) { 		//tha allaksei
           printf("client: error in write\n");
        }
        printf("\n");
        
    }
   
   return 1;

}


