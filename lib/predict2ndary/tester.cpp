//#include <fstream>
//#include <string>
#include <iostream>
#include "nussinov.hpp"

//using STR = std::string ;

/*void output_results(STR seq,STR fold,STR outfile){
    fdbk("nusstester : outputing \"");fdbk(outfile);fdbk("\" : ");fdbk(fold);
    std::ofstream dest(outfile+".txt");
    dest << seq+"\n"+fold;
    dest.close();
	return;
} */
int main(int argc,char*argv[]){
    char* RNA2ndry = nussinov::predict("GGGAAAUCC");
    std::cout << "In the tester : " <<RNA2ndry<< "\n"; 
    //output_results( argv[1] , RNA2ndry , argv[2] );
    //fdbk("In the tester, after outputing : ");fdbk(RNA2ndry);fdbk("\n"); 
    return 0;    
}