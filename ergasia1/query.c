#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query.h"

int search(arrayWords* array, Map* map, Trie* trie){
}

void documentFrequency(arrayWords* array, Trie* trie){
	int occurrences=0;
	int flagForArray=0;
	
	arrayWords* myArray = array; 
	
	if(myArray->position==0){			//must get every word of trie
		myArray = getAllWordsOfTrie(trie);
		flagForArray=1;
	}

	if(myArray->position!=0){
		for(int i=0; i<myArray->position; i++){
			occurrences=0;
			char* wordToSearch = myArray->words[i];
			
			postingList* pL = searchWordInTrie(trie, wordToSearch);
			if(pL!=NULL){		//word exists
				occurrences = pL->documentFreq;
			}
			
			printf("%s %d\n", wordToSearch, occurrences);
		}
		if(flagForArray==1)
			deleteArrayWords(myArray);
	}
}

void termFrequency(arrayWords* array, Trie* trie){
	if(array->position!=2){
		printf("Error! Wrong number of arguments. Please try again.\n");
		return;
	}
	int id = atoi(array->words[0]);
	if(id<0){
		printf("Error! Invalid ID. Please try again.\n");
		return;
	}
	char* wordToSearch = array->words[1];
	
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
