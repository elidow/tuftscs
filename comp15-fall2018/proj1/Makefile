
#  Makefile
#  COMP15
#  
#
#  Makefile for the proj1: main and trie


CC = clang++
CFLAGS = -Wall -Wextra -c
DEPS = Trie.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o Trie.o
	$(CC) -o main main.o Trie.o

clean:
	rm -f *.o core* *~ main
