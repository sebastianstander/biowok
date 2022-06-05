CC = g++
CFLAGS = -Wall -g
CSTD = c++17
CSYM = ADD_FEEDBACK=1
tester: tester.o nussinov.o
	$(CC) -std=$(CSTD) -o tester tester.o nussinov.o
tester.o: tester.cpp nussinov.hpp
	$(CC) -std=$(CSTD) -c tester.cpp -D $(CSYM)
nussinov.o: nussinov.hpp nussinov.cpp