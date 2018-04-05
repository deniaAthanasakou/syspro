CC = gcc -g
FILES = main.c pathStruct.c process.c
OBJECTS = main.o pathStruct.o process.o
OUT = jobExecutor
HEADERS = pathStruct.h process.h


all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES) 
	make clean
	
main.o: main.c
	$(CC) -c main.c
	
pathStruct.o: pathStruct.c
	$(CC) -c pathStruct.c	
		
process.o: process.c
	$(CC) -c process.c	
		
clean:
	rm -f $(OBJECTS)

