#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query.h"

int search(arrayWords* array, Map* map, Trie* trie){
}

void documentFrequency(arrayWords* array, Trie* trie){
	int occurrences=0;
	if(array->length!=0){
		for(int i=0; i<array->length; i++){
			occurrences=0;
			char* wordToSearch = array->words[i];
			
			postingList* pL = searchWordInTrie(trie, wordToSearch);
			if(pL!=NULL){		//word exists
				occurrences = pL->documentFreq;
			}
			
			printf("%s %d\n", wordToSearch, occurrences);
		}
	}
	else{
		//must get every word of trie
	}
}

void termFrequency(arrayWords* array, Trie* trie){
	if(array->length!=2){
		printf("Error! Wrong number of arguments. Please try again.\n");
		return;
	}
	int id = atoi(array->words[0]);
	if(id<0){
		printf("Error! Invalid ID. Please try again.\n");
		return;
	}
	char* wordToSearch = array->words[1];
	//printf("id = %d\n", id);
	//printf("word = %s\n", wordToSearch);
	
	int occurrences=0;
	
	postingList* pL = searchWordInTrie(trie, wordToSearch);
	if(pL!=NULL){		//word exists
		OccurrencesInText* node = searchForId(pL, id);
		if(node!=NULL){
			occurrences = node->occurrences;
		}
	}
	printf("%d %s %d\n", id, wordToSearch, occurrences);
	
}
