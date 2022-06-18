CC = g++
CFLAGS = -Wall -g
CSTD = -std=c++17
CSYM = -D ADD_FEEDBACK=1
tester: tester.o aligner.o
	$(CC) $(CSTD) -o aligner tester.o aligner.o
tester.o: tester.cpp aligner.hpp
	$(CC) $(CSTD) -c tester.cpp
aligner.o: aligner.hpp nussinov.cpp
	$(CC) $(CSTD) -c aligner.cpp $(CSYM)