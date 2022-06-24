CC = g++
CFLAGS = -Wall -g
CSTD = -std=c++17
CSYM = -D ADD_FEEDBACK=1
tester: tester.o nussinov.o
	$(CC) $(CSTD) -o tester tester.o nussinov.o
tester.o: tester.cpp nussinov.hpp
	$(CC) $(CSTD) -c tester.cpp
nussinov.o: nussinov.cpp nussinov.hpp 
	$(CC) $(CSTD) -c nussinov.cpp $(CSYM)