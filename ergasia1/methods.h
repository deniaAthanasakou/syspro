#ifndef _METHODS_H_
#define _METHODS_H_
#include "map.h"

typedef struct arrayWords{
	int length;					//length of array of strings
	char** words;			//array of strings
}arrayWords;

int initialize(FILE* file, Map* map);
arrayWords* stringToArray(char* text);
void printArrayWords(arrayWords* array_of_words);
void deleteArrayWords(arrayWords* array_of_words);


#endif
