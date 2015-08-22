CC=gcc
CFLAGS=-c -g
all: autocomplete

autocomplete: test.o trie.o 
	$(CC) -g test.o trie.o -o  autocomplete 

test.o: test.c
	$(CC) $(CFLAGS) test.c

trie.o: trie.c
	$(CC) $(CFLAGS) trie.c


clean:
	rm *o autocomplete
