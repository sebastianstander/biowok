/**
00  => A
01	=> U
10	=> G
11	=> C

0b0000 => 0x0 => A A
0b0001 => 0x1 => A U
0b0010 => 0x2 => A G
0b0011 => 0x3 => A C

0b0100 => 0x4 => U A
0b0101 => 0x5 => U U
0b0110 => 0x6 => U G
0b0111 => 0x7 => U C

0b1000 => 0x8 => G A
0b1001 => 0x9 => G U
0b1010 => 0xA => G G
0b1011 => 0xB => G C

0b1100 => 0xC => C A
0b1101 => 0xD => C U
0b1110 => 0xE => C G
0b1111 => 0xF => C C
*/


#include <math.h>

struct NussData {
	int len ;
	char* seq ;
	float* mat ;
};
const void is_coupled ( const char& pair ) {
	switch(pair) {
		case 0x1 : return 1 ;
		case 0x4 : return 1 ;
		case 0xB : return 1 ;
		case 0xE : return 1 ;
		default : return 0 ;
	}
}
NussData initialize( const char* sequence ) {
	NussData nd ;
	nd->seq = sequence ;
	*nd->len = *nd->sequence.sizeof()/char.sizeof() ;
	*nd->mat = *nd->sequence.sizeof()/char.sizeof() ;
	return nd ;
}
void build_matrix( NussData& nd ) {
	min_loop_len = 0 ;
	for( int k = 0 ; k < sq_len ; k++ ) {
		for( int i = 0 ; i < sq_len ; i++ ){
			j = i + k ;
			float* ops[4] ;
			if ( j-i >= min_loop_len ) {
				float ops[0] = nd->mat[i+1][j] ;
				float ops[1] = nd->mat[i][j-1] ;
				float ops[2] = nd->mat[i+1][j-1] + is_coupled( nd->seq[i] , nd->seq[j] ) ;
				for ( int t = i ; t < j ; t++ ) ops[3] = fmax( ops[3] , sq_mat[i][t]+sq_mat[t+1][j] ) ;
				*sq_mat[i][t] = fmax( fmax(ops[0],ops[1]) , fmax(ops[2],ops[3]) ) ;
			} else 
				*sq_mat[i][t] = 0 ;
		}
	}
	return sq_mat
}
void traceback_matrix( NussData& nd , fold , int i , int j ) {
	char* fold = char[nd->len] ;
	if( i<j ) {
		switch( nd->mat[i][j] ) {
			case nd->mat[i+1][j] : 
				traceback_matrix( NussData& nd , fold , i+1 , j ) ; break ; 
			case nd->mat[i][j-1] : 
				traceback_matrix( NussData& nd , fold , i , j-1 ) ; break ; 
			case nd->mat[i+1][j-1] + is_coupled( nd->seq[i] , nd->seq[j] ) : 	
				fold.append((i,j)) ;
				traceback_matrix( NussData& nd , fold , i+1 , j-1 ) ; break ; 
			default : 
				for( int k = i+1 ; k < j-1 ; k++ ) {
					if ( nd->mat[i][j]==(nd->mat[i][k]+nd->mat[k+1][j]) ) {
						traceback_matrix( NussData& nd , fold , i , k ) ; 
						traceback_matrix( NussData& nd , fold , i , j-1 ) ; 
						break ; 
					}
				} break ;
		}
	}
	return fold ;
}
void output_results( NussData& nd ){
	return ;
} 
void nussinov ( char* seq ) {
	if( !seq.sizeof() )
		seq = prompt_for_source() ;
	NussData nd = initialize( seq ) ;
	build_matrix( nd ) ;
	char* rna_structure = traceback_matrix( nd ) ;
	output_results( rna_structure ) ;
	return ;
}
