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
	
Trie* insertLetterIntoTrie(Trie* trie, char charForInsert, bool setPostingList, int id){

	Trie* trieOfInsert = getSameLetterNode(trie,  charForInsert);
	if(trieOfInsert == NULL){
		trieOfInsert = malloc(sizeof(Trie));
		initializeTrie(&trieOfInsert);	
	}
	if (trieOfInsert->letter=='\0'){
		trieOfInsert->letter = charForInsert;
	}
	if(setPostingList){
		if(trieOfInsert->pL==NULL){
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

void insertFullWordIntoTrie(Trie* trie, char* word, int id){
	Trie* nextVertical = trie;
	Trie* insertedNode = NULL;
	//printf("word %s\n", word);
	for(int i=0; i<strlen(word); i++){
		bool setPostingList = false;
		if(i==strlen(word)-1)		//last letter
			setPostingList = true;
		insertedNode = insertLetterIntoTrie(nextVertical, word[i], setPostingList, id);
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

void insertLineTextIntoTrie(Trie* trie, char* line, int id){
	char* word;
	word = strtok(line, " \t");
	while(word!=NULL){
		
		char* wordToInsert = malloc((strlen(word)+1)*sizeof(char));
		strcpy(wordToInsert,word);
		insertFullWordIntoTrie(trie, wordToInsert, id);
		
		free(wordToInsert);
		wordToInsert = NULL;
		
		word = strtok(NULL, " \t");
	}
}


void InsertAllLinesIntoTrie(Trie* trie, Map* map){
	for(int i=0; i<map->length; i++){
		insertLineTextIntoTrie(trie,map->array[i].text ,map->array[i].id);
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
	//printf("searching for word '%s'\n", word);
	for(int i=0; i<strlen(word); i++){
		tempTrie = horizontalTraversal(tempTrie, word[i]);
		if(tempTrie==NULL){
			//printf("Letter '%c' does not exist in this level, so word '%s' does not exist either\n", word[i], word);
			return NULL;
		}
		prevTrie = tempTrie;
		tempTrie = tempTrie->verticalNext;
	}
	return prevTrie->pL;
	
}







































 
 
