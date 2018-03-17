#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayWords.h"


arrayWords* stringToArray(char* text){
	char* pch;
	char** arrayOfWords; 
	pch = strtok (text," \t");
	int noOfWords=0;
	
	arrayWords* arrayW = malloc(sizeof(arrayWords));
	createArrayWords(arrayW);
	
	while (pch != NULL)
	{	
		char* wordForInsert = malloc((strlen(pch)+1)* sizeof(char));
		strcpy(wordForInsert,pch);   
		insertArrayWords(arrayW, wordForInsert); //add pch into arrayOfWords
		
		pch = strtok (NULL, " \t");
	}
	
	return arrayW;

}

void createArrayWords(arrayWords* array){
	array->length=10;
	array->position=0;
	array->words = malloc(sizeof(char*)*array->length);
	
}

void doubleArrayWords(arrayWords* array){
	array->length*=2;
	array->words = realloc(array->words,sizeof(char*)*array->length); 

}
void insertArrayWords(arrayWords* array, char* word){
	if(array->position==array->length){
		doubleArrayWords(array);
	}
	array->words[array->position] = word;
	array->position++; 
}



void printArrayWords(arrayWords* array_of_words){
	printf("Printing array of words\n");
	for(int i=0; i<array_of_words->position; i++){
		printf("%s\n", array_of_words->words[i]);
	}
}


void deleteArrayWords(arrayWords* array_of_words){
	if(array_of_words!=NULL){
		for(int i=0;i<array_of_words->position;i++){
			if( array_of_words->words[i]!=NULL){
				free(array_of_words->words[i]);
				array_of_words->words[i] = NULL;
			}
		}
		free(array_of_words->words);
		free(array_of_words);
		array_of_words=NULL;	
	}
}
























