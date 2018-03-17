#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayWords.h"
#include "map.h"
#include "trie.h"
#include "query.h"

int main (int argc,char* argv[]){
	if(argc<3 || argc>5 || argc==4){
		printf("Error! Wrong Number of Arguments.\n");
		exit(1);
	}
	char* fileName=NULL;
	int KResults=10;
	for(int i=0; i<argc; i++){
		if(!strcmp(argv[i],"-i"))
			fileName=argv[i+1];							//argument before initialize file should be -i
		else if(!strcmp(argv[i],"-k"))
			KResults=atoi(argv[i+1]);						//argument before query file should be -q
	}
	
	if(fileName==NULL){
		printf("Error! No input file was given.\n");
		exit(1);
	}
	if(KResults<=0){
		printf("Error! Invalid value for K.\n");
		exit(1);
	}
	printf("K is %d\n",KResults);
	
	
	
	Map* map = createMap();
	
	
	//initialize
	FILE *initFile;
	initFile = fopen (fileName,"r");
	int init = 0;
	if (initFile!=NULL)
	{
		init = getMapFromFile(initFile, map);
		fclose (initFile);
	}
	if (init==0){
		printf("Error! Map was not initialized from file.\n");
		destroyMap(map);
		exit(1);
		
	}
	
	
	ContainsTrie* containsTrie = malloc(sizeof(ContainsTrie));
	initializeContainsTrie(&containsTrie);
	InsertAllLinesIntoTrie(containsTrie,map);
	
	//printf("Printing trie Horizontally\n");
	//printTrieHorizontally(containsTrie->firstNode);
	//printTrieVertically(containsTrie->firstNode);
	//printMap(map);
	
		
	//read user input for queries
	char *line = NULL;
	size_t len = 0;

	char* query = NULL;
	while(1){
		printf("\nPlease input your query\n");
		printf("Your choices are:\n\n/search word1 word2 ... word 10\n/df (word)\n/tf id word\n/exit\n\n");
		if(getline(&query, &len, stdin) != -1){
			char* instruction = strtok(query," \t\n");
			char* remainingLine = strtok(NULL,"\n");
			//printf("INSTRUCTION %s\n", instruction);
			//printf("REMAINING LINE %s\n", remainingLine);
			arrayWords* array = stringToArray(remainingLine);
			//printArrayWords(array);
			if(strcmp(instruction,"/search")==0){
				search(array, map, containsTrie, KResults);
			}
			else if(strcmp(instruction,"/df")==0){
				documentFrequency(array,containsTrie->firstNode);
			}
			else if(strcmp(instruction,"/tf")==0){
				termFrequency(array, containsTrie->firstNode);
			}
			else if(strcmp(instruction,"/exit")==0){
				if (query){
					free(query);
					query=NULL;
				}
				deleteArrayWords(array);
				break;
			}
			else{
				printf("Error! Wrong query. Please try again.\n"); 
			}
			deleteArrayWords(array);
		}
		else{
			if (query){
				free(query);
				query=NULL;
			}
			break;
		}
	}
	printf("End of while\n");
	
	destroyMap(map);
	destroyContainsTrie(containsTrie);
	
	return 0;
	
	
	
	
	
	
	
	
	
	
	
	
	
}
