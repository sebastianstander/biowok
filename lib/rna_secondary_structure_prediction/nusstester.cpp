#include <fstream>
#include <iostream>
#include <string>
#include "nussinov.hpp"

using STR = std::string ;

void output_results( STR seq , STR fold , STR outfile ){
    std::cout << "nusstester : outputing \"" << outfile << "\" : " << fold << std::endl;
    std::ofstream dest( outfile+".txt" ) ;
    dest << seq+"\n"+fold;
    dest.close() ;
	return;
} 
int main( int argc , char*argv[] ){
    STR RNA2ndry = nussinov::run(argv[1]);
    std::cout << "In the tester : " << RNA2ndry << std::endl; 
    output_results( argv[1] , RNA2ndry , argv[2] );
    std::cout << "In the tester, after outputing : " << RNA2ndry << std::endl; 
    return 0;    
}