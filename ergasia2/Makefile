CC = gcc -g
FILES = main.c pathStruct.c process.c trie.c postingList.c list.c instructions.c arrayWords.c bytesWordsLinesInfo.c
OBJECTS = main.o pathStruct.o process.o trie.o postingList.o list.o instructions.o arrayWords.o bytesWordsLinesInfo.o
OUT = jobExecutor
HEADERS = pathStruct.h process.h trie.h postingList.h list.h instructions.h arrayWords.h bytesWordsLinesInfo.h


all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES) 
	make clean
	
main.o: main.c
	$(CC) -c main.c
	
pathStruct.o: pathStruct.c
	$(CC) -c pathStruct.c	
		
process.o: process.c
	$(CC) -c process.c	
	
trie.o: trie.c
	$(CC) -c trie.c	
	
postingList.o: postingList.c
	$(CC) -c postingList.c			
		
list.o: list.c
	$(CC) -c list.c	
	
instructions.o: instructions.c
	$(CC) -c instructions.c		
	
arrayWords.o: arrayWords.c
	$(CC) -c arrayWords.c		
	
bytesWordsLinesInfo.o: bytesWordsLinesInfo.c
	$(CC) -c bytesWordsLinesInfo.c		
			
clean:
	rm -f $(OBJECTS)

