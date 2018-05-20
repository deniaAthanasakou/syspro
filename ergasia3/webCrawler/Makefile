CC = gcc -g
FILES = main.c errorHandler.c getPages.c
OBJECTS = main.o errorHandler.o getPages.o
OUT = mycrawler
HEADERS = errorHandler.h getPages.h

all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES) 
	make clean
	
main.o: main.c
	$(CC) -c main.c

errorHandler.o: errorHandler.c
	$(CC) -c errorHandler.c	
	
getPages.o: getPages.c
	$(CC) -c getPages.c	
		
clean:
	rm -f $(OBJECTS)

