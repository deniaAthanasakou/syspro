CC = gcc -g -pthread
FILES = AllTests.c CuTest.c CuTestQueue.c ../webCrawler/queue.c ../webServer/errorHandler.c
OBJECTS = AllTests.o CuTest.o CuTestQueue.o queue.o errorHandler.o
OUT = test
HEADERS = CuTest.h CuTestQueue.h  ../webCrawler/queue.h  ../webServer/errorHandler.h

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

	

errorHandler.o: ../webServer/errorHandler.c
	$(CC) -c ../webServer/errorHandler.c				

clean:
	rm -f $(OBJECTS)

