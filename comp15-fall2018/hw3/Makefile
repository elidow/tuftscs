CXX      = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra
LDFLAGS  = -g3


#
# Here are the rules!  Each rule has a "target" followed by a colon.
# After the colon, is a list of "dependencies" (also called
# "prerequisites") all on one line.  These are files that must already
# exist and be up-to-date before you can make the target.  So, the
# first rule below says that you'd like define how to make a thing
# called "peanutOlympics," and that depends on 4 .o files.  You may follow
# that line with a recipe as a series of one line commands indented
# with a tab character (yes, it must be a tab character!).  In this
# first rule, if you have all the .o files up-to-date, you make a
# peanutOlympics by running clang++ with the flags specified above giving it
# all the .o files and producing leaving the executable output in a
# file named "peanutOlympics."
# 
#
driver: driver.o CheckoutQueue.o GrocerySim.o
	${CXX} ${LDFLAGS} -o driver driver.o CheckoutQueue.o GrocerySim.o

driver.o:  driver.cpp GrocerySim.o

CheckoutQueue.o:  CheckoutQueue.cpp CheckoutQueue.h 
	${CXX} ${CXXFLAGS} -c -o CheckoutQueue.o CheckoutQueue.cpp

GrocerySim.o:  GrocerySim.cpp GrocerySim.h CheckoutQueue.cpp CheckoutQueue.h
	${CXX} ${CXXFLAGS} -c -o GrocerySim.o GrocerySim.cpp


clean:
	rm -rf driver *.o *.dSYM
