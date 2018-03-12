#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "query.h"
#include "documentIdsHandler.h"

int search(arrayWords* array, Map* map, Trie* trie){
	if(array->position<1){
		printf("Error! No word was given. Please try again.\n");
		return 0;
	}
	int elements = array->position;
	if(array->position>10){
		printf("Error! Too many words were given. Only the first 10 will be taken into consideration.\n");
		elements = 10;
	}
	int printCounter=0;
	double IDF[elements];
	int* idArray = malloc(0*sizeof(int));
	int idArrayLength = 0;
	int idPosition = 0;
	for(int i=0; i<elements; i++){
		int docFreq=0;
		char* wordToSearch = array->words[i];
		
		postingList* pL = searchWordInTrie(trie, wordToSearch);
		if(pL!=NULL){		//word exists
			docFreq = pL->documentFreq;
		}
		if(docFreq!=0){
			idArrayLength+=docFreq;
			idArray = realloc(idArray,idArrayLength*sizeof(int));
			while(pL!=NULL){
				//pL->firstNode = 
			}
			
			
		}
		
		
		IDF[i] = log((double)(map->position-occurrences+0.5)/(double)(occurrences+0.5));
		//printf("IDF[%d]: %f\n", i, IDF[i]);
	}
	return 1;
	
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
