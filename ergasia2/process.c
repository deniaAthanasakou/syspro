#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include "process.h"
#include "instructions.h"

#define BUFFSIZE 1024

int server(int readfd, int writefd, char* queryLine) {

	printf("in server\n");
    if ( write(writefd, queryLine, strlen(queryLine)) != strlen(queryLine)) { 
        printf("server: error in write\n");
    }
    printf("ended server\n");
    
  /*  char buffer[BUFFSIZE];
    int length;
	buffer[0] = '\0';
	printf("server: before read from fileDescr\n");
	 while( (length = read(readfd, buffer, BUFFSIZE) ) > 0) {
	 	buffer[length] = '\0';
	 	printf("BUFFER IS '%s' %d\n", buffer, length);
	 	if(strcmp(buffer,"search")==0){
			
		}
		else if(strcmp(buffer,"maxcount")==0){
			
		}
		else if(strcmp(buffer,"mincount")==0){
			
		}
		else if(strcmp(buffer,"/wc")==0){
			printf("IN IF\n");
			length=0;
			buffer[0] = '\0';
			if(length = read(readfd, buffer, BUFFSIZE)>0){ //read bytes
				
				buffer[length] = '\0';
				
				printf("bytes are '%d'\n", buffer[0]);
				
				if(length = read(readfd, buffer, BUFFSIZE)>0){ //read bytes
					buffer[length] = '\0';
					printf("words are '%d'\n", buffer[0]);
					
					if(length = read(readfd, buffer, BUFFSIZE)>0){ //read bytes
						buffer[length] = '\0';
						printf("lines are '%d'\n", buffer[0]);
					}
					
				}
			}
			
			

		}
       // if ( write(STDOUT_FILENO, buffer[0], length) != length) { 
       //      printf("server: error in write in STDOUT\n");
       // }
       printf(" break\n");
     	break;
    }*/
    //printf("server: after read from fileDescr\n");
    
   return 1;
}


int client(int readfd, int writefd, ContainsTrie* containsTrie) {

  	char line[MAXBUFF];
   	int n;
	printf("in client\n");
	line[0] = '\0';
    while( (n = read(readfd, line, MAXBUFF) ) > 0) {
 		printf("client: BUFFER length  %d\n", n);
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
				
				/*printf("client: before write wc length %ld\n", strlen(instruction));
				if ( write(writefd, instruction , strlen(instruction)) != strlen(instruction)) { 		//send word count for confirmation
				     printf("client: error in write\n");
				}
				else{
				//printf("client: before write  bytes\n");		
					if ( write(writefd, &info->bytes, sizeof(info->bytes)) != sizeof(info->bytes)) { 	//write bytes
						 printf("client: error in write\n");
					}
				
					else{
			   		 //	printf("client: before write words \n");			
			   		 	if ( write(writefd, &info->words, sizeof(info->words)) != sizeof(info->words)) { 	//write noOfWords
							 printf("client: error in write\n");
						}
						//printf("client: after write words \n");			
						else{
							if ( write(writefd, &info->lines, sizeof(info->lines)) != sizeof(info->lines)) { 	//write noOfLines
								 printf("client: error in write\n");
							}
							printf("client: after write \n");	
						}
					}		
				}
				*/
				
				free(info);
				
			}
		}
		else if(strcmp(instruction,"/exit")==0 || strcmp(instruction,"\\exit")==0){
			printf("return 0\n");
        	return 0;
		}
		//else{			//wrong input
		//	return 1;
		//}
		
       
    }
   
   return 1;

}


