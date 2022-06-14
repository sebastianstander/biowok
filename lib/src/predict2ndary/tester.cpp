#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include "nussinov.hpp"
/**
 * - Remove File Output (Delegate to JSONConverter)
 * - Add Randomized Sequence Generator()
 * - Migrate Formatting Sequence outside namespace
 * - Add 2 versions (formatted & unformatted)
 * - Command Line Designations( -u n m ) => conduct n tests, each of m length.
 * - Command Line Designations( -a n ) => conduct n tests from lengths 1 to n.
 * - Command Line Designations( -s n q ) => conduct n tests of the sequence q.
 * - Command Line Defaults( x ) => conduct 1 Length 10 test.
 */
using STR = std::string;
using namespace std::chrono;
using TIMESTAMP = std::chrono::steady_clock;

void test(int n,int m,STR& q,bool are_differing){
    do{
        char RNA2ndry[seq.size()]; 
        RNA2ndry[seq.size()] = '\0';
        if(!m) {
            nussinov::predict(q,RNA2ndry);
        } else if(are_differing) {
            q = sequence_generation::make(n);
            nussinov::predict(q,RNA2ndry);
        } else {
            q = sequence_generation::make(m);
            nussinov::predict(q,RNA2ndry);
        }
    }while(--n);
}
int main(int argc,char*argv[]){
    /*
    if( argv[1][0] == '-' ){
        switch( arg[1][1] ){
            case 'u' : test(argv[1],argv[2],""); return 0;
            case 'a' : test(argv[1],-1,""); n = 1 ; return 0;
            case 's' : test(argv[1],0,arg[2]); n = 1 ; return 0;
            default : test(argv[1],0,arg[2]); return 0;
        };
    } else 
        test(1,10,""); 
    return 0;*/

    STR seq = argv[1];
    char RNA2ndry[seq.size()]; RNA2ndry[seq.size()] = '\0';
    auto prior = TIMESTAMP::now();
    nussinov::predict(argv[1],RNA2ndry);
    auto post = TIMESTAMP::now();
    std::cout << "In the tester :\n\t- \"" <<argv[1]<<"\n\t- \"" <<RNA2ndry<< "\"\n\t- length, " << seq.size() << "\n\t- elapsed : " 
        << duration_cast<nanoseconds>(post-prior).count() << " ns (";   
        << duration_cast<milliseconds>(post-prior).count() << " ms) \n";   
    return 0;    
}

