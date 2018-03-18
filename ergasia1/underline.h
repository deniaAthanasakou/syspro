#ifndef _UNDERLINE_H_
#define _UNDERLINE_H_
#include "arrayWords.h"

typedef struct UnderlineNode{
	int startingPoint;
	int endingPoint;
}UnderlineNode;

typedef struct Underline{		//contains array of [startingPoint, endingPoint] sets
	int length; 				//initially 5
	int position;				//position of first null element
	UnderlineNode* array;		
}Underline;


void initializeUnderline(Underline* underline);
void initializeUnderlineNode(UnderlineNode* node);
void doubleUnderline(Underline* underline);

void insertIntoUnderline(Underline* underline, int startingPoint, int endingPoint);

int getEndingPointFromStartingPoint(Underline* underline, int startingPoint);

void deleteUnderline(Underline* underline);
void printUnderline(Underline* underline);

#endif
