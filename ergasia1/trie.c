#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

void initializeContainsTrie(ContainsTrie** containsTrie){
	(*containsTrie)->noOfTrieWords=0;
	(*containsTrie)->firstNode = malloc(sizeof(Trie));
	initializeTrie(&((*containsTrie)->firstNode));
}


void initializeTrie(Trie** trie){
	(*trie)->letter= '\0';
	(*trie)->verticalNext = NULL;
	(*trie)->horizontalNext = NULL;
	(*trie)->pL = NULL;
}
	
Trie* insertLetterIntoTrie(ContainsTrie* containsTrie, Trie* trie, char charForInsert, bool setPostingList, int id){

	Trie* trieOfInsert = getSameLetterNode(trie,  charForInsert);
	if(trieOfInsert == NULL){
		trieOfInsert = malloc(sizeof(Trie));
		initializeTrie(&trieOfInsert);	
	}
	if (trieOfInsert->letter=='\0'){
		trieOfInsert->letter = charForInsert;
	}
	if(setPostingList){						//last letter of word was inserted
		if(trieOfInsert->pL==NULL){	//new word will be inseted
			containsTrie->noOfTrieWords++;
			trieOfInsert->pL = malloc(sizeof(postingList));
			createPostingList(trieOfInsert->pL);
		}
		insertIntoPostingList(trieOfInsert->pL, id);
		
	}
	return trieOfInsert;
	
}

bool letterExists(Trie* trie, char charForInsert){
	if (trie->letter==charForInsert)
		return true;
	return false;	
}

void insertFullWordIntoTrie(ContainsTrie* containsTrie, Trie* trie, char* word, int id){
	Trie* nextVertical = trie;
	Trie* insertedNode = NULL;
	for(int i=0; i<strlen(word); i++){
		bool setPostingList = false;
		if(i==strlen(word)-1){		//last letter
			setPostingList = true;
		}
		insertedNode = insertLetterIntoTrie(containsTrie, nextVertical, word[i], setPostingList, id);
		if(i!=strlen(word)-1 && insertedNode->verticalNext==NULL){
			nextVertical = malloc(sizeof(Trie));
			initializeTrie(&nextVertical);
			insertedNode->verticalNext = nextVertical;
		}
		nextVertical  = insertedNode->verticalNext;
	}
}

Trie* getSameLetterNode(Trie* trie, char charForInsert){		//goes through trie horrizontally and if charForInsert is not found returns first Null node 
	Trie* nextHorizontal = trie;
	while(nextHorizontal!=NULL && nextHorizontal->letter!='\0'){
		if(letterExists(nextHorizontal,charForInsert)){
			return nextHorizontal;
		}
		if(nextHorizontal-> horizontalNext == NULL){
			Trie* tempNode = malloc(sizeof(Trie));
			initializeTrie(&tempNode);	
			nextHorizontal->horizontalNext = tempNode;
		}
		nextHorizontal = nextHorizontal->horizontalNext;
	}
	return nextHorizontal;	
}

void insertLineTextIntoTrie(ContainsTrie* containsTrie, Trie* trie, char* line, int id){
	char* tempLine = malloc((strlen(line)+1)*sizeof(char));
	strcpy(tempLine, line);
	char* word;
	word = strtok(tempLine, " \t");
	while(word!=NULL){
		
		char* wordToInsert = malloc((strlen(word)+1)*sizeof(char));
		strcpy(wordToInsert,word);
		insertFullWordIntoTrie(containsTrie, trie, wordToInsert, id);		//insert word
		
		free(wordToInsert);
		wordToInsert = NULL;
		
		word = strtok(NULL, " \t");
	}
	if(tempLine)
		free(tempLine);
}


void InsertAllLinesIntoTrie(ContainsTrie* containsTrie, Map* map){
	for(int i=0; i<map->length; i++){
		insertLineTextIntoTrie(containsTrie, containsTrie->firstNode, map->array[i].text ,map->array[i].id);
	}
}



void destroyContainsTrie(ContainsTrie* containsTrie){
	if(containsTrie!=NULL){
		destroyTrie(containsTrie->firstNode);
		free(containsTrie);
	}
}


void destroyTrie(Trie* trie){
	if(trie!=NULL){
		destroyTrie(trie->verticalNext);
		destroyTrie(trie->horizontalNext);
		destroySingleNode(trie);
	}
}


void destroySingleNode(Trie* trie){
	destroyPostingList(trie->pL);
	free(trie);
	trie=NULL;
}

Trie* horizontalTraversal(Trie* trie, char charForInsert){
	Trie* nextHorizontal = trie;
	while(nextHorizontal!=NULL){
		if(letterExists(nextHorizontal,charForInsert)){
			return nextHorizontal;
		}
		nextHorizontal = nextHorizontal->horizontalNext;
	}
	return nextHorizontal;	
}


postingList* searchWordInTrie(Trie* trie, char* word){
	Trie* tempTrie = trie;
	Trie* prevTrie = trie;
	for(int i=0; i<strlen(word); i++){
		tempTrie = horizontalTraversal(tempTrie, word[i]);
		if(tempTrie==NULL){
			return NULL;
		}
		prevTrie = tempTrie;
		tempTrie = tempTrie->verticalNext;
	}
	return prevTrie->pL;
	
}

arrayWords* getAllWordsOfTrie(Trie* trie){
	arrayWords* array = malloc(sizeof(arrayWords));
	createArrayWords(array);
	while(trie!=NULL){
		char* word = malloc(sizeof(char));
		word[0] = '\0';
		word = recGetWordsFromTrie(trie, trie, word, array);
		free(word);
		
		trie = trie->horizontalNext;
	}
	return array;
}

char* recGetWordsFromTrie(Trie* originalTrie, Trie* trie, char* word, arrayWords* array){	//returns word that exists in trie
	if (trie!=NULL){
		int newLength = strlen(word)+1;
		
		word = realloc(word, (newLength+1)*sizeof(char));
		
		word[newLength -1] = trie->letter;
		word[newLength] = '\0';
    	if(trie->pL!=NULL){	
    		char* wordForInsert = malloc((strlen(word)+1)* sizeof(char));
			strcpy(wordForInsert,word);  
			insertArrayWords(array, wordForInsert); //add word into arrayOfWords
		}
    }
    if (trie->verticalNext!=NULL){	
    	word = recGetWordsFromTrie(originalTrie, trie->verticalNext, word, array);
    }
    int newLength = strlen(word)-1;
	if(newLength>0){
		word = realloc(word, (newLength+1)*sizeof(char));
		word[newLength] = '\0';
	}
	
    if(trie->horizontalNext == originalTrie->horizontalNext && trie->horizontalNext!=NULL){
    	return word;
    }
    if (trie->horizontalNext!=NULL){
    	word = recGetWordsFromTrie(originalTrie, trie->horizontalNext, word, array);
    }
    return word;
}


double getScoreWithoutSum(Trie* trie, Map* map, double idf, char* word, int textId, double avgdl){
	double k1 = 1.2;
	double b = 0.75;
	
	double tf = 0.0;
	
	postingList* pL = searchWordInTrie(trie, word);		//get posting list of word
	if(pL!=NULL){		//word exists
		OccurrencesInText* node = getNodeById(pL, textId);
		if(node!=NULL){
			tf = (double)node->occurrences;
		}
	} 
	
	if(tf==0 || idf==0 || map->position==0){
		return 0;
	}
	
	double D = (double)map->array[textId].noOfWords;
	
	double result = (idf *tf*(k1+1.0))/(tf + k1 *(1.0 - b + (b*D/avgdl)));

	return result;
	
}


































 
 
