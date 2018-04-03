CC = gcc -g
FILES = main.c pathStruct.c
OBJECTS = main.o pathStruct.o
OUT = jobExecutor
HEADERS = pathStruct.h


all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES) 
	make clean
	
main.o: main.c
	$(CC) -c main.c
	
pathStruct.o: pathStruct.c
	$(CC) -c pathStruct.c	
		
clean:
	rm -f $(OBJECTS)

