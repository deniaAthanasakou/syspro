CC = gcc -g
FILES = main.c errorHandler.c getPages.c queue.c pageHandler.c
OBJECTS = main.o errorHandler.o getPages.o queue.o pageHandler.o
OUT = mycrawler
HEADERS = errorHandler.h getPages.h queue.h pageHandler.h

all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES) 
	make clean
	
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

clean:
	rm -f $(OBJECTS)

