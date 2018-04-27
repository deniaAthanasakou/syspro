#ifndef _BYTES_WORDS_LINES_INFO_H_
#define _BYTES_WORDS_LINES_INFO_H_
#include <stdbool.h>

typedef struct BytesWordsLinesNode{
	char* fileName;
	int bytes;
	int words;
	int lines;
}BytesWordsLinesNode;

typedef struct BytesWordsLinesStruct{
	BytesWordsLinesNode* array;
	int position;
	int length;		//initially 5
}BytesWordsLinesStruct;


BytesWordsLinesStruct* createBytesWordsLinesStruct();
void doubleBytesWordsLinesStruct(BytesWordsLinesStruct* info);
void insertBytesWordsLinesStruct(BytesWordsLinesStruct* info, char* fileName, int bytes, int words, int lines);

void printBytesWordsLinesStruct(BytesWordsLinesStruct* info);
void deleteBytesWordsLinesStruct(BytesWordsLinesStruct* info);

//bool checkifWordExists(arrayWords* array, char* word);

#endif
