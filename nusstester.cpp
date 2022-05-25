#include <fstream>
#include <iostream>
#include <string>
#include "nussinov.hpp"

using STR = std::string ;

void output_results( STR seq , STR fold , STR outfile ){
    std::cout << "nusstester : outputing \"" << outfile << "\" : " << fold << std::endl;

    //std::ofstream dest( outfile+".txt" ) ;
    //dest << seq+"\n"+fold;
    //dest.close() ;
	return;
} 
int main( int argc , char*argv[] ){
    //char* RNA2ndry ;
    std::cout << "nusstester : No Additional Arguement Case" << std::endl;
    const char* RNA2ndry = nussinov::run("GGGAAAUCC");
    std::cout << "In the tester : " << RNA2ndry << std::endl; 
    STR RNA2ndry_str = RNA2ndry;
    std::cout << "In the tester, try II : " << RNA2ndry_str << std::endl; 
    output_results( "GGGAAAUCC" , RNA2ndry_str , "untitled" );
    std::cout << "In the tester, after outputing : " << RNA2ndry << std::endl; 
    return 0;    
    /*switch(argc) {
        case 1 :
            std::cout << "nusstester : No Additional Arguement Case" << std::endl;
            RNA2ndry = nussinov::run("GGGAAAUCC");
            std::cout << "In the tester : " << RNA2ndry << std::endl; 
            output_results( "GGGAAAUCC" , RNA2ndry , "untitled" );
            return 0;
        case 2 :
            std::cout << "nusstester : Single Arguement Case" << std::endl;
            RNA2ndry = nussinov::run(argv[1]);
            output_results( argv[1] , RNA2ndry , "untitled" );
            return 0;
        default :
            std::cout << "nusstester : Default Case (2+ Arguements)" << std::endl;
            RNA2ndry = nussinov::run(argv[1]);
            output_results( argv[1] , RNA2ndry , argv[2] );
            return 0;
    }*/
}