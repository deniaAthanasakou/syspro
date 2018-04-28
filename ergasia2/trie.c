#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "trie.h"

void initializeContainsTrie(ContainsTrie** containsTrie){
	(*containsTrie)->noOfTrieWords=0;
	(*containsTrie)->firstNode = malloc(sizeof(Trie));
	initializeTrie(&((*containsTrie)->firstNode));
	
	(*containsTrie)->info = createBytesWordsLinesStruct();
	(*containsTrie)->mapOfFiles = createMap();
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


void destroyContainsTrie(ContainsTrie* containsTrie){
	if(containsTrie!=NULL){
		deleteBytesWordsLinesStruct(containsTrie->info);
		destroyMap(containsTrie->mapOfFiles);
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

	int fd = open(fullPath, O_RDONLY);
	struct stat buf;
	fstat(fd, &buf);
	int numBytes = buf.st_size;
	if(fd != -1)
	{
		close(fd);
	}

	//insertIntoMap(containsTrie->map, char* fileName)
	FILE* file = fopen(fullPath,"r");
	char *line = NULL;
	size_t len = 0;
	int read;
	if (file == NULL){
		printf("Error! Null file was given.\n");
		return 0;
	}
	
	char* path = malloc((strlen(fullPath)+1)*sizeof(char));
	strcpy(path, fullPath);
	MapNode* mapNode = insertIntoMap(containsTrie->mapOfFiles, path);
	
	
	int lineCounter = -1;
	int numWords = 0;
	
	while ((read = getline(&line, &len, file)) != -1) {
	 	lineCounter++;
	 	
		
		//inserting lines into map
		char* text = malloc((strlen(line)+1)* sizeof(char));
		strcpy(text, line);
		if(text[strlen(line)-1]=='\n');{
			text[strlen(line)-1] = '\0';
		}
		insertIntoMapNode(mapNode, line);
		free(text);
		text=NULL;
	 		

		if(!strcmp(line, "\n")){
			continue;
		}
		
		int multipleSpacesFlag = 0;
		int lengthOfWord = 0;
		int maxLength = 10;
		//int bytesBeforeNextWord = -1;
		int bytesBeforeWord = 0;
		int spaces = 0;
		int numOfSpacesAtBeggining = 0;
		
		int thisLineStartedWithWhitespace = 0;
		
		char* word = malloc(maxLength);
		for(int i=0; i<strlen(line); i++){

			if(line[i] == ' ' || line[i] == '\n' || line[i] == '\t'){		//whitespace
				if(i==0){				//count spaces from beggining
					numOfSpacesAtBeggining++;
					int j = i;
					while(line[j+1] == ' ' || line[j+1] == '\n' || line[j+1] == '\t'){
						j++;
						numOfSpacesAtBeggining++;

					}
				}
				else{
					spaces = 1; //first space
					while(line[i+1] == ' ' || line[i+1] == '\n' || line[i+1] == '\t'){
						multipleSpacesFlag = 1;
						i++;
						spaces++;

					}
				
					if(multipleSpacesFlag)
						i--;			//move backwards so that next for can show next character
				
				}

				if(lengthOfWord!=0){
					word = realloc(word, lengthOfWord +1 *sizeof(char));
					word[lengthOfWord] = '\0';

					if(numOfSpacesAtBeggining>0)
						bytesBeforeWord = numOfSpacesAtBeggining;
						
						
					numOfSpacesAtBeggining=0;
				//	printf("word %s\n", word);
					insertFullWordIntoTrie(containsTrie, containsTrie->firstNode, word, fullPath, lineCounter, bytesBeforeWord);
					numWords++;
					bytesBeforeWord += lengthOfWord + spaces;
					
					spaces = 0;
					
					free(word);
					word = NULL;
					lengthOfWord=0;
					
				}
				
				multipleSpacesFlag = 0;
				
			}
			else{				//character
				if(word == NULL){
					word = malloc(maxLength);
					lengthOfWord=0;
				}
				if(lengthOfWord == maxLength-1){
					maxLength*=2;
					word = realloc(word, maxLength *sizeof(char));
				}
				word[lengthOfWord] = line[i];
				lengthOfWord++;
			
			}
			
		}
		if(word)
			free(word);
	}
	reduceMapNodeArrayLength(mapNode);

	if (line){
		free(line);
		line=NULL;
	}
	
	
	insertBytesWordsLinesStruct(containsTrie->info, fullPath, numBytes, numWords, lineCounter+1);
	
	return 1;

}


int createTrieFromDir(ContainsTrie* containsTrie, char* pathofDir){





	if (pathofDir[0] == '/') 
   	 	memmove(pathofDir, pathofDir+1, strlen(pathofDir));
		
//	printf("pathofDir-------------------------------------- %s\n", pathofDir);
	DIR *dir;
	struct dirent *ent;
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
		
		//printf("FULL PATH IS %s\n", fullPath);
		
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



















 
 
