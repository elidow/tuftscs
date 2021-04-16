CC = clang++
CFLAGS = -Wall -Wextra -c
DEPS = Pirate.h ArrayList.h PirateMates.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hookbook: hookbook.o Pirate.o ArrayList.o
	$(CC) -o hookbook hookbook.o Pirate.o ArrayList.o

clean:
	rm -f *.o core* *~ hookbook
