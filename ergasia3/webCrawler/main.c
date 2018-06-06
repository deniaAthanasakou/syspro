#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/timeb.h>        
#include "errorHandler.h"
#include "getPages.h"

int main (int argc,char* argv[]){

	struct timeb begin;
	ftime(&begin);

	if(argc!=12){
		printf("Error! Wrong Number of Arguments.\n");
		exit(1);
	}

	char* name_of_save_dir=NULL;
	int num_of_threads=-1;		
	int port=-1;		
	int command_port=-1;	
	char* host_or_IP=NULL;
	char* starting_URL=NULL;	

	for(int i=0; i<argc; i++){
		if(!strcmp(argv[i],"-d"))
			name_of_save_dir=argv[i+1];							//argument before name of save directory should be -d
		else if(!strcmp(argv[i],"-t"))
			num_of_threads=atoi(argv[i+1]);						//argument before number of threads should be -t
		else if(!strcmp(argv[i],"-p"))
			port=atoi(argv[i+1]);								//argument before port should be -p
		else if(!strcmp(argv[i],"-c"))
			command_port=atoi(argv[i+1]);						//argument before command port should be -c
		else if(!strcmp(argv[i],"-h"))
			host_or_IP=argv[i+1];							//argument before host_or_IP should be -h
		else if (i==argc-1){
			starting_URL=argv[i];								//last argument must be starting url
		}
	}

	DIR *save_dir = opendir(name_of_save_dir);
	if (save_dir == NULL) {					//Not a directory or doesn't exist
		perror_exit("Error in save directory");
	}
	closedir(save_dir);
	char cmd[500];
	sprintf(cmd,"if [ \"$(ls -A %s)\" ]; then echo \"Warning: directory %s is full and will be emptied.\";rm -rf %s/*;fi",name_of_save_dir,name_of_save_dir , name_of_save_dir); 
	system(cmd);

	if(num_of_threads<=0){
		printf("Error! Invalid value for number of threads.\n");
		exit(1);
	}
	if(port<0){
		printf("Error! Invalid value for serving port.\n");
		exit(1);
	}
	if(command_port<0){
		printf("Error! Invalid value for command port.\n");
		exit(1);
	}
	if(host_or_IP<0){
		printf("Error! Invalid value for host or IP.\n");
		exit(1);
	}
	if(starting_URL==NULL){
		printf("Error! NULL URL was given.\n");
		exit(1);
	}
	if(port==command_port){
		printf("Error! Different ports are required.\n");
		exit(1);
	}

	connectToServer(port, command_port, host_or_IP, starting_URL, name_of_save_dir, num_of_threads, &begin);

	return 0;

}
