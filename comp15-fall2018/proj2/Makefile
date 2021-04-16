
#  Makefile
#  COMP15
#  
#  Makefile for Proj2: 


CXX      = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra -O2
LDFLAGS  = -g3


gerp: FSTreeTraversal.o FSTree.o DirNode.o Index.o LinkedList.o DataType.o StringProcessing.o
	${CXX} ${LDFLAGS} -o gerp FSTreeTraversal.o FSTree.o DirNode.o Index.o LinkedList.o DataType.o StringProcessing.o

FSTreeTraversal.o:  FSTreeTraversal.cpp FSTree.o DirNode.o Index.o StringProcessing.o

Index.o: Index.cpp Index.h DirNode.h LinkedList.h LinkedList.cpp DataType.h DataType.cpp StringProcessing.h StringProcessing.cpp
	${CXX} ${CXXFLAGS} -c -o Index.o Index.cpp

LinkedList.o:  LinkedList.cpp LinkedList.h
	${CXX} ${CXXFLAGS} -c -o LinkedList.o LinkedList.cpp

DataType.o:  DataType.cpp DataType.h
	${CXX} ${CXXFLAGS} -c -o DataType.o DataType.cpp

StringProcessing.o:  StringProcessing.cpp StringProcessing.h
	${CXX} ${CXXFLAGS} -c -o StringProcessing.o StringProcessing.cpp

clean:
	rm -rf gerp *.o *.dSYM
