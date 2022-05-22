#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <stack>

using namespace std ;

#ifdef VERBOSE
	#define VP(...) fprintf ( stderr , __VA_ARGS__ );
#else
	#define VP(...);
#endif

/* Modifies the constants used in the scoring model of both algorithims. */
enum scoring_model {
	MISMATCH = -1	,
	MATCH = 2 		,
	GAP_PENALTY = -2
} ;

/* Holds pointers to both sequences strings and the similiatry matrix data structure. */
typedef struct similarity_matrix {
	string * seqA ;
	string * seqB ;
	int * matrix ;
} similarity_matrix ;

/* Returns the score for a given entry */
int score_entry ( similarity_matrix * SM , int row , int col ) {
	string A = SM->seqA->substr(col-1,1) ;	
	string B = SM->seqB->substr(row-1,1) ;				VP (".SSME.$............matching A[%d] to B[%d] ( %s & %s )...\n", row-1 , col -1 , A.c_str() , B.c_str() );	
	if ( A == B ) { 									VP (".SSME.$............match found ( A[%d] = %s,  B[%d] = %s) ...\n", row , A.c_str() , col , B.c_str() );	
		return MATCH ; 
	} 													VP (".SSME.$............mismatch found ( A[%d] = %s,  B[%d] = %s) ...\n", row , A.c_str() , col , B.c_str()  );		
	return MISMATCH ;
}

/* Returns the result the actual functions of each of the algorithim to a given entry */
int calculate_similarity_matrix_entry ( similarity_matrix * SM , int row , int col , int width ) { 
	if ( row == 0 && col == 0 ) 	{ 					VP (".CSME.$............intial entry case found : F(%d,%d) = %d ...\n", row , col , 0 );
		return 0 ;										// case (0,0) : [0,0] = 0
	} else if ( row == 0 ) 			{ 					VP (".CSME.$............leftmost entry case found :  F(%d,%d) => %d ...\n", row , col , (GAP_PENALTY * col) );
		return (GAP_PENALTY * col) ; 					// case (0,j) : [0,j] = -d*j
	} else if ( col == 0 )			{ 					VP (".CSME.$............uppermost entry case found : F(%d,%d) => %d ...\n", row , col , (GAP_PENALTY * row)  );
		return (GAP_PENALTY * row) ; 					// case (i,0) : [i,0] = -d*i
	} else {											VP (".CSME.$............general entry case found : F(%d,%d) => ...\n", row , col );			
		// case (i,j) : [i,j] = max { [i-1,j-1] + score_entry(i,j) || [i-1,j] - GAP_PENALTY || [i,j-1] - GAP_PENALTY }	
		int entry_value = SM->matrix[((row-1)*width)+(col-1)] + score_entry ( SM , row , col ) ;	VP (".CSME.$............assuming diagonal : F(%d,%d) = %d...\n", row-1 , col-1 , entry_value );	
		if ( entry_value < ( SM->matrix[(row*width)+(col-1)] + GAP_PENALTY) ) { 				
			entry_value = (SM->matrix[(row*width)+(col-1)] + GAP_PENALTY) ; 						VP (".CSME.$............found better horizontal gap case : F(%d,%d) = %d ...\n", row , col-1 , entry_value );
		}
		if ( entry_value < (SM->matrix[((row-1)*width)+(col)] + GAP_PENALTY) ) { 
			entry_value = (SM->matrix[((row-1)*width)+(col)] + GAP_PENALTY) ;						VP (".CSME.$............found better vertical gap case : F(%d,%d) = %d ...\n", row-1 , col , entry_value );
		}
		return entry_value ;
	}	
}

