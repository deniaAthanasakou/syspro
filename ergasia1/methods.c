#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methods.h"


int initialize(FILE* file, Map* map){
	char *line = NULL;
	size_t len = 0;
	int read;
	if (file == NULL){
		printf("Error! Null file was given\n");
		return 0;
	}
	int counter=1;//0;	
	while ((read = getline(&line, &len, file)) != -1) {
		int lineNumber = atoi(strtok(line," \t"));
		if(lineNumber!=counter){
			printf("Error in numbering file lines\n");
			
			if (line){
				free(line);
				line=NULL;
			}
			
			return 0;
		}
		
		char* remainingLine = strtok(NULL,"\n");
		printf("%d\n", lineNumber);
		printf("'%s'\n", remainingLine);
		
		//inserting lines into map
		char* text = malloc((strlen(remainingLine)+1)* sizeof(char));
		strcpy(text, remainingLine);
		insertIntoMap(map, lineNumber, text);
		counter++;		
	}
	//printf("map->Length %d, map->position %d\n", map->length, map->position);
	//printMap(map);
	reduceMapLength(map);
	//printf("map->Length %d, map->position %d\n", map->length, map->position);
	//printMap(map);

	if (line){
		free(line);
		line=NULL;
	}
	return 1;
}

arrayWords* stringToArray(char* text){
	char* pch;
	char** arrayOfWords; 
	pch = strtok (text," \t");
	int noOfWords=0;
	arrayOfWords = malloc(noOfWords * sizeof(char*));
	while (pch != NULL)
	{	
		noOfWords++;
		arrayOfWords = (char**)realloc(arrayOfWords, noOfWords * sizeof(char*));		
		arrayOfWords[noOfWords-1]=malloc((strlen(pch)+1)* sizeof(char));
		strcpy(arrayOfWords[noOfWords-1],pch);    //add pch into arrayOfWords
		pch = strtok (NULL, " \t");
	}
	
	arrayWords* arrayW = malloc(sizeof(arrayWords));
	arrayW->length = noOfWords;
	arrayW->words = arrayOfWords;
	
	return arrayW;

}

void printArrayWords(arrayWords* array_of_words){
	printf("Printing array of words\n");
	for(int i=0; i<array_of_words->length; i++){
		printf("%s\n", array_of_words->words[i]);
	}
}

void deleteArrayWords(arrayWords* array_of_words){
	if(array_of_words!=NULL){
		for(int i=0;i<array_of_words->length;i++){
			if( array_of_words->words[i]!=NULL){
				free(array_of_words->words[i]);
				array_of_words->words[i] = NULL;
			}
		}
		free(array_of_words->words);
		free(array_of_words);	
	}
}
























