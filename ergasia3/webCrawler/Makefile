CC = gcc -g -pthread
FILES = main.c errorHandler.c getPages.c queue.c pageHandler.c thread.c search.c
OBJECTS = main.o errorHandler.o getPages.o queue.o pageHandler.o thread.o search.o
OUT = mycrawler
HEADERS = errorHandler.h getPages.h queue.h pageHandler.h thread.h search.h

all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES) 
	make clean
	make makeJob
	
main.o: main.c
	$(CC) -c main.c

errorHandler.o: errorHandler.c
	$(CC) -c errorHandler.c	
	
getPages.o: getPages.c
	$(CC) -c getPages.c	

queue.o: queue.c
	$(CC) -c queue.c

pageHandler.o: pageHandler.c
	$(CC) -c pageHandler.c		

thread.o: thread.c
	$(CC) -c thread.c	

search.o: search.c
	$(CC) -c search.c		

makeJob:
	cd ../JobExecutor && $(MAKE)

clean:
	rm -f $(OBJECTS)



