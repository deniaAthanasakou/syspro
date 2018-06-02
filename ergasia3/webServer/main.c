#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "socketHandler.h"
#include "errorHandler.h"


int main (int argc,char* argv[]){

	if(argc!=9){
		printf("Error! Wrong Number of Arguments.\n");
		exit(1);
	}

	char* name_of_root_dir=NULL;
	int num_of_threads=-1;		
	int serving_port=-1;		
	int command_port=-1;	

	for(int i=0; i<argc; i++){
		if(!strcmp(argv[i],"-d"))
			name_of_root_dir=argv[i+1];							//argument before name of root directory should be -d
		else if(!strcmp(argv[i],"-t"))
			num_of_threads=atoi(argv[i+1]);						//argument before number of threads should be -t
		else if(!strcmp(argv[i],"-p"))
			serving_port=atoi(argv[i+1]);						//argument before serving port should be -p
		else if(!strcmp(argv[i],"-c"))
			command_port=atoi(argv[i+1]);						//argument before command port should be -c
	}

	DIR *root_dir = opendir(name_of_root_dir);
	if (root_dir == NULL) {					//Not a directory or doesn't exist
		perror_exit("Error in root directory");
	}
	int n = 0;
	struct dirent *d;
	while ((d = readdir(root_dir)) != NULL) {
	if(++n > 2)
	  break;
	}
	closedir(root_dir);
	if (n <= 2) {//Directory Empty
		printf("Error! Root directory is empty.\n");
		exit(1);
	}

	if(num_of_threads<=0){
		printf("Error! Invalid value for number of threads.\n");
		exit(1);
	}
	if(serving_port<0){
		printf("Error! Invalid value for serving port.\n");
		exit(1);
	}
	if(command_port<0){
		printf("Error! Invalid value for command port.\n");
		exit(1);
	}
	if(serving_port==command_port){
		printf("Error! Different ports were required.\n");
		exit(1);
	}

	printf("Printing input: root dir '%s', num_of_threads '%d', serving_port '%d', command_port '%d'\n", name_of_root_dir, num_of_threads, serving_port, command_port);
	
	createSocket(serving_port, command_port, name_of_root_dir, num_of_threads);

	return 0;

}