/* Calls for each entry in similarity matrix, contained in a struct at the highest level, to be filled or localized in 
the case of smith_waterman while also recording the max indices (or index) */
int build_similarity_matrix ( similarity_matrix * SM, stack<int> * XS , bool local ) {
	int max_index = 0 ;	int max = -1 ;						VP (".BSIM.$.........establishing similarity matrix of size \"%lu\"...\n", ((SM->seqA->size()+1)*(SM->seqB->size()+1)) );
	int width = SM->seqA->size()+1 ;						VP (".BSIM.$.........width of similarity matrix = \"%d\"...\n", width );
	int count = width * (SM->seqB->size()+1) ;				VP (".BSIM.$.........confirmed size of similarity = \"%d\"...\n", count );
	stack<int> TALLY ;
	for (int entry = 0 ; entry < count ; entry ++) {		VP (".BSIM.$.........for entry \"%d\" ( F(%d,%d) )...\n", entry , entry/width , entry%width );
		int entry_value = calculate_similarity_matrix_entry ( SM , entry/width , entry%width , width ) ;
		if ( local ) {										VP (".BSIM.$...............localizing negative entry[%d] = %d...\n", entry , entry_value );
			if ( entry_value < 0 ) {
				entry_value = 0 ; 		 					VP (".BSIM.$...............to entry[%d] = %d...\n", entry , entry_value );
			}	
		} 													
		if ( entry_value > -1 && max < entry_value ) {		VP (".BSIM.$...............found new max entry at [%d]...\n", entry );				
			if ( ! XS->empty() ) {
				while ( ! XS->empty() && TALLY.top() == max ) {	VP (".BSIM.$...............discarding old entries on stack ( [%d] = %d )...\n", XS->top() , TALLY.top() ) ;														
					TALLY.pop ( ) ;
					XS->pop ( ) ;	
				}											VP (".BSIM.$...............all old entries handled...\n" );
			}	
			TALLY.push ( entry_value ) ;					VP (".BSIM.$...............placed new value (%d) stacked in tally...\n", entry_value ); 
			XS->push ( entry ) ;							VP (".BSIM.$...............placed new entry [%d] stacked on stack...\n", entry ); 
			max = entry_value ;								VP (".BSIM.$...............max now equals = %d...\n", max );	
			max_index = entry ;								VP (".BSIM.$...............max_entry now equals = %d...\n", max_index );	
														
		} else if ( entry_value > -1 && max == entry_value ) {	VP (".BSIM.$...............another max entry found at [%d] ...\n", entry_value );
			TALLY.push ( entry_value ) ;					VP (".BSIM.$...............placed new value (%d) stacked in tally...\n", entry_value ); 	
 			XS->push ( entry ) ;							VP (".BSIM.$...............placed new entry [%d] stacked on stack...\n", entry ); 
 			max_index = entry ;								VP (".BSIM.$...............max_entry now equals = %d...\n", max_index );	
		}													VP (".BSIM.$............established F(%d,%d) = %d ...\n", entry/width , entry%width , entry_value );
		SM->matrix[entry] = entry_value ;
	} 														VP (".BSIM.$.........highest score found (%d) at SM[%d] ( F(%d,%d) )...\n", max , max_index , max_index/width , max_index%width );
	return max ;
} 

/* Conducts the traceback funtion of for both sequence alignment algorithims recursively to make use of multiple valid branching cases */
void traceback_similarity_matrix ( similarity_matrix * SM , stack<string> * ALs , string A , string B , bool local , int width , int row , int col , int total ) {
	VP (".TRSM.$.........Tracing (%d,%d)...\n", row , col );	
	VP (".TRSM.$.........current position = (%d)...\n", SM->matrix [ ((row)*width)+(col)] );	
	if ( row == 0 && col == 0 ) { 									
		A += "." ; A += B ; A += "." ; A += to_string(total) ; 							VP (".TRSM.$............global base case found, results = \"%s\"...\n", A.c_str() );	
		if ( A.length() > 3 ) ALs->push ( A ) ; return ; 
	}
	if ( local ) {													
		if ( row == 0 || col == 0 ) { 
			A += "." ; A += B ; A += "." ; A += to_string(total) ; 						VP (".TRSM.$............local base case found, results = \"%s\"...\n", A.c_str() );	
			if ( A.length() > 3 ) ALs->push ( A ) ; return ; 
		} else if ( (SM->matrix [ ((row)*width)+(col)] + score_entry ( SM , row , col )) == 0 ) {
			A += "." ; A += B ; A += "." ; A += to_string(total) ; 						VP (".TRSM.$............local base case found, results = \"%s\"...\n", A.c_str() );	
			if ( A.length() > 3 ) ALs->push ( A ) ; return ; 
		}
	}
	int current = SM->matrix [ ((row)*width)+(col)] ;
	int routes_taken = 0 ;
	if ( row > 0 && col > 0 && current == (SM->matrix [ ((row-1)*width)+(col-1)] + score_entry ( SM , row , col ) ) ) { 									
		A += SM->seqA->substr(col-1,1) ;	
		B += SM->seqB->substr(row-1,1) ;												VP (".TRSM.$............diagonal case found, results = \n\t\t%s\n\t\t%s\n", A.c_str() , B.c_str() );	
		traceback_similarity_matrix ( SM , ALs , A , B , local , width , row-1 , col-1 ,total ) ; 
		routes_taken ++ ;
		total += (SM->matrix [ ((row-1)*width)+(col-1)] + score_entry ( SM , row , col )) ;
	} if ( row > 0 && current == (SM->matrix [ ( row *width)+(col-1)] + GAP_PENALTY) ) { 
		if ( routes_taken ) { A.erase ( A.end()-1 ) ; B.erase ( B.end()-1 ) ; }
		A += SM->seqA->substr(col-1,1) ;
		B += "-" ;																		VP (".TRSM.$............horizontal case found, results = \n\t\t%s\n\t\t%s\n", A.c_str() , B.c_str() );	
		traceback_similarity_matrix ( SM , ALs , A , B , local , width ,  row  , col-1 , total ) ; 
		routes_taken ++ ;
		total += (SM->matrix [ ( row *width)+(col-1)] + GAP_PENALTY) ;
	} if ( current == (SM->matrix [ ((row-1)*width)+( col )] + GAP_PENALTY) ) { 
		if ( routes_taken ) { A.erase ( A.end()-1 ) ; B.erase ( B.end()-1 ) ; }
		A += "-" ;		
		B += SM->seqB->substr(row-1,1) ;												VP (".TRSM.$............vertical case found, results = \n\t\t%s\n\t\t%s\n", A.c_str() , B.c_str() );	
		traceback_similarity_matrix ( SM , ALs , A , B , local , width , row-1 ,  col , total ) ; 
		total += (SM->matrix [ ((row-1)*width)+( col )] + GAP_PENALTY) ; ;
	} return ;
}

