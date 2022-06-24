#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include "../include/aligner.hpp"

using STR = std::string;
using namespace std::chrono;
using TIMESTAMP = std::chrono::steady_clock;

int main(int argc,char* argv[]){        std::cout<<"<TEST>::Can enter main function\n";
    if(argc>2) {
        STR seqA = argv[1];             std::cout<<"<TEST>::Assigned argv[1]("<<argv[1]<<") to a STR seqA("<<seqA<<")\n";
        STR seqB = argv[2];             std::cout<<"<TEST>::Assigned argv[2]("<<argv[2]<<") to a STR seqB("<<seqB<<")\n";
        auto prior = TIMESTAMP::now();
        STR alignment = aligner::align(argv[1],argv[2],false);   std::cout<<"exiting aligner\n";
        auto post = TIMESTAMP::now();
        std::cout << "<TEST>::In the tester : \n" <<alignment<< "\n- elapsed : " 
                  << duration_cast<nanoseconds>(post-prior).count() << " ns ("
                  << duration_cast<milliseconds>(post-prior).count() << " ms) \n";
    }
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