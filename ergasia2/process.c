#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include "process.h"



int server(int readfd, int writefd, char* line) {

    if ( write(writefd, line, strlen(line)) != strlen(line)) { 
        printf("server: error in write\n");
    }

   return 1;
}


int client(int readfd, int writefd) {

  char buff[MAXBUFF];
   int n;

	buff[0] = '\0';
    while( (n = read(readfd, buff, MAXBUFF) ) > 0) {
 
		//printf("in client\n");
		printf("buff before is '%s'\n", buff);
		buff[n] = '\0';
		printf("buff is '%s'\n", buff);
		
		
		char* line = malloc(n*sizeof(char));
		strcpy(line, buff);
		char* instruction = strtok(line," \t\n");
		char* remainingLine = strtok(NULL,"\n");				//for some reason is null
		printf("instruction '%s' remainingLine '%s'\n",instruction, remainingLine);
		
		
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
			printf("return 0\n");
        	return 0;
		}
		else{			//wrong input
			return 1;
		}
		
		
		
		//printf("buff is '%s'\n", buff);
        if (write(STDOUT_FILENO, buff, n) != n) { 
           printf("client: error in write\n");
        }
        printf("\n");
    }
   
   return 1;

}


