#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bytesWordsLinesInfo.h"

BytesWordsLinesStruct* createBytesWordsLinesStruct(){
	BytesWordsLinesStruct* info = malloc(sizeof(BytesWordsLinesStruct));
	
	info->length = 5;
	info->position = 0;
	info->array = malloc(info->length *sizeof(BytesWordsLinesNode));
	
	for(int i=0; i<info->length; i++){
		info->array[i].fileName = NULL;
		info->array[i].bytes = 0;
		info->array[i].words = 0;
		info->array[i].lines = 0;
	}
	
	return info;
}

void doubleBytesWordsLinesStruct(BytesWordsLinesStruct* info){
	int oldLength = info->length;
	info->length*=2;
	info->array = realloc(info->array,sizeof(BytesWordsLinesNode)*info->length); 
	
	for(int i=oldLength; i<info->length; i++){
		info->array[i].fileName = NULL;
		info->array[i].bytes = 0;
		info->array[i].words = 0;
		info->array[i].lines = 0;
	}

}

void insertBytesWordsLinesStruct(BytesWordsLinesStruct* info, char* fileName, int bytes, int words, int lines){
	if(info->position==info->length){
		doubleBytesWordsLinesStruct(info);
	}
	info->array[info->position].fileName = fileName;
	info->array[info->position].bytes = bytes;
	info->array[info->position].words = words;
	info->array[info->position].lines = lines;
	info->position++; 
}


void printBytesWordsLinesStruct(BytesWordsLinesStruct* info){
	printf("Printing BytesWordsLinesStruct\n");
	for(int i=0; i<info->position; i++){
		printf("%s bytes: %d words: %d lines: %d\n", info->array[i].fileName , info->array[i].bytes , info->array[i].words , info->array[i].lines);
	}
}

void deleteBytesWordsLinesStruct(BytesWordsLinesStruct* info){
	if(info!=NULL){
		free(info->array);
		free(info);
		info=NULL;	
	}
}

