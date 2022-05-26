#include "nussinov.hpp"

char* nussinov::format_sequence( char* formatted , const char* seq , int n ) {
    for( int c = 0 ; c < n ; c++ ) {
        formatted[c] = (seq[c]=='A')*0x05 + (seq[c]=='U')*0x01 + (seq[c]=='G')*0x02 + (seq[c]=='C')*0x03 ;
        if( formatted[c] == 0x00 ) {
            formatted = nullptr ;
            return formatted ;
        } 
        formatted[c] = (seq[c]!='A')*formatted[c] ; 
    } 
    formatted[n] = '\0'; 
    return formatted;
}
void nussinov::build_matrix( NussData& nd , const int& min_loop_len ) {
    int(*m)[nd.len] = (int(*)[nd.len]) nd.mat ; 
	int j, bi = 0;
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
void nussinov::traceback_matrix( NussData& nd , int i , int j ) {
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
    int mat[nd.len][nd.len] = {};
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
