#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <random>
#include "../include/aligner.hpp"
#ifdef DISPLAY_ALL_RESULTS
    #ifdef DISPLAY_STRINGS
        #define display_results(i,n,a,b,c,x)\
            std::cout<<"\n\tTest "<<n<<" Results : "<<x<<"...\n"<<std::endl
    #else
        #define display_results(i,n,a,b,c,x)\
            std::cout <<\
                "\n\tTest "<<i<<" ("<<n<<" character) results : \n"\
                "\t\t• Sequence A : \""<<a<<"\"...\n" <<\
                "\t\t• Sequence B : \""<<b<<"\"...\n" <<\
                "\t\t• Result : \""<<c<<"\"...\n" <<\
                "\t\t• Duration : "<<x<<" ms (ns)...\n" <<\
            std::endl
    #endif
#else
    #define display_results(i,n,a,b,c,x)
#endif
using STR = std::string;
using namespace std::chrono;
using TIMESTAMP = std::chrono::steady_clock;
/*
class AlingerTestingSuite {
    private :   unsigned int std_test_sizes[20] = {1,5,10,20,50,100,200,500,1000,2000,5000,10000,20000};
                constexpr unsigned int timeout_threshold_ms(){ return 5000; } //5 seconds 
                std::default_random_engine randomizer ;
                std::uniform_int_distribution<char> restricted_distribution(97,100);
                std::uniform_int_distribution<char> full_distribution(33,126);
    public :
        AlingerTestingSuite()
        void run_testing_suite( UINT cutoff , UINT per_size , char iteration_scheme , 
                                bool is_local=false , bool avg_or_all=false , bool asymmetrical=true ){
            UINT average_runtime, current_runtime;

            exhaust_single_test_type( NdWn_restricted_AGToUC_charset_rand_test , 5 )
        }
        UINT exhaust_single_test_type ( UINT per_size ){   
            for( UINT i=0 ; i<20 ; i++ ) {
                average_runtime = 0 ;
                for( UINT ofsize=0 ; ofsize<per_size ; ofsize++ ){
                    average_runtime += NdWn_restricted_AGToUC_charset_rand_test( std_test_sizes[i] ) ;
                    average_runtime /= per_size ;
                }
                std::cout << "\t\"NdWn_restricted_AGToUC_charset_rand_test\"-even-count:"<<i<<" averages : \n" <<
                    average_runtime << " ns ("<< average_runtime/1000 <<" ms)...\n" <<
                std::endl ;
            }
        }
        UINT NdWn_restricted_AGToUC_charset_rand_test( UINT n , UINT m = 0 ){   
            m = (!m)?n:m;
            char bufferA[n]; char* sqA = bufferA ;
            char bufferB[m]; char* sqB = bufferB ;
            build_random_string(sqA,std_test_sizes[i],true);
            build_random_string(sqB,std_test_sizes[i],true);
            auto prior = TIMESTAMP::now();
            Aligner{ sqA , sqB , true };
            auto post = TIMESTAMP::now();
            display_results(n,m,current_runtime);
            return duration_cast<nanoseconds>(post-prior).count();
        }
        void full_utf8_charset_rand_test( UINT i , ){

        }
        
        two_empty_sequences_test
        empty_first_sequence_test
        empty_second_sequence_test

        assign_custom_score_model( ScoreModel sm ) ;
        random_sequence_test( bool restrict_to_ACGT ) 
        all_matched_random_character_test()
        all_mismatched_random_sequence_test()
    private :
        inline char translate_to_AGCT( char val ){ 
            return (val==97)*(65)+(val==98)*(67)+(val==99)*(71)+(val==100)*(84);
        }
        void build_random_string( char* buffer , const int charc , const bool is_resticted ){
            for( int i = 0 ; i < charc ; i++ )
                buffer[i] = (is_resticted)? 
                    translate_to_AGCT( char(restricted_distribution(randomizer)) ) 
                    :
                    full_distribution(randomizer) ;
        }
}
*/
int main(int argc,char* argv[]){        std::cout<<"<TEST>::Can enter main function\n";
    if(argc>2) {
        STR seqA = argv[1];             std::cout<<"<TEST>::Assigned argv[1]("<<argv[1]<<") to a STR seqA("<<seqA<<")\n";
        STR seqB = argv[2];             std::cout<<"<TEST>::Assigned argv[2]("<<argv[2]<<") to a STR seqB("<<seqB<<")\n";
        auto prior = TIMESTAMP::now();
        Align::Aligner AL{ argv[1] , argv[2] , false };
        auto post = TIMESTAMP::now();   std::cout << "<TEST>::In the tester : \n " << "AL.m_AL" << "\n- elapsed : " 
                                                    << duration_cast<nanoseconds>(post-prior).count() << " ns ("
                                                    << duration_cast<milliseconds>(post-prior).count() << " ms) \n";
    }
    return 0;  
}