#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "instructions.h"

void search(char* text, ContainsTrie* containsTrie){
	arrayWords* array = stringToArray(text, 1);
	Trie* trie = containsTrie->firstNode;
	
	arrayWords* arrayOfFilenames = malloc(sizeof(arrayWords));
	createArrayWords(arrayOfFilenames);
	
	for(int i=0; i<array->position; i++){		//for each query word
	//printf("Word '%s' .\n", array->words[i]);
		postingList* pL = searchWordInTrie(trie, array->words[i]);
		if(pL==NULL){			//word does not exist
			printf("Word '%s' does not exist.\n", array->words[i]);
			continue;
		}
	
		
		postingListNode* tempNode = pL->firstNode;
		while(tempNode!=NULL){							//for each document
		
		
			int* linesForWordInDoc = malloc(0);
			int sizeOfLinesForWordInDoc = 0;

			insertArrayWords(arrayOfFilenames, tempNode->filePath, 1);		//do not enter if it already exists
			//get path, no of line
			//write on pipe
			printf("FilePath is %s\n", tempNode->filePath);
			//get lines
			ListNode* tempListNode = tempNode->info->firstNode;
			while(tempListNode!=NULL){
				if(lineAlreadyExists(linesForWordInDoc, sizeOfLinesForWordInDoc, tempListNode->lineOfText)){										//line has already been selected
					tempListNode = tempListNode->next;
					continue;
				}
				linesForWordInDoc[sizeOfLinesForWordInDoc] = tempListNode->lineOfText;
				sizeOfLinesForWordInDoc++;
				linesForWordInDoc = realloc(linesForWordInDoc, sizeOfLinesForWordInDoc*sizeof(int));
				
				//write on pipe
				printf("line is %d\n",  tempListNode->lineOfText);
				
				//get contents of line
				
				
				tempListNode = tempListNode->next;
			}
		
		
			tempNode = tempNode->next;
			free(linesForWordInDoc);
			linesForWordInDoc = NULL;
		}
		
		
	}
	
}



FileInfoMinMax* maxCount(char* text, Trie* trie){
	
	arrayWords* array = stringToArray(text, 0);
	if(array->position!=1){
		printf("Error! Only 1 word should be given.\n");
		deleteArrayWords(array);
		return NULL;
	}
	
	char* wordToSearch = array->words[0];
	
	

	postingList* pL = searchWordInTrie(trie, wordToSearch);
	if(pL==NULL){			//word does not exist
		printf("Word '%s' does not exist.\n", wordToSearch);
		deleteArrayWords(array);
		return NULL;
	}
		
		
	FileInfoMinMax* info = malloc(sizeof(FileInfoMinMax));
	info->type="max";
	info->minOrMax=0;
	info->fileName = NULL;
		
	postingListNode* tempNode = pL->firstNode;
	while(tempNode!=NULL){
		if(tempNode->occurrences > info->minOrMax){
			info->minOrMax = tempNode->occurrences;
			info->fileName = tempNode->filePath;
		}
		else if(tempNode->occurrences == info->minOrMax){ 		//choose alphabetically smaller
			if(strcmp(tempNode->filePath, info->fileName)<0){
				info->fileName = tempNode->filePath;
			}
		}
		
		tempNode = tempNode->next;
	}
	
	
	printf("%s %s %d\n", info->type, info->fileName, info->minOrMax);
	deleteArrayWords(array);
	return info;
	
	//actually must write in pipe 1 integer and 1 string: info->fileName, info->minOrMax
}

FileInfoMinMax* minCount(char* text, Trie* trie){

	arrayWords* array = stringToArray(text, 0);
	if(array->position!=1){
		printf("Error! Only 1 word should be given.\n");
		deleteArrayWords(array);
		return NULL;
	}
	
	char* wordToSearch = array->words[0];
	
	

	postingList* pL = searchWordInTrie(trie, wordToSearch);
	if(pL==NULL){			//word does not exist
		printf("Word '%s' does not exist.\n", wordToSearch);
		deleteArrayWords(array);
		return NULL;
	}
		
		
	FileInfoMinMax* info = malloc(sizeof(FileInfoMinMax));
	info->type="min";
	info->minOrMax=INT_MAX;		//defined value
	info->fileName = NULL;
	
		
	postingListNode* tempNode = pL->firstNode;
	while(tempNode!=NULL){
		if(tempNode->occurrences < info->minOrMax){
			info->minOrMax = tempNode->occurrences;
			info->fileName = tempNode->filePath;
		}
		else if(tempNode->occurrences == info->minOrMax){ 		//choose alphabetically smaller
			if(strcmp(tempNode->filePath, info->fileName)<0){
				info->fileName = tempNode->filePath;
			}
		}
		
		tempNode = tempNode->next;
	}
	
	printf("%s %s %d\n", info->type, info->fileName, info->minOrMax);
	deleteArrayWords(array);
	return info;
	//actually must write in pipe 1 integer and 1 string: info->fileName, info->minOrMax
}

BytesWordsLinesNode* wc(ContainsTrie* containsTrie){
	//get statistics from all Files
	BytesWordsLinesNode* summedUpInfo = malloc(sizeof(BytesWordsLinesNode));
	summedUpInfo->fileName = NULL;
	summedUpInfo->bytes = 0;
	summedUpInfo->words = 0;
	summedUpInfo->lines = 0;
	
	BytesWordsLinesStruct* info = containsTrie->info;	
	for(int i=0; i<info->position; i++){
		summedUpInfo->bytes+= info->array[i].bytes;
		summedUpInfo->words+= info->array[i].words;
		summedUpInfo->lines+= info->array[i].lines;

	}
	printf("Total Number of bytes is: %d. Total Number of bytes is: %d. Total Number of bytes is: %d.\n",summedUpInfo->bytes, summedUpInfo->words, summedUpInfo->lines);
	return summedUpInfo;
	
	//actually must write in pipe 3 integers: summedUpInfo->bytes, summedUpInfo->words, summedUpInfo->lines
}


bool lineAlreadyExists(int* array, int size, int line){
	for(int i=0; i<size; i++){
		if(array[i]==line){
			return true;
		}
	}
	return false;
}




