#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include "../include/upgma.hpp"
using STR = std::string;
using namespace std::chrono;
using TIMESTAMP = std::chrono::steady_clock;
int main(){
    char* seqs = "GTTAAACATCTCCTCGTGAAACAACATGACGTTAAACATGTGGACGCACAGATGTCGCCTGTCTTACTGGCATGA";
    unsigned int n = 15;
    unsigned int k = 5;
    auto prior = TIMESTAMP::now();
    PhylogeneticTree tr{ n , k , seqs };
    auto post = TIMESTAMP::now();
    std::cout << "In the tester :\n\t- \"" << seqs <<"\n\t- assigned sequence length, \"" << n << "\"\n\t- number of sequences, \"" << k << "\"\n\t- elapsed : " 
        << duration_cast<nanoseconds>(post-prior).count() << " ns ("  
        << duration_cast<milliseconds>(post-prior).count() << " ms) \n";   
    return 0;
}