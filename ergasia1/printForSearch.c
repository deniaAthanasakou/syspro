#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "printForSearch.h"
#include "underline.h"

void initializePrintForSearch(PrintForSearch* pfs, arrayWords* array){
	pfs->length = 10;
	pfs->position = 0;
	pfs->array = malloc(pfs->length * sizeof(PrintForSearchNode));
	pfs->queryWords = array;
	pfs->screenColumns = 136;
	pfs->spacesBeforeText = 22;
	for(int i=0; i<pfs->length ; i++){
		initializePrintForSearchNode(&(pfs->array[i]));
	}
}

void initializePrintForSearchNode(PrintForSearchNode* node){
	node->textId = -1;
	node->score = -1.0;
	node->text = NULL;
	
}

void doublePrintForSearch(PrintForSearch* pfs){
	int oldLength = pfs->length;
	pfs->length*=2;
	pfs->array = realloc(pfs->array,sizeof(PrintForSearchNode)*pfs->length);
	for(int i=oldLength; i<pfs->length ; i++){
		initializePrintForSearchNode(&(pfs->array[i]));
	} 
}

int binaryPrintForSearch(PrintForSearchNode* array, double score, int first, int last, int realLastElement){
	if(realLastElement==-1)	//there are no elements in array
		return 0;
	if (last <= first){
 	     return (score >array[first].score)?  (first + 1): first;
    }
 
    int mid = (first + last)/2;
 
    if(score == array[mid].score)	
         return mid+1;
 
    if(score > array[mid].score)
        return binaryPrintForSearch(array, score, mid+1, last, realLastElement);
    return binaryPrintForSearch(array, score, first, mid-1, realLastElement);
}

void insertionSortPrintForSearch(PrintForSearch* pfs, int textId, double score, char* text){
	if(pfs->position==pfs->length){	//double array
		doublePrintForSearch(pfs);
	}
	
	// find location where element sould be inseretd
	int loc = binaryPrintForSearch(pfs->array, score, 0, pfs->position-1, pfs->position-1);	

	int j = pfs->position-1;	//position of last element
	// Move all elements after location to create space
	while (j >= loc)
	{
	   pfs->array[j+1] = pfs->array[j];
	    j--;
	}
    
	pfs->array[j+1].textId = textId;
	pfs->array[j+1].score = score;
	pfs->array[j+1].text = text;		//must not be deleted
	pfs->position++;
}

void deletePrintForSearch(PrintForSearch* pfs){
	free(pfs->array);
	free(pfs);
	pfs = NULL;
}

void printPrintForSearchElements(PrintForSearch* pfs){
	printf("Printing PrintForSearch\n");
	printf("query words are:\n");
	printArrayWords(pfs->queryWords);
	for(int i=0; i<pfs->position; i++){
		printf("TEXT ID '%d', SCORE '%f', TEXT '%s'\n", pfs->array[i].textId, pfs->array[i].score, pfs->array[i].text);
	}
}

