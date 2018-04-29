#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "instructions.h"

SearchStruct* search(char* text, ContainsTrie* containsTrie){
	arrayWords* array = stringToArray(text, 1);
	Trie* trie = containsTrie->firstNode;
	
	
	if(array->position==0){
		printf("No query words were given.\n");
		deleteArrayWords(array);
		return NULL;
	}

	SearchStruct* searchStruct = createSearchStruct();
	
	
	arrayWords* arrayOfFileNames = malloc(sizeof(arrayWords));
	createArrayWords(arrayOfFileNames);

	for(int i=0; i<array->position; i++){		//for each query word
	//printf("Word '%s' .\n", array->words[i]);
		postingList* pL = searchWordInTrie(trie, array->words[i]);
		if(pL==NULL){			//word does not exist
			printf("Word '%s' does not exist.\n", array->words[i]);
			continue;
		}
	
		
		postingListNode* tempNode = pL->firstNode;
		while(tempNode!=NULL){							//for each document
			if(checkifWordExists(arrayOfFileNames, tempNode->filePath)){
				tempNode = tempNode->next;
				continue;
			}
			insertArrayWords(arrayOfFileNames, tempNode->filePath, 1);
			printf("\n\n");
		
			int* linesForWordInDoc = malloc(0);
			int sizeOfLinesForWordInDoc = 0;
			
			
			//get path, no of line
			//write on pipe
		//	printf("FilePath is '%s'\n", tempNode->filePath);
			//get lines
			ListNode* tempListNode = tempNode->info->firstNode;
			while(tempListNode!=NULL){
				if(lineAlreadyExists(linesForWordInDoc, sizeOfLinesForWordInDoc, tempListNode->lineOfText)){					//line has already been printed
					tempListNode = tempListNode->next;
					continue;
				}
				sizeOfLinesForWordInDoc++;
				linesForWordInDoc = realloc(linesForWordInDoc, sizeOfLinesForWordInDoc*sizeof(int));
				linesForWordInDoc[sizeOfLinesForWordInDoc-1] = tempListNode->lineOfText;
				
				
				//write on pipe
			//	printf("Number of line is '%d'\n",  tempListNode->lineOfText);
				
				//get contents of line
				char* contentsOfLine = getLineOfFile(containsTrie->mapOfFiles, tempNode->filePath, tempListNode->lineOfText);
				if(contentsOfLine!=NULL){
					//write on pipe
				//	printf("line is '%s'\n",  contentsOfLine);
					insertIntoSearchStruct(searchStruct,tempNode->filePath, tempListNode->lineOfText, contentsOfLine );
					
				}
				
				
				tempListNode = tempListNode->next;
			}
		
		
			tempNode = tempNode->next;
			free(linesForWordInDoc);
			linesForWordInDoc = NULL;
			
			
		}
		
		
	}
	free(arrayOfFileNames->words);
	free(arrayOfFileNames);
	deleteArrayWords(array);
	return searchStruct;
	
}



FileInfoMinMax* maxCount(char* text, Trie* trie){
	
	arrayWords* array = stringToArray(text, 0);
	if(array->position!=1){
		printf("Error! One word should be given.\n");
		deleteArrayWords(array);
		return NULL;
	}
	
	char* wordToSearch = array->words[0];
	
	

	postingList* pL = searchWordInTrie(trie, wordToSearch);
	if(pL==NULL){			//word does not exist
	//	printf("Word '%s' does not exist.\n", wordToSearch);
		deleteArrayWords(array);
		return NULL;
	}
		
		
	FileInfoMinMax* info = malloc(sizeof(FileInfoMinMax));
	info->type="max";
	info->minOrMax=0;
	info->fileName = NULL;
	
	char* tempFile = "\0";
		
	postingListNode* tempNode = pL->firstNode;
	while(tempNode!=NULL){
		if(tempNode->occurrences > info->minOrMax){
			info->minOrMax = tempNode->occurrences;
			tempFile = tempNode->filePath;
		}
		else if(tempNode->occurrences == info->minOrMax){ 		//choose alphabetically smaller
			if(strcmp(tempFile,"\0")==0){
				tempFile = tempNode->filePath;					//initialization
			}
			else if(strcmp(tempNode->filePath, tempFile)<0){
				tempFile = tempNode->filePath;
			}
		}
		
		tempNode = tempNode->next;
	}
	
	if(tempFile!=NULL){
		info->fileName = malloc((strlen(tempFile)+1)*sizeof(char));
		strcpy(info->fileName, tempFile);
	}
	//printf("%s %s %d\n", info->type, info->fileName, info->minOrMax);
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
	//	printf("Word '%s' does not exist.\n", wordToSearch);
		deleteArrayWords(array);
		return NULL;
	}
		
		
	FileInfoMinMax* info = malloc(sizeof(FileInfoMinMax));
	info->type="min";
	info->minOrMax=INT_MAX;		//defined value
	info->fileName = NULL;
	
	char* tempFile = "\0";
		
	postingListNode* tempNode = pL->firstNode;
	while(tempNode!=NULL){
		if(tempNode->occurrences < info->minOrMax){
			info->minOrMax = tempNode->occurrences;
			tempFile = tempNode->filePath;
		}
		else if(tempNode->occurrences == info->minOrMax){ 		//choose alphabetically smaller
			if(strcmp(tempFile,"\0")==0){
				tempFile = tempNode->filePath;					//initialization
			}
			else if(strcmp(tempNode->filePath, tempFile)<0){
				tempFile = tempNode->filePath;
			}
		}
		
		tempNode = tempNode->next;
	}
	
	
	
	//printf("%s %s %d\n", info->type, info->fileName, tempFile);
	
	
	if(tempFile!=NULL){
		info->fileName = malloc((strlen(tempFile)+1)*sizeof(char));
		strcpy(info->fileName, tempFile);
	}
	
	
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
	//printf("Total Number of bytes is: %d. Total Number of words is: %d. Total Number of lines is: %d.\n",summedUpInfo->bytes, summedUpInfo->words, summedUpInfo->lines);
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




