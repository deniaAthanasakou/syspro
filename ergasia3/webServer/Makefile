CC = gcc -g
FILES = main.c socketHandler.c errorHandler.c
OBJECTS = main.o socketHandler.o errorHandler.o
OUT = myhttpd
HEADERS = socketHandler.h errorHandler.h

all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES) 
	make clean
	
main.o: main.c
	$(CC) -c main.c

socketHandler.o: socketHandler.c
	$(CC) -c socketHandler.c	

errorHandler.o: errorHandler.c
	$(CC) -c errorHandler.c	
	
	
clean:
	rm -f $(OBJECTS)