void printKResultsDESC(PrintForSearch* pfs, int topK){
	
	int upToHere=0;
	if(	pfs->position-1 - topK>=0)
		upToHere = pfs->position - topK;
	
	int counter=1;
	
	struct winsize w;
	int result = ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);	

	if(result!=-1)
		pfs->screenColumns = w.ws_col;				// get terminal width
	
	for(int i=pfs->position-1; i>=upToHere; i--){	//for each document
		printf("%4d.(%4d)[%8.4lf] ", counter,pfs->array[i].textId, pfs->array[i].score);	//print statistics
		
		int counterLine = 0;
		int textStarter = 0;
		int j = textStarter;
		int lengthOfTextRead = 0;
		
		char* wordToSearch = malloc(0);
		int wordToSearchLength = 0;
		int startingPoint = 0;			//used for underlining words
		int endingPoint = 0;			//used for underlining words
		
		while(lengthOfTextRead < strlen(pfs->array[i].text)){		//have yet not found eof
			if(counterLine!=0){
				for(int k=0; k<pfs->spacesBeforeText; k++){
					printf(" " );									//must print spaces to make up for loss of counter, text id and score
				}
			}
			
			Underline* underline = malloc(sizeof(Underline));
			initializeUnderline(underline);
			
			
			for(j=0; j<pfs->screenColumns - pfs->spacesBeforeText ; j++){					//print characters up to screenColumns
				if( pfs->array[i].text[j + lengthOfTextRead] == '\0')						//if eof was found then break
					break;

				char c = pfs->array[i].text[j + lengthOfTextRead];							//get current character

				int tempWordLength = 0;
				int tempCharacter = c;
				while(tempCharacter!=' ' & tempCharacter != '\t'){							//get length of current word
					if(tempCharacter == '\0')
						break;
					tempWordLength++;
					tempCharacter = pfs->array[i].text[j + lengthOfTextRead +tempWordLength];
				}
				if(j + tempWordLength-1 >= pfs->screenColumns - pfs->spacesBeforeText){			//check if word will be able to fit entirely into line. if not break
					lengthOfTextRead--;
					break;
				} 
				
				
				printf("%c", c );											
				
				if(c == ' ' || c == '\t'){														//if space was found, wordToSearch must be checked for underlining
					
					if(wordToSearchLength!=0){
						endingPoint = startingPoint + wordToSearchLength -1;

						wordToSearchLength++;
						wordToSearch = realloc(wordToSearch,wordToSearchLength*sizeof(char));
						wordToSearch[wordToSearchLength-1] = '\0'; 
						
						if(checkifWordExists(pfs->queryWords, wordToSearch)){					//if wordToSearch must be underlined
							insertIntoUnderline(underline,startingPoint,endingPoint);			//insert starting and ending points into struct underline
						}

						wordToSearchLength = 0;													//reinitialize wordToSearch and length
						free(wordToSearch);
						wordToSearch = malloc(0);
					}
					
					startingPoint = j + 1;
					
				}
				else{																			//if character was not space, insert character into wordToSearch
					wordToSearchLength++;
					wordToSearch = realloc(wordToSearch,wordToSearchLength*sizeof(char));
					wordToSearch[wordToSearchLength-1] = c; 
				}
				
				if(j==pfs->screenColumns - pfs->spacesBeforeText -1 && (pfs->array[i].text[j + lengthOfTextRead +1]==' ' || c == '\t')){	//if we've reached last character of line and next character is space 
					
					endingPoint = startingPoint + wordToSearchLength -1;
					wordToSearchLength++;
					wordToSearch = realloc(wordToSearch,wordToSearchLength*sizeof(char));
					wordToSearch[wordToSearchLength-1] = '\0'; 
					if(checkifWordExists(pfs->queryWords, wordToSearch)){					//check if word must be inserted into underline array
						insertIntoUnderline(underline,startingPoint,endingPoint);
					}
					
					
					wordToSearchLength = 0;
					free(wordToSearch);
					wordToSearch = malloc(0);
					startingPoint = j + 1;
				}	
			}
			printf("\n");																//print new line so that words can be underlined
			
	
			
			
			for(int k=0; k<pfs->spacesBeforeText; k++){									//must print spaces to make up for loss of counter, text id and score
				printf(" " );
			}
			for(int k=0; k<pfs->screenColumns - pfs->spacesBeforeText; k++){				//print ^ to underline word of query
				int endPoint = getEndingPointFromStartingPoint(underline, k);				//get endingPoint from function
				while(k<=endPoint){
					printf("^");
					k++;
				}
				printf(" ");

			}
			deleteUnderline(underline);
			printf("\n");																//print new line so that the rest of the text can be printed		
			
			textStarter= textStarter + pfs->screenColumns;
			lengthOfTextRead += j;
			counterLine++;
			
		}
		printf("\n");
		counter++;
		
		if(wordToSearch){
			free(wordToSearch);
			wordToSearch = NULL;
		}
		
	}
}