/* Parses the optimal alignments as their placed on the string stack, reversing and tokenizing them */
void parse_alignment ( FILE * output , stack<string> * ALs ) {
	string alignment = ALs->top() ;  													VP (".OUTP.$............retrieving alignment from stack \"%s\"...\n", alignment.c_str() ) ;
	reverse(alignment.begin(), alignment.end()) ;										VP (".OUTP.$............reversing alignment \"%s\"...\n", alignment.c_str() ) ;
	size_t A_scope = alignment.find(".") ; int scopeA = static_cast<int>(A_scope);		VP (".OUTP.$............establishing scopeA = %d...\n", scopeA ) ;
	size_t B_scope = alignment.rfind(".") ; int scopeB = static_cast<int>(B_scope);		VP (".OUTP.$............establishing scopeB = %d...\n", scopeB ) ;
	string A = alignment.substr (scopeB+1,(scopeB-1)-scopeA) ;							VP (".OUTP.$............portioning out A \"%s\"...\n", A.c_str() ) ;
	string B = alignment.substr (scopeA+1,(scopeB-1)-scopeA) ;							VP (".OUTP.$............portioning out B \"%s\"...\n", B.c_str() ) ;
	fprintf( output , "%s\n", A.c_str()) ;	
	fprintf( output , "%s", B.c_str()) ;	
}

/* Converts the various data values and structures into strings in a text file */
void output_results ( similarity_matrix * SM , stack<string> * ALs , int width , int entry_count , int optimal_score , char * output_filename ) {
	
	FILE * output = fopen ( output_filename , "w") ;									VP (".OUTP.$.........opening \"output.txt\" file...\n") ;
	
	fprintf( output , "File Name: aligner.cpp\n" ) ;
	
	fprintf( output , "\n2.in:\n%s\n%s\n", SM->seqA->c_str() , SM->seqB->c_str() ) ;
	
	fprintf( output , "\n2.o1:\n%d\n", optimal_score ) ;
	
	fprintf( output , "\n2.o2:\n") ;													VP (".OUTP.$.........writing 2.o2...\n") ;

	/* This paticular implementation unfortunately works with the transpose of 
	the matrix, the result as an oversight in inital design.This loop converts 
	the matrix to it's form designated in the assignment criteria */	
	int col_converter = 0 ; int row_converter = 0;										VP (".OUTP.$............width of sequence = %d...\new" , width ) ;
	for ( int entry = 0 ; entry < entry_count ; entry ++ ) {							VP (".OUTP.$............for entry %d (%d) ( F(%d,%d)=%d )...\n" , (row_converter + col_converter) , entry , entry/width , entry%width , SM->matrix[entry] ) ;
		fprintf( output , "%d ", SM->matrix[entry ] ) ;
		col_converter += width ;
		if ((entry+1) % width == 0) { 
			fprintf( output , "\n" ) ;													VP (".OUTP.$............starting new line (%d/%d)....\n" , entry % width , width ) ;
			col_converter = 0 ;
			row_converter ++ ;
		} 
	}
	
	/* As with the loop, this stack is used to reverse the stack of alignments
	in order to adhere to the assignments criteria */
	stack<string> ALCs ;																VP (".OUTP.$.........pointer stack size = %lu...\n", ALs->size()) ;
	while ( ! ALs->empty() ) {
		ALCs.push ( ALs->top() ) ;
		ALs->pop ( ) ;
	}

	fprintf( output , "\n\n\n2.o3:\n") ;												VP (".OUTP.$.........writing 2.o3...\n") ; VP (".OUTP.$.........intial stack size = %lu...\n", ALCs.size()) ;
	if ( ! ALCs.empty() ) parse_alignment ( output , &ALCs ) ;							VP (".OUTP.$.........remaining stack size = %lu...\n", ALCs.size()) ;
	
	fprintf( output , "\n\n2.o4:\n") ;													VP (".OUTP.$.........writing 2.o4...\n") ;
	if ( ALCs.size() > 1 ) { fprintf( output , "YES") ; } else { fprintf( output , "NO") ; } VP (".OUTP.$.........remaining stack size = %lu...\n", ALCs.size()) ;
	
	fprintf( output , "\n\n2.o5:\n") ;													VP (".OUTP.$.........writing 2.o5...\n") ;
	while ( ! ALCs.empty() ) { parse_alignment ( output , &ALCs ) ; fprintf( output , "\n\n") ; ALCs.pop(); }

	fclose ( output ) ;
}

