#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

int getMapFromFile(FILE* file, Map* map){
	char *line = NULL;
	size_t len = 0;
	int read;
	if (file == NULL){
		printf("Error! Null file was given\n");
		return 0;
	}
	int counter=0;	
	while ((read = getline(&line, &len, file)) != -1) {
		if(!strcmp(line, "\n")){	
			counter++;
			continue;
		}
		char* tempLine = strtok(line," \t");

		int lineNumber = atoi(tempLine);
		
		if(lineNumber!=counter){
			printf("Error in numbering file lines\n");
			if (line){
				free(line);
				line=NULL;
			}
			
			return 0;
		}
		
		char* remainingLine = strtok(NULL,"\n");
		
		//inserting lines into map
		char* text = malloc((strlen(remainingLine)+1)* sizeof(char));
		strcpy(text, remainingLine);
		insertIntoMap(map, lineNumber, text);
		counter++;		
	}
	reduceMapLength(map);

	if (line){
		free(line);
		line=NULL;
	}
	return 1;
}

Map* createMap(){
	Map* map = malloc(sizeof(Map));
	map->length = 5;
	map->position = 0;
	map->noOfWordsFull = -1;
	map->array = malloc(map->length*sizeof(MapNode));
	return map;
}
void insertIntoMap(Map* map, int id, char* text){
	MapNode node;
	node.id = id;
	node.text = text;
	node.noOfWords = getNoOfWordsOfMapText(&node);
	
	if(map->position+1==map->length){
		doubleMap(map);
	}
	map->array[map->position] = node;
	map->position++;
	
}

void doubleMap(Map* map){
	map->length*=2;
	map->array = (MapNode*)realloc(map->array, map->length*sizeof(MapNode));
	
}

void reduceMapLength(Map* map){
	map->array = (MapNode*)realloc(map->array, map->position*sizeof(MapNode));
	map->length = map->position;
}


int getNoOfWordsOfMapText(MapNode* node){		//returns the number of words that node->text contains
	char* word = malloc(sizeof(char)*(strlen(node->text)+1));
	strcpy(word, node->text); 
	char* pch;
	pch = strtok (word," \t");
	int noOfWords=0;
	while (pch != NULL)
	{	
		noOfWords++;
		pch = strtok (NULL, " \t");
	}
	if(word!=NULL)
		free(word);
	return noOfWords;
}


int getNoOfAllWords(Map* map){
	if(map->noOfWordsFull!=-1)
		return map->noOfWordsFull;
		
	int sum=0;
	for(int i=0; i<map->position; i++){
		sum+=map->array[i].noOfWords;
	}
	map->noOfWordsFull = sum;
	return sum;
}


void printMap(Map* map){
	printf("Printing map:\n");
	for(int i=0; i<map->position; i++){
		printf("id '%d', text '%s'\n", map->array[i].id,map->array[i].text);
	}
}

void destroyMap(Map* map){
	if(map!=NULL){
		for(int i=0; i<map->position; i++){
			free(map->array[i].text);
		}
		free(map->array);
		free(map);
		map=NULL;
	}
}
