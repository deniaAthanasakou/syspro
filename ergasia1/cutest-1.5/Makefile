CC = gcc -g
FILES = AllTests.c CuTest.c CuTestTrie.c CuTestPostingList.c ../map.c ../methods.c ../trie.c ../postingList.c ../documentIdsHandler.c
OBJECTS = AllTests.o CuTest.o CuTestTrie.o CuTestPostingList.o ../map.o ../methods.o ../trie.o ../postingList.o ../documentIdsHandler.o
OUT = test
HEADERS = CuTest.h CuTestTrie.h CuTestPostingList.h ../map.h ../methods.h ../trie.h ../postingList.h ../documentIdsHandler.h

all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES)
	make clean

AllTests.o: AllTests.c
	$(CC) -c AllTests.c
	
CuTest.o: CuTest.c
	$(CC) -c CuTest.c	

CuTestStack.o: CuTestStack.c
	$(CC) -c CuTestStack.c

CuTestTrie.o: CuTestTrie.c
	$(CC) -c CuTestTrie.c

CuTestPostingList.o: CuTestPostingList.c
	$(CC) -c CuTestPostingList.c		
	
map.o: ../map.c
	$(CC) -c ../map.c	

methods.o: ../methods.c
	$(CC) -c ../methods.c
	
trie.o: ../trie.c
	$(CC) -c ../trie.c	

postingList.o: ../postingList.c
	$(CC) -c ../postingList.c				

documentIdsHandler.o: ../documentIdsHandler.c
	$(CC) -c ../documentIdsHandler.c				

clean:
	rm -f $(OBJECTS)

