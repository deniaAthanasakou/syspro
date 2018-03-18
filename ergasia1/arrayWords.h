#ifndef _ARRAY_WORDS_H_
#define _ARRAY_WORDS_H_
#include "map.h"
#include <stdbool.h>

typedef struct arrayWords{
	int length;				//length of array of strings (initially 10)
	char** words;			//array of strings
	int position;			//position of first null element
}arrayWords;

arrayWords* stringToArray(char* text);
void printArrayWords(arrayWords* array_of_words);
void deleteArrayWords(arrayWords* array_of_words);

void createArrayWords(arrayWords* array);
void doubleArrayWords(arrayWords* array);
void insertArrayWords(arrayWords* array, char* word);

bool checkifWordExists(arrayWords* array, char* word);

#endif
