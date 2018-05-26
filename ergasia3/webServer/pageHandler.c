#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

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
			respStr->firstLine = "HTTP/1.1 403 Forbidden";
			respStr->contentLength = 124;
			respStr->content = "<html>Trying to access this file but don’t think I can make it.</html>";
		}
		else{ // file does not exist
			respStr->firstLine = "HTTP/1.1 404 Not Found";
			respStr->contentLength = 124;
			respStr->content = "<html>Sorry dude, couldn’t find this file.</html>";
		}
		
	}
	else{	//read content of file
		respStr->firstLine = "HTTP/1.1 200 OK";
		respStr->contentLength = 124;
		respStr->content = "<html>Must get Content Of Page.</html>";


		close (fd);
	}

	return respStr;
}