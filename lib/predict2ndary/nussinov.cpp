/**
 * @file nuss.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-02
 * 
 */
#include "nussinov.hpp"
char* nussinov::compress_sequence( char* formatted , const char* seq , int n ) {
    char current;
    for( int b = 0 ; b < n/4 ; b++ ){ 
        current = 0b00000000;
        for( int c = 0 ; c < 4 ; c++ )
            int        
            current = ((seq[(b*4)+c]=='A')*0x05 + (seq[b+c]=='U')*0x01 + (seq[b+c]=='G')*0x02 + (seq[b+c]=='C')*0x03 ) ;
            if(!current) {
                formatted = nullptr ;
                return formatted ;
            }
            current = (seq[c]!='A')*current;
            formatted[b] = formatted[b]+(current<<(c*2)); 

        formatted[c] = (seq[c]=='A')*0x05 + (seq[c]=='U')*0x01 + (seq[c]=='G')*0x02 + (seq[c]=='C')*0x03 ;
    } 
    formatted[n] = '\0'; 
    return formatted;
}
void nussinov::build_matrix( NussData& nd , const int& min_loop_len ) {
	int j, bi = 0;
    for( int k = 1 ; k < nd.len ; k++ ) {
		for( int i = 0 ; i < nd.len-k ; i++ ){
			j = i+k;
			if( j-i >= min_loop_len ) {
				bi = 0;
				for( int t = i ; t < j ; t++ ) bi = max( bi , nd.mat[i][t]+nd.mat[t+1][j] );
				nd.mat[i][j] = max( max(nd.mat[i+1][j],nd.mat[i][j-1]) , max(nd.mat[i+1][j-1]+is_coupled((nd.seq[i]<<2)+nd.seq[j]),bi) );
			} else 
				nd.mat[i][j] = 0;
		}   
	} return ;
}
void nussinov::traceback_matrix( NussData& nd , int i , int j ) {
    nd.recur++;
	if( i<j ) {
        fdbk("For nd.mat[");fdbk(i);fdbk("][");fdbk(j);fdbk("]\n");

        if( nd.mat[i][j]==nd.mat[i+1][j] ) {
            fdbk("\tGoing Left to nd.mat[");fdbk(i+1);fdbk("][");fdbk(j);fdbk("]\n");
            traceback_matrix( nd , i+1 , j ); 
        } else if( nd.mat[i][j]==nd.mat[i][j-1] ) {
            fdbk("\tGoing Down to nd.mat[");fdbk(i);fdbk("][");fdbk(j-1);fdbk("]\n");
            traceback_matrix( nd , i , j-1 ); 

        } else if( nd.mat[i][j]== (nd.mat[i+1][j-1]+is_coupled((nd.seq[i]<<2)+nd.seq[j])) ) {
            fdbk("\tGoing Diag to nd.mat[");fdbk(i+1);fdbk("][");fdbk(j-1);fdbk("]\n");
            fdbk("\t...Adding Fold to nd.mat[");fdbk(i);fdbk("][");fdbk(j);fdbk("]\n");
            nd.fld[i] = 41*(i>j)+40*(i<j) ;
            nd.fld[j] = 40*(i>j)+41*(i<j) ;
			traceback_matrix( nd , i+1 , j-1 );
        } else {
            fdbk("\tRetracing Bifurication frond.mat[");fdbk(i);fdbk("][");fdbk(j-1);fdbk("]\n");
            for( int k = i+1 ; k < j ; k++ ) {
				if( nd.mat[i][j]==(nd.mat[i][k]+nd.mat[k+1][j]) ) {
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
char* nussinov::run( const char* seq ) {   
    NussData nd;                                    fdbk("\n");            

    // Get the length of the c-string (without using the std or builtin libraries)
    nd.len = 0; nd.recur = 0 ;
    while (seq[nd.len] != '\0') nd.len++;           
                                                    fdbk(seq);fdbk(" ");fdbk(nd.len);fdbk("\n\n");

    // Format the string literal into a compressable, c-string version;
    char formatted[nd.len];
	format_sequence( formatted , seq , nd.len );
    nd.seq = formatted ;

    // Initialize the Distance Matrix & Save a Pointer to NussData Struct;
    int mat[nd.len*nd.len] = {};
    nd.mat = mat;                                   //test_pass( nd );

    // Fill in the Distance Matrix according the Nussinov's Algorithm.
    build_matrix( nd , 0 );                         //test_pass( nd );
    
    // Initialize the c-string holding the RNA Secondary Structure Layout.
    char fold[nd.len+1];
    int c = 0; 
    while( c<=nd.len ) fold[c++]='.'; 
    fold[nd.len]='\0'; 
    nd.fld = fold ;                                 fdbk("Structure(Prior) => "); fdbk(nd.fld); fdbk("\n\n");

    // Traceback through the matrix to detemine & record the RNA Secondary Structure.
    traceback_matrix( nd , 0 , nd.len-1 );          fdbk("\n                   "); fdbk(seq); fdbk("\n");
                                                    fdbk("Structure(Post) => "); fdbk(nd.fld); fdbk("\n\n");

    fdbk("Recursive Calls = "); fdbk(nd.recur-1); fdbk(" \n\n\n");
    return nd.fld;
}
