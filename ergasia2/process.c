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


    while( (n = read(readfd, buff, MAXBUFF) ) > 0) {
		//printf("in client\n");
		buff[4] = 'k';
        if ( write(STDOUT_FILENO, buff, n) != n) { 
           printf("client: error in write\n");
        }
        printf("\n");
    }
  
   
   return 1;

}


