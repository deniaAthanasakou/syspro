CC = gcc -g
FILES = main.c methods.c map.c trie.c
OBJECTS = main.o methods.o map.o trie.o
OUT = minisearch
HEADERS = methods.h map.h trie.h


all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES)
	make clean
	
main.o: main.c
	$(CC) -c main.c

methods.o: methods.c
	$(CC) -c methods.c
	
map.o: map.c
	$(CC) -c map.c	

trie.o: trie.c
	$(CC) -c trie.c		

clean:
	rm -f $(OBJECTS)s

