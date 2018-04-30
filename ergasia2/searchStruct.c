#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "searchStruct.h"


SearchStruct* createSearchStruct(){
	SearchStruct* searchStruct = malloc(sizeof(SearchStruct));
	searchStruct->length = 5;
	searchStruct->position = 0;
	searchStruct->array = malloc(searchStruct->length*sizeof(SearchNode));
	for(int i=0; i<searchStruct->length; i++){
		initializeSearchNode(&(searchStruct->array[i]));
	}
	return searchStruct;
}

int initializeSearchNode(SearchNode* node){
	node->lineNo = -1;
	node->fileName = NULL;
	node->content = NULL;
}

void insertIntoSearchStruct(SearchStruct* searchStruct, char* fileName, int line, char* content){
	if(searchStruct->position==searchStruct->length){
		doubleSearchStruct(searchStruct);
	}
	searchStruct->array[searchStruct->position].lineNo = line;
	searchStruct->array[searchStruct->position].fileName = malloc((strlen(fileName)+1)*sizeof(char));
	strcpy(searchStruct->array[searchStruct->position].fileName, fileName);
	searchStruct->array[searchStruct->position].content = malloc((strlen(content)+1)*sizeof(char));
	strcpy(searchStruct->array[searchStruct->position].content, content);
	
	if(searchStruct->array[searchStruct->position].content[strlen(content)-1] == '\n');
		searchStruct->array[searchStruct->position].content[strlen(content)-1] = '\0';
	
	searchStruct->position++;
}	

void printSearchStruct(SearchStruct* searchStruct){
	printf("Printing search nodes: pos = %d\n", searchStruct->position);
	for(int i=0; i<searchStruct->position; i++){
		printf("filename: '%s', line no '%d', content '%s'\n",searchStruct->array[i].fileName, searchStruct->array[i].lineNo, searchStruct->array[i].content);
	}
}

void doubleSearchStruct(SearchStruct* searchStruct){
	int oldLength = searchStruct->length;
	searchStruct->length*=2;
	searchStruct->array = (SearchNode*)realloc(searchStruct->array, searchStruct->length*sizeof(SearchNode));
	for(int i=oldLength; i<searchStruct->length; i++){
		initializeSearchNode(&(searchStruct->array[i]));
	}
}

void destroySearchStruct(SearchStruct* searchStruct){
	if(searchStruct!=NULL){
		for(int i=0; i<searchStruct->position; i++){ 	//destroy contents of node
			free(searchStruct->array[i].fileName);
			free(searchStruct->array[i].content);
		}
		free(searchStruct->array);
		free(searchStruct);
	}
}

char* getStringForPrint(SearchStruct* searchStruct, int deadLine){
	
	char* sendString = malloc((2*sizeof(int) +10)*sizeof(char));
	sprintf(sendString, "search|%d|%d|", deadLine, searchStruct->position);			//number of elements
	int lengthOfString = 0;
	for(int i=0; i<searchStruct->position; i++){
		lengthOfString = strlen(sendString);
		char* beggining = malloc((strlen("Server: One or more query words were discovered in file '%s'")+1+strlen(searchStruct->array[i].fileName))*sizeof(char));
		sprintf(beggining,"Server: One or more query words were discovered in file '%s'", searchStruct->array[i].fileName);
		
		char* middle = malloc((strlen(" in line '%d'")+1+sizeof(searchStruct->array[i].lineNo))*sizeof(char));
		sprintf(middle," in line '%d'", searchStruct->array[i].lineNo);
		
		char* ending = malloc((strlen(" with contents '%s'.\n")+1+strlen(searchStruct->array[i].content))*sizeof(char));
		sprintf(ending," with contents '%s'.\n", searchStruct->array[i].content);

		sendString = realloc(sendString, (lengthOfString + strlen(beggining) + strlen(middle) + strlen(ending)+1)*sizeof(char));
		
		strcat(sendString,beggining );
		strcat(sendString,middle );
		strcat(sendString,ending );
		
		free(beggining);
		free(middle);
		free(ending);
	}
	
	return sendString;
				
}












