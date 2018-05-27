#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <errno.h>

#include "pageHandler.h"

ResponseStr* getResponseStrOfPage(char* page, char* rootDirectory){

	ResponseStr* respStr = malloc(sizeof(ResponseStr));

	char* fileName=malloc((strlen(rootDirectory) + strlen(page) +1)*sizeof(char));
	sprintf(fileName, "%s%s", rootDirectory,page );
	printf("fileName = '%s'\n", fileName);

	int fd = open(fileName, O_RDONLY, 0644);

	if (fd==-1){
		printf("errno=%d\n", errno);
		if(errno == EACCES){// we do not have read permission
			respStr->firstLine=malloc((strlen("HTTP/1.1 403 Forbidden")+1)*sizeof(char));
			strcpy(respStr->firstLine, "HTTP/1.1 403 Forbidden");
			respStr->contentLength = 124;
			respStr->content=malloc((strlen("<html>Trying to access this file but don’t think I can make it.</html>")+1)*sizeof(char));
			strcpy(respStr->content, "<html>Trying to access this file but don’t think I can make it.</html>");
			//respStr->content = "<html>Trying to access this file but don’t think I can make it.</html>";
		}
		else{ // file does not exist
			respStr->firstLine=malloc((strlen("HTTP/1.1 404 Not Found")+1)*sizeof(char));
			strcpy(respStr->firstLine, "HTTP/1.1 404 Not Found");
			respStr->contentLength = 124;
			respStr->content=malloc((strlen("<html>Sorry dude, couldn’t find this file.</html>")+1)*sizeof(char));
			strcpy(respStr->content, "<html>Sorry dude, couldn’t find this file.</html>");
			//respStr->content = "<html>Sorry dude, couldn’t find this file.</html>";
		}
		
	}
	else{	//read content of file


		struct stat buf;
		fstat(fd, &buf);
		int numBytes = buf.st_size;
		char cont[numBytes];
		printf("numBytes=%d\n", numBytes);
		int contLength=0;
		if((contLength=read(fd, cont, numBytes))<0){
			respStr->content=malloc((strlen("<html>Error with file reading.</html>")+1)*sizeof(char));
			strcpy(respStr->content, "<html>Error with file reading.</html>");
			respStr->contentLength = 124; 	//default?
			//respStr->content = "<html>Error with file reading.</html>";
		}
		else{
			cont[contLength]='\0';
			respStr->contentLength = strlen(cont)-49; 	//length of header + length of footer = 49
			//respStr->content = cont;
			respStr->content=malloc((strlen(cont)+1)*sizeof(char));
			strcpy(respStr->content, cont);
		}
		//printf("cont=%s\n", cont);

		respStr->firstLine=malloc((strlen("HTTP/1.1 200 OK")+1)*sizeof(char));
		strcpy(respStr->firstLine, "HTTP/1.1 200 OK");
		
		




		close (fd);
	}
	free(fileName);
	return respStr;
}
