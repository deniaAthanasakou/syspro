CC = gcc -g
FILES = main.c methods.c map.c trie.c postingList.c query.c
OBJECTS = main.o methods.o map.o trie.o postingList.o query.o
OUT = minisearch
HEADERS = methods.h map.h trie.h postingList.h query.h


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
	
query.o: query.c
	$(CC) -c query.c		

clean:
	rm -f $(OBJECTS)s

