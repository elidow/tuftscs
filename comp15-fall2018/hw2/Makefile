#
#  Makefile
#  COMP15
#  Fall 2018
#
#  Makefile for the train-conductor.cpp, LinkedList and Station
#


CC = clang++
CFLAGS = -Wall -Wextra -c 
DEPS = Station.h LinkedList.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

train-conductor: train-conductor.o Station.o LinkedList.o
	$(CC) -o train-conductor train-conductor.o Station.o LinkedList.o

clean:
	rm -f *.o core* *~ train-conductor
