CC = gcc -g
FILES = AllTests.c CuTest.c CuTestTrie.c ../map.c ../methods.c ../trie.c
OBJECTS = AllTests.o CuTest.o CuTestTrie.o ../map.o ../methods.o ../trie.o
OUT = test
HEADERS = CuTest.h CuTestTrie.h ../map.h ../methods.h ../trie.h

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
	
map.o: ../map.c
	$(CC) -c ../map.c	

methods.o: ../methods.c
	$(CC) -c ../methods.c
	
trie.o: ../trie.c
	$(CC) -c ../trie.c			


clean:
	rm -f $(OBJECTS)

