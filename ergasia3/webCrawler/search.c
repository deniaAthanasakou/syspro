#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* internet sockets */
#include <unistd.h> /* read, write, close */ 
#include <dirent.h>
#include <sys/wait.h>


#include "errorHandler.h"
#include "search.h"

void searchHandler(int fd, char* command, char* save_dir){
	char *token;
   
   /* get the first token */
   token = strtok(command, " \t");
   
   /* walk through other tokens */
   char* searchWords = strtok(NULL, "");
   if(searchWords==NULL){
   		if (write(fd, "Wrong format of instruction search\n", strlen("Wrong format of instruction search\n")) < 0){
			perror_exit("write");
		}
		return;
   }
   char* docFile = createDocFile(save_dir);
   if(docFile==NULL){
   		if (write(fd, "Error in docfile\n", strlen("Error in docfile\n")) < 0){		
			perror_exit("write");
		}
		return;
   }

   createJobExecutor(docFile, fd, searchWords);

   free(docFile);
}


char* createDocFile(char* save_dir){

	char* fileName = malloc((strlen("docFile")+1)*sizeof(char));
	strcpy(fileName, "docFile");

	FILE* docFile = fopen(fileName, "w");
	if(!docFile){
		printf("Error! Could not create doc File\n");
		return NULL;
	}

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (save_dir)) != NULL) {
	  /* print all the files and directories within directory */
		  while ((ent = readdir (dir)) != NULL) {
		  	if(ent->d_name[0]!='.'){
			  	char* folderName=malloc((strlen(save_dir)+ strlen(ent->d_name)+2)* sizeof(char));

			  	if(save_dir[strlen(save_dir)-1]=='/'){
			  		sprintf(folderName, "%s%s", save_dir, ent->d_name);
			  	}
			  	else{
			  		sprintf(folderName, "%s/%s", save_dir, ent->d_name);
			  	}
			    fprintf (docFile, "%s\n", folderName);

			    free(folderName);
			}
		  }
		  closedir (dir);
	} 
	else {
		  /* could not open directory */
		  perror_exit ("opendir");
		  return NULL;
	}

	fclose(docFile);

	return fileName;
}


void createJobExecutor(char* docFile, int fd, char* searchWords){

	char command[200];
	sprintf(command, "/search %s -d deadline", searchWords);

	//must create pipes and replace then with stdin and stdout so that instruction will be taken from command and result will be printed into command port
	int childpid = fork();
	if (childpid == -1){		//error
		printf("Failed to fork");
		exit(1);
	}
	else if (childpid == 0){			//child

		char* arguments[6] = {"../JobExecutor/jobExecutor", "-d", docFile, "-w", "10", (char*)NULL};
		execv("../JobExecutor/jobExecutor", arguments);

	}
	else{
		while (wait(NULL) > 0)		//wait for child
	  	{
	  	}
	}

}