#ifdef ADD_FEEDBACK
    #include "feedback_stream.hpp"
    /*#define test_pass(nd)\
        int(*m)[nd.len]=(int(*)[nd.len])nd.mat;\
        for(int i=0;i<nd.len;i++){\
            for(int j=0;j<nd.len;j++){ fdbk(m[i][j]); fdbk(" ");}\
            fdbk("\n");\
        }fdbk("\n");     
#else
    #define test_pass(nd)*/
#endif

struct NussData { 
    int recur;
    int len; 
    char* seq; 
    char* fld; 
    void* mat;
};
namespace nussinov {
    const inline int max( const int a , const int b ){ return (a<=b)*b+(a>b)*a; }
    const inline int is_coupled( char pair ) { return (pair==0x01)+(pair==0x04)+(pair==0x0B)+(pair==0x0E); }
    char* format_sequence( char* formatted , const char* seq , int n );
    void build_matrix( NussData& nd , const int& min_loop_len );
    void traceback_matrix( NussData& nd , int i , int j );
    char* run( const char* seq );
};