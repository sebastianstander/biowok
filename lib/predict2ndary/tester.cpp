//#include <fstream>
//#include <string>
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
    std::cout<<"I am able to do the basic fucking tasks I'm asked to.\n";
    char* RNA2ndry = nussinov::predict("GGGAAAUCC");
    //fdbk("In the tester : ");fdbk(RNA2ndry);fdbk("\n"); 
    nussinov::cpp_echo();
    //output_results( argv[1] , RNA2ndry , argv[2] );
    //fdbk("In the tester, after outputing : ");fdbk(RNA2ndry);fdbk("\n"); 
    return 0;    
}