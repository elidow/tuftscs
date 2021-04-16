
#  Makefile
#  COMP15
#  
#
#  Makefile for hw5: 


CXX      = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra
LDFLAGS  = -g3


sixdegrees: main.o SixDegrees.o Graph.o Actor.o LinkedList.o Stack.o Queue.o
	${CXX} ${LDFLAGS} -o sixdegrees main.o SixDegrees.o Graph.o Actor.o LinkedList.o Stack.o Queue.o

test-graph: test-graph.o SixDegrees.o Graph.o Actor.o LinkedList.o Stack.o Queue.o
	${CXX} ${LDFLAGS} -o test-graph test-graph.o SixDegrees.o Graph.o Actor.o LinkedList.o Stack.o Queue.o

test-graph.o: test-graph.cpp SixDegrees.o

main.o:  main.cpp SixDegrees.o

SixDegrees.o: SixDegrees.cpp SixDegrees.h Actor.cpp Actor.h Graph.h Graph.cpp LinkedList.h LinkedList.cpp
	${CXX} ${CXXFLAGS} -c -o SixDegrees.o SixDegrees.cpp

Graph.o:  Graph.cpp Graph.h Actor.cpp Actor.h Stack.cpp Stack.h Queue.cpp Queue.h
	${CXX} ${CXXFLAGS} -c -o Graph.o Graph.cpp

Actor.o:  Actor.cpp Actor.h LinkedList.cpp LinkedList.h
	${CXX} ${CXXFLAGS} -c -o Actor.o Actor.cpp

LinkedList.o:  LinkedList.cpp LinkedList.h
	${CXX} ${CXXFLAGS} -c -o LinkedList.o LinkedList.cpp


clean:
	rm -rf sixdegrees *.o *.dSYM
