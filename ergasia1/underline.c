#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "underline.h"


void initializeUnderline(Underline* underline){
	underline->length = 5;
	underline->position = 0;
	underline->array = malloc(sizeof(UnderlineNode)*underline->length);
	for(int i=0; i<underline->length; i++){
		initializeUnderlineNode(&(underline->array[i]));
	}
}

void initializeUnderlineNode(UnderlineNode* node){
	node->startingPoint = -1;
	node->endingPoint = -1;
}

void doubleUnderline(Underline* underline){
	int oldLength = underline->length;
	underline->length*=2;
	underline->array = realloc(underline->array,sizeof(UnderlineNode)*underline->length);
	for(int i=oldLength; i<underline->length; i++){
		initializeUnderlineNode(&(underline->array[i]));
	}
}


void insertIntoUnderline(Underline* underline, int startingPoint, int endingPoint){
	if(underline->position == underline->length){
		doubleUnderline(underline);
	}
	//printf("underline->position = %d\n", underline->position);
	underline->array[underline->position].startingPoint = startingPoint;
	underline->array[underline->position].endingPoint = endingPoint;
	underline->position++;
}

int getEndingPointFromStartingPoint(Underline* underline, int startingPoint){
	for(int i=0; i<underline->position; i++){
		if(underline->array[i].startingPoint == startingPoint)
			return underline->array[i].endingPoint;
	}
	return -1;				//not found
}


void deleteUnderline(Underline* underline){
	if(underline!=NULL){
		free(underline->array);
		free(underline);
	}
}

void printUnderline(Underline* underline){
	if(underline->position==0)
		return;
	printf("Printing elements for underline:\n");
	for(int i=0; i<underline->position; i++){
		printf("Starting point: '%d', Ending point '%d'\n",underline->array[i].startingPoint, underline->array[i].endingPoint);
	}
}

