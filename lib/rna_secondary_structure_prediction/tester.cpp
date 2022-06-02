//#include <fstream>
#include <string>
#include <iostream>
//#include "nussinov.hpp"

using STR = std::string ;

void output_results( STR seq , STR fold , STR outfile ){
    //fdbk("nusstester : outputing \"");fdbk(outfile);fdbk("\" : ");fdbk(fold);
    //std::ofstream dest( outfile+".txt" ) ;
    dest << seq+"\n"+fold;
    dest.close() ;
	return;
} 
int main( int argc , char*argv[] ){
    //STR RNA2ndry = nussinov::run(argv[1]);
    const char* seq = "GGGAAAUCC";
    std::cout<<"testing compile"<<std::endl;
    //STR RNA2ndry = nussinov::run(seq);
    //fdbk("In the tester : ");fdbk(RNA2ndry); 
    //output_results( argv[1] , RNA2ndry , argv[2] );
    //output_results( seq , RNA2ndry , "out.txt" );
    //fdbk("In the tester, after outputing : ");fdbk(RNA2ndry); 
    return 0;    
}