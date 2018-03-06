#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

void initializeTrie(Trie** trie){
	(*trie)->letter= '\0';
	(*trie)->verticalNext = NULL;
	(*trie)->horizontalNext = NULL;
	(*trie)->pL = NULL;
}
	
Trie* insertLetterIntoTrie(Trie* trie, char charForInsert){

	Trie* trieOfInsert = getSameLetterNode(trie,  charForInsert);
	if(trieOfInsert == NULL){
		trieOfInsert = malloc(sizeof(Trie));
		initializeTrie(&trieOfInsert);	
	}
	if (trieOfInsert->letter=='\0'){
		trieOfInsert->letter = charForInsert;
	}
	return trieOfInsert;
	
}

bool letterExists(Trie* trie, char charForInsert){
	if (trie->letter==charForInsert)
		return true;
	return false;	
}

void insertFullWordIntoTrie(Trie* trie, char* word){
	Trie* nextVertical = trie;
	Trie* insertedNode = NULL;
	//printf("word %s\n", word);
	for(int i=0; i<strlen(word); i++){

		insertedNode = insertLetterIntoTrie(nextVertical, word[i]);
		if(i!=strlen(word)-1 && insertedNode->verticalNext==NULL){
			nextVertical = malloc(sizeof(Trie));
			initializeTrie(&nextVertical);
			insertedNode->verticalNext = nextVertical;
			//printf("next node ptr %p,inserted->next %p, nextVertical %p\n",trie->verticalNext,insertedNode->verticalNext, nextVertical);
		}
		nextVertical  = insertedNode->verticalNext;
	}
}

Trie* getSameLetterNode(Trie* trie, char charForInsert){
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

void insertLineTextIntoTrie(Trie* trie, char* line){
	char* word;
	word = strtok(line, " \t");
	while(word!=NULL){
		
		char* wordToInsert = malloc((strlen(word)+1)*sizeof(char));
		strcpy(wordToInsert,word);
		insertFullWordIntoTrie(trie, wordToInsert);

		word = strtok(NULL, " \t");
	}
}


void InsertAllLinesIntoTrie(Trie* trie, Map* map){
	for(int i=0; i<map->length; i++){
		insertLineTextIntoTrie(trie,map->array[i].text);
	}
}



void printTrieHorizontally(Trie* trie){
	if(trie==NULL){
		printf("NULL TRIE\n");
		return;
	}
	printf("'%c'\n",trie->letter);
	printTrieHorizontally(trie->horizontalNext);	
	//printTrieVertically(trie);	
}

void printTrieVertically(Trie* trie){
	if(trie==NULL){
		printf("\nNULL TRIE\n");
		return;
	}
	printf("%c",trie->letter);
	printTrieVertically(trie->verticalNext);	
}














































 
 
