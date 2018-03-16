#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "query.h"
#include "documentIdsHandler.h"
#include "printForSearch.h"
#include "idf.h"

int search(arrayWords* array, Map* map, ContainsTrie* containsTrie){
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

	DifferentIds *diffIds = malloc(sizeof(DifferentIds));
	createDifferentIds(diffIds);
	
	IdfForWords* idfForWords = malloc(sizeof(IdfForWords));
	initializeIdfForWords(idfForWords, elements);
	
	int allWords = getNoOfAllWords(map);		
	double avgdl = (double)allWords / map->position;
	
	for(int i=0; i<elements; i++){			//for each word
		int docFreq=0;
		char* wordToSearch = array->words[i];	
		
		postingList* pL = searchWordInTrie(containsTrie->firstNode, wordToSearch);
		if(pL!=NULL){		//word exists
			docFreq = pL->documentFreq;
			
			getDifferentIds(pL, diffIds);	
			
		}

		double idf = log((double)(map->position - docFreq+0.5)/(double)(docFreq+0.5));
		insertionSortIdfForWords(idfForWords, idf,  wordToSearch);
	}
	
	PrintForSearch* pfs = malloc(sizeof(PrintForSearch));
	initializePrintForSearch(pfs);
	
	for(int i=0; i<diffIds->position; i++){		//for each different document
		double score = 0.0;
		MapNode* node = getMapNode(map, diffIds->ids[i], 0, diffIds->position);
		char* line = node->text;
		arrayWords* arrayOfWords = stringToArray(line);
		for(int j=0; j<arrayOfWords->position; j++){	//for each word of document

			IdfForWordNode* idfNode = binarySearchIdfForWord(idfForWords->array,arrayOfWords->words[i], 0,idfForWords->position-1, idfForWords->position-1);
			if(idfNode==NULL)				//if word is not in query, continue
				continue;
			score+=getScoreWithoutSum(containsTrie->firstNode, map, idfNode->idf, arrayOfWords->words[i], diffIds->ids[i], avgdl);
			
		}
		deleteArrayWords(arrayOfWords);
		insertionSortPrintForSearch(pfs,  diffIds->ids[i], score, line);
	}
	/*for each line of text
		sum=0
		for each word
			sum+=get Score
			
	Sort sums
	print top-k sums
	*/
	/*na kanw mia domh p tha krataei to counter, to score, to text kai to text id kai meta na th sortarw me vash to score se fthinousa seira*/
	
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
