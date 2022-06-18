#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include "aligner.hpp"

int main(){
    STR seqA = argv[1];
    STR seqB = argv[2];
    auto prior = TIMESTAMP::now();
    STR alignment = aligner::needleman_wuncsh(argv[1],argv[2]);
    auto post = TIMESTAMP::now();
    std::cout << "In the tester :\n\t- \"" <<argv[1]<<"\n\t- \"" <<RNA2ndry<< "\"\n\t- length, " << seq.size() << "\n\t- elapsed : " 
        << duration_cast<nanoseconds>(post-prior).count() << " ns (";   
        << duration_cast<milliseconds>(post-prior).count() << " ms) \n";   
    return 0;  
}

/**
O(n)
O(m)

matrix(nm) 
alignment_string > 1.5*((n*(n>=m))+(m*(n<m)))
alignment_stack 


store gap information in the build matrix (0 row and column)



*/