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
    const char* run( const char* seq );
};