#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "instructions.h"

//#define INT_MAX 2147483647	



FileInfoMinMax* maxCount(arrayWords* array, Trie* trie){
	if(array->position!=1){
		printf("Error! Only 1 word should be given.\n");
		return NULL;
	}
	
	char* wordToSearch = array->words[0];
	
	

	postingList* pL = searchWordInTrie(trie, wordToSearch);
	if(pL==NULL){			//word does not exist
		printf("Word '%s' does not exist.\n", wordToSearch);
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
	return info;
}

FileInfoMinMax* minCount(arrayWords* array, Trie* trie){
	if(array->position!=1){
		printf("Error! Only 1 word should be given.\n");
		return NULL;
	}
	
	char* wordToSearch = array->words[0];
	
	

	postingList* pL = searchWordInTrie(trie, wordToSearch);
	if(pL==NULL){			//word does not exist
		printf("Word '%s' does not exist.\n", wordToSearch);
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
	return info;
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
		summedUpInfo->bytes+=  info->array[i].bytes;
		summedUpInfo->words+=  info->array[i].words;
		summedUpInfo->lines+=  info->array[i].lines;
	}
	
	return summedUpInfo;
}







