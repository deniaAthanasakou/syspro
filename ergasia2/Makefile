CC = gcc -g
FILES = main.c pathStruct.c process.c trie.c postingList.c
OBJECTS = main.o pathStruct.o process.o trie.o postingList.o
OUT = jobExecutor
HEADERS = pathStruct.h process.h trie.h postingList.h


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
		
clean:
	rm -f $(OBJECTS)

