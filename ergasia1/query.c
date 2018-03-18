#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "query.h"
#include "documentIdsHandler.h"
#include "printForSearch.h"
#include "idf.h"

int search(arrayWords* array, Map* map, ContainsTrie* containsTrie, int topK){

	if(array->position<1){			//no search word was given
		return 0;
	}
	int elements = array->position;
	if(array->position>10){			//more than ten words were given, only the first 10 will be used
		elements = 10;
	}
	int printCounter=0;

	DifferentIds *diffIds = malloc(sizeof(DifferentIds));
	createDifferentIds(diffIds);
	
	IdfForWords* idfForWords = malloc(sizeof(IdfForWords));
	initializeIdfForWords(idfForWords, elements);
	
	int allWords = getNoOfAllWords(map);		
	double avgdl = (double)allWords / map->position;
	for(int i=0; i<elements; i++){			//for each word get diffIds
		double docFreq=0.0;
		char* wordToSearch = array->words[i];	
		
		postingList* pL = searchWordInTrie(containsTrie->firstNode, wordToSearch);		//return posting list of wordToSearch
		if(pL!=NULL){		//word exists
			docFreq = (double)pL->documentFreq;
			getDifferentIds(pL, diffIds);									//get different text ids from posting lists
			
		}
		double N = (double)map->position;
		double idf = log10((double)(N - docFreq+0.5)/(docFreq+0.5));		//compute idf for word
		insertionSortIdfForWords(idfForWords, idf,  wordToSearch);
	}
	PrintForSearch* pfs = malloc(sizeof(PrintForSearch));
	initializePrintForSearch(pfs, array);
	
	for(int i=0; i<diffIds->position; i++){		//for each different document
		double score = 0.0;

		for(int j=0; j<elements; j++){			//for each word of query

			IdfForWordNode* idfNode = binarySearchIdfForWord(idfForWords->array, array->words[j], 0,idfForWords->position-1, idfForWords->position-1);	//get idf for word
			score+=getScoreWithoutSum(containsTrie->firstNode, map, idfNode->idf, array->words[j], diffIds->ids[i], avgdl);			//compute score
		}
		
		
		char* line = map->array[ diffIds->ids[i]].text;
		insertionSortPrintForSearch(pfs,  diffIds->ids[i], score, line);				//insert printing info into pfs
		
	}
	printKResultsDESC(pfs, topK);															//print topK results
	
	deleteIdfForWords(idfForWords);
	deletePrintForSearch(pfs);
	
	destroyDifferentIds(diffIds);
	
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
		return;
	}
	int id = atoi(array->words[0]);		
	if(id<0){
		return;
	}
	char* wordToSearch = array->words[1];
	
	int occurrences=0;
	
	postingList* pL = searchWordInTrie(trie, wordToSearch);
	if(pL!=NULL){		//word exists
		OccurrencesInText* node = getNodeById(pL, id);
		if(node!=NULL){
			occurrences = node->occurrences;
		}
	}
	printf("%d %s %d\n", id, wordToSearch, occurrences);
	
}
