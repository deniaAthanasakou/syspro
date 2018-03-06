CC = gcc -g
FILES = main.c methods.c map.c trie.c postingList.c
OBJECTS = main.o methods.o map.o trie.o postingList.o
OUT = minisearch
HEADERS = methods.h map.h trie.h postingList.h


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
	
postingList.o: postingList.c
	$(CC) -c postingList.c		

clean:
	rm -f $(OBJECTS)s

