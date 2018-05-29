CC = gcc -g
FILES = AllTests.c CuTest.c CuTestQueue.c ../webCrawler/queue.c
OBJECTS = AllTests.o CuTest.o CuTestQueue.o queue.o
OUT = test
HEADERS = CuTest.h CuTestQueue.h ../webCrawler/queue.h

all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES)
	make clean

AllTests.o: AllTests.c
	$(CC) -c AllTests.c
	
CuTest.o: CuTest.c
	$(CC) -c CuTest.c	

CuTestQueue.o: CuTestQueue.c
	$(CC) -c CuTestQueue.c
				
queue.o: ../webCrawler/queue.c
	$(CC) -c ../webCrawler/queue.c				

clean:
	rm -f $(OBJECTS)