/* Highest level method for needleman_wunsch, utilizes the same methods with global (0) features active */
void needleman_wunsch ( string * sequence_A , string * sequence_B ) {
	similarity_matrix SM ;																VP (".NDWH.$......running needleman_wunsch for \"%s\" and \"%s\"...\n", sequence_A->c_str() , sequence_B->c_str() );
	int width = sequence_A->size()+1 ;
	int length = sequence_B->size()+1 ;
	int entry_count = length * width ;
	SM.seqA = sequence_A ;																VP (".NDWH.$......the first sequence is \"%s\"...\n", SM.seqA->c_str() );
	SM.seqB = sequence_B ;																VP (".NDWH.$......the second sequence is \"%s\"...\n", SM.seqB->c_str() );
	int smatrix [entry_count];															VP (".NDWH.$......establishing similarity matrix of size \"%d\"...\n", entry_count );
	memset( smatrix, 0, entry_count*sizeof(smatrix[0]) ) ;  
	SM.matrix = smatrix ; 
	stack<int> XS ;
	int highest_score = build_similarity_matrix ( &SM , &XS , 0 ) ;						VP (".NDWH.$......optimal stack size = %lu ...\n", XS.size() );
	stack<string> ALs ;
	traceback_similarity_matrix ( &SM , &ALs , "" , "" , 0 , width , length-1 , width-1 , 0 ) ;
	char filename [] = "global_output.txt" ;
	output_results ( &SM , &ALs , width , entry_count , highest_score , filename ) ;
	return ;
}

/* Highest level method for smith_waterman, utilizes the same methods with local (1) features active */
void smith_waterman  ( string * sequence_A , string * sequence_B ) {
	similarity_matrix SM ;																VP (".SMWT.$......running smith_waterman for \"%s\" and \"%s\"...\n", sequence_A->c_str() , sequence_B->c_str() );
	int width = sequence_A->size()+1 ;
	int length = sequence_B->size()+1 ;
	int entry_count = length * width ;
	SM.seqA = sequence_A ;																VP (".SMWT.$......the first sequence is \"%s\"...\n", SM.seqA->c_str() );
	SM.seqB = sequence_B ;																VP (".SMWT.$......the second sequence is \"%s\"...\n", SM.seqB->c_str() );
	int smatrix [entry_count];															VP (".SMWT.$......establishing similarity matrix of size \"%d\"...\n", entry_count );
	memset( smatrix, 0, entry_count*sizeof(smatrix[0]) ) ;  
	SM.matrix = smatrix ; 
	stack<int> XS ;
	int highest_score = build_similarity_matrix ( &SM , &XS , 1 ) ;						VP (".SMWT.$......optimal stack size = %lu ...\n", XS.size() );
	stack<string> ALs ;
	while ( ! XS.empty() ) {
		int max_index = XS.top() ;
		traceback_similarity_matrix ( &SM , &ALs , "" , "" , 1 , width , (max_index/width) , (max_index%width) , 0 ) ;
		XS.pop() ;
	}
	char filename [] = "local_output.txt" ;
	output_results ( &SM , &ALs , width , entry_count , highest_score , filename ) ;
	return ;
} 

/* A static entry point for the sake of avoiding using makefile */
int main ( int argc , char * argv[] ) {
	string sequence_A (argv[1]) ;														VP (".MAIN.$...the first sequence is \"%s\"...\n", sequence_A.c_str() );
	string sequence_B (argv[2]) ;														VP (".MAIN.$...the second sequence is \"%s\"...\n", sequence_B.c_str() );
																						VP (".MAIN.$...entering needleman_wunsch()...\n");
	needleman_wunsch ( &sequence_A , &sequence_B ) ;									VP (".MAIN.$...entering smith_waterman()...\n");
	smith_waterman ( &sequence_A , &sequence_B ) ;
	return 1 ;
}