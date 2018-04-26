CC = gcc -g
FILES = AllTests.c CuTest.c CuTestProcess.c CuTestPathStruct.c CuTestTrie.c CuTestPostingList.c CuTestList.c ../process.c ../pathStruct.c ../trie.c ../postingList.c ../list.c
OBJECTS = AllTests.o CuTest.o CuTestProcess.o CuTestPathStruct.o CuTestTrie.o CuTestPostingList.o CuTestList.o process.o pathStruct.o trie.o postingList.o list.o
OUT = test
HEADERS = CuTest.h CuTestProcess.h CuTestPathStruct.h CuTestTrie.h CuTestPostingList.h CuTestList.h ../process.h ../pathStruct.h ../trie.h ../postingList.h ../list.h

all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES)
	make clean

AllTests.o: AllTests.c
	$(CC) -c AllTests.c
	
CuTest.o: CuTest.c
	$(CC) -c CuTest.c	
				
CuTestProcess.o: CuTestProcess.c
	$(CC) -c CuTestProcess.c
	
CuTestPathStruct.o: CuTestPathStruct.c
	$(CC) -c CuTestPathStruct.c	
	
CuTestTrie.o: CuTestTrie.c
	$(CC) -c CuTestTrie.c	
	
CuTestPostingList.o: CuTestPostingList.c
	$(CC) -c CuTestPostingList.c
	
CuTestList.o: CuTestList.c
	$(CC) -c CuTestList.c			
	
process.o: ../process.c
	$(CC) -c ../process.c	
	
pathStruct.o: ../pathStruct.c
	$(CC) -c ../pathStruct.c	
	
trie.o: ../trie.c
	$(CC) -c ../trie.c		
	
postingList.o: ../postingList.c
	$(CC) -c ../postingList.c		
	
list.o: ../list.c
	$(CC) -c ../list.c			

clean:
	rm -f $(OBJECTS)

