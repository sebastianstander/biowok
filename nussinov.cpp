#include "feedback_stream.hpp"
#include <stdio.h>
struct NussData { 
    int recur;
    int len; 
    char* seq; 
    char* fld; 
    void* mat;
};
const inline int max( const int a , const int b ){
    return (a<=b)*b+(a>b)*a; 
}
const inline int is_coupled( char pair ) { 
    return (pair==0x01)+(pair==0x04)+(pair==0x0B)+(pair==0x0E); 
}
void format_sequence( char* formatted , const char* seq , int n ) {
    for( int c = 0 ; c < n ; c++ ) {
        formatted[c] = (seq[c]=='A')*0x05 + (seq[c]=='U')*0x01 + (seq[c]=='G')*0x02 + (seq[c]=='C')*0x03 ;
        if( !formatted[c] ) {
            formatted = nullptr ;
            return ;
        } 
        formatted[c] = (seq[c]!='A')*formatted[c] ; 
    } 
    formatted[n] = '\0'; 
    return ;
}
void build_matrix( NussData& nd , const int& min_loop_len ) {
    int(*m)[nd.len] = (int(*)[nd.len]) nd.mat ; 
	int j = 0;
    int bi = 0;
    for( int k = 1 ; k < nd.len ; k++ ) {
		for( int i = 0 ; i < nd.len-k ; i++ ){
			j = i+k;
			if( j-i >= min_loop_len ) {
				bi = 0;
				for( int t = i ; t < j ; t++ ) bi = max( bi , m[i][t]+m[t+1][j] );
				m[i][j] = max( max(m[i+1][j],m[i][j-1]) , max(m[i+1][j-1]+is_coupled((nd.seq[i]<<2)+nd.seq[j]),bi) );
			} else 
				m[i][j] = 0;
		}   
	} return ;
}
void traceback_matrix( NussData& nd , int i , int j ) {
    int(*m)[nd.len] = (int(*)[nd.len]) nd.mat ; 
    nd.recur++;
	if( i<j ) {
        fdbk("For m[");fdbk(i);fdbk("][");fdbk(j);fdbk("]\n");

        if( m[i][j]==m[i+1][j] ) {
            fdbk("\tGoing Left to m[");fdbk(i+1);fdbk("][");fdbk(j);fdbk("]\n");
            traceback_matrix( nd , i+1 , j ); 
        } else if( m[i][j]==m[i][j-1] ) {
            fdbk("\tGoing Down to m[");fdbk(i);fdbk("][");fdbk(j-1);fdbk("]\n");
            traceback_matrix( nd , i , j-1 ); 

        } else if( m[i][j]== (m[i+1][j-1]+is_coupled((nd.seq[i]<<2)+nd.seq[j])) ) {
            fdbk("\tGoing Diag to m[");fdbk(i+1);fdbk("][");fdbk(j-1);fdbk("]\n");
            fdbk("\t...Adding Fold to m[");fdbk(i);fdbk("][");fdbk(j);fdbk("]\n");
            nd.fld[i] = 41*(i>j)+40*(i<j) ;
            nd.fld[j] = 40*(i>j)+41*(i<j) ;
			traceback_matrix( nd , i+1 , j-1 );
        } else {
            fdbk("\tRetracing Bifurication from[");fdbk(i);fdbk("][");fdbk(j-1);fdbk("]\n");
            for( int k = i+1 ; k < j ; k++ ) {
				if( m[i][j]==(m[i][k]+m[k+1][j]) ) {
                    fdbk("\tBifuricating Left to[");fdbk(i);fdbk("][");fdbk(k);fdbk("]\n");
					traceback_matrix( nd , i , k ); 
                    fdbk("\tBifuricating Right to[");fdbk(k+1);fdbk("][");fdbk(j);fdbk("]\n");
					traceback_matrix( nd , k+1 , j ); 
					break; 
				}
			} 
        }
    }
    return;
}
void output_results( const char* seq , const NussData& nd , const char* oname ){
    fdbk("Outputing Results");
    const char* ext = ".txt" ; 
    int olen = 0;
    while(oname[olen]!='\0') olen++ ;
    char flnm[olen+5];
    flnm[olen+4]='\0';-
    for( int i=0 ; i<olen ; i++) flnm[i] = oname[i];
    for( int i=0 ; i<4 ; i++) flnm[olen+i] = ext[i];
    fdbk("Output_Filename : ");fdbk(flnm);
    FILE* ofl = fopen(flnm,"w");
    fwrite( nd.fld , sizeof(char) , nd.len , ofl );
	return;
} 
void test_pass( NussData& nd ){
    int(*m)[nd.len] = (int(*)[nd.len]) nd.mat ; 
    for( int i = 0 ; i < nd.len ; i++ ) {
        for( int j = 0 ; j < nd.len ; j++ ) {
            fdbk(m[i][j]); fdbk(" ");
        }
        fdbk("\n");
    }
    fdbk("\n");       
}
void nussinov ( const char* seq , const char* output_filename ) {   
    NussData nd;                                    fdbk("\n");            

    // Get the length of the c-string (without using the std or builtin libraries)
    nd.len = 0; nd.recur = 0 ;
    while (seq[nd.len] != '\0') nd.len++;           fdbk(seq);fdbk(" ");fdbk(nd.len);fdbk("\n\n");

    // Format the string literal into a compressable, c-string version;
    char formatted[sizeof(seq)];
	format_sequence( formatted , seq , nd.len );
    nd.seq = formatted ;

    // Initialize the Distance Matrix & Save a Pointer to NussData Struct;
    int mat[nd.len][nd.len]= {};
    nd.mat = mat;                                   test_pass( nd );

    // Fill in the Distance Matrix according the Nussinov's Algorithm.
    build_matrix( nd , 0 );                         test_pass( nd );
    
    // Initialize the c-string holding the RNA Secondary Structure Layout.
    char fold[nd.len];
    int c = 0; 
    while( c<=nd.len ) fold[c++]='.'; 
    fold[nd.len]='\0'; 
    nd.fld = fold ;                                 fdbk("Structure(Prior) => "); fdbk(nd.fld); fdbk("\n\n");

    // Traceback through the matrix to detemine & record the RNA Secondary Structure.
    traceback_matrix( nd , 0 , nd.len-1 );          fdbk("\n                   "); fdbk(seq); fdbk("\n");
                                                    fdbk("Structure(Post) => "); fdbk(nd.fld); fdbk("\n\n");

    fdbk("Recursive Calls = "); fdbk(nd.recur-1); fdbk(" \n\n\n");

    
    // Export the results into a custom file format.
    output_results( seq , nd , output_filename );

    return;
}
int main( int argc , char*argv[] ){
    if( argc==1 ) 
        nussinov("GGGAAAUCC","untitled");
    else if( argc==2 )
        nussinov(argv[1],"untitled");
    else 
        nussinov(argv[1],argv[2]);
    return 0;
}