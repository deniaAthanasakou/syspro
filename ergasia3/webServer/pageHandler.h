#ifndef _PAGE_HANDLER_H_
#define _PAGE_HANDLER_H_

typedef struct ResponseStr{
	char* firstLine;
	int contentLength;
	char* content;
}ResponseStr;

ResponseStr* getResponseStrOfPage(char* page, char* rootDirectory);


#endif