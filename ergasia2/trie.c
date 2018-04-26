#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
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
	
Trie* insertLetterIntoTrie(ContainsTrie* containsTrie, Trie* trie, char charForInsert, bool setPostingList, char* path, int lineOfWord, int wordOffset){

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
		insertIntoPostingList(trieOfInsert->pL, path, lineOfWord, wordOffset);
		
	}
	
	return trieOfInsert;
	
}

bool letterExists(Trie* trie, char charForInsert){
	if (trie->letter==charForInsert)
		return true;
	return false;	
}

void insertFullWordIntoTrie(ContainsTrie* containsTrie, Trie* trie, char* word, char* path, int lineOfWord, int wordOffset){
	Trie* nextVertical = trie;
	Trie* insertedNode = NULL;
	for(int i=0; i<strlen(word); i++){
		bool setPostingList = false;
		if(i==strlen(word)-1){		//last letter
			setPostingList = true;
		}
		insertedNode = insertLetterIntoTrie(containsTrie, nextVertical, word[i], setPostingList, path, lineOfWord, wordOffset);
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
/*
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
*/


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


int createTrieFromFile(ContainsTrie* containsTrie, char* fullPath){

	FILE* file = fopen(fullPath,"r");
	char *line = NULL;
	size_t len = 0;
	int read;
	if (file == NULL){
		printf("Error! Null file was given.\n");
		return 0;
	}
	
	int lineCounter = -1;
	
	
	while ((read = getline(&line, &len, file)) != -1) {
	 	lineCounter++;
		if(!strcmp(line, "\n")){	
			continue;
		}
		
		char* tempWord = strtok(line," \t");
		int bytesBeforeWord = 0;
		while(tempWord!=NULL){
			if(tempWord[strlen(tempWord)-1]=='\n'){
				tempWord[strlen(tempWord)-1]='\0';
			}
			printf("////////////////////////tempWord %s\n", tempWord);
			
			//inserting word into trie
			char* text = malloc((strlen(tempWord)+1)* sizeof(char));
			strcpy(text, tempWord);
			insertFullWordIntoTrie(containsTrie, containsTrie->firstNode, tempWord, fullPath, lineCounter, bytesBeforeWord);
			free(text);
			text=NULL;

			bytesBeforeWord+=strlen(tempWord) +1;	//1 is for space or tab			maybe i need to change it
			tempWord = strtok(NULL," \t");
			
			
		}
	}

	if (line){
		free(line);
		line=NULL;
	}
	return 1;

}


int createTrieFromDir(ContainsTrie* containsTrie, char* pathofDir){

	DIR *dir;
	struct dirent *ent;
	printf("pathofDir %s\n", pathofDir);
	dir = opendir(pathofDir);
	int noErrors = 1;
	if (dir != NULL) {
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
		//printf ("%s\n", ent->d_name);
		if(ent->d_name[0]=='.')
			continue;
		//correct file name
		//create path with pathofDir/filename	
		char* fileName = ent->d_name;
		char* fullPath = malloc(sizeof(char)*(strlen(pathofDir)+strlen(fileName)+2));
		strcpy(fullPath, pathofDir);
		strcat(fullPath, "/");
		strcat(fullPath, fileName);
		
		printf("FULL PATH IS %s\n", fullPath);
		
		noErrors = createTrieFromFile(containsTrie, fullPath);
		
		 free(fullPath);
		 fullPath=NULL;
		
	  }
	  
	 
	  closedir (dir);
	  
	  return noErrors;
	  
	} else {
	  /* could not open directory */
	  perror ("Error! Could not open directory.");
	  return 0;
	}
	
}



















 
 
