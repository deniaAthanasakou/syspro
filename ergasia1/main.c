#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methods.h"
#include "map.h"
#include "trie.h"

int main (int argc,char* argv[]){
	if(argc!=5){
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
		init = initialize(initFile, map);
		fclose (initFile);
	}
	if (init==0){
		exit(1);
		
	}
	
	//printMap(map);
	
	Trie* trie = trie = malloc(sizeof(Trie));
	initializeTrie(&trie);
	InsertAllLinesIntoTrie(trie,map);
	
	printf("Printing trie Horizontally\n");
	printTrieHorizontally(trie);
	//printTrieVertically(trie);	
	//eisodos apo xrhsth 
	
	return 0;
}
