CC = gcc -g
FILES = main.c methods.c map.c
OBJECTS = main.o methods.o map.o
OUT = minisearch
HEADERS = methods.h map.h


all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES) -lm
	make clean
	
main.o: main.c
	$(CC) -c main.c

methods.o: methods.c
	$(CC) -c methods.c
	
map.o: map.c
	$(CC) -c map.c	

clean:
	rm -f $(OBJECTS)s

