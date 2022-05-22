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
void cluster () {
	return ;
}
void build_distance_matrix () {
	return ;
}
void output_distance_matrix ( int element_count ) {
	int rows = 1
	for (int i = 0 ; int i < element_count ; i++ ) {
		if ( i % count == 0 ) {
			i = i + rows ;
		}
	}
	return ;
}
void UPGMA ( string * input_file ) {
	FILE * input = fopen (input_file) ;
	build_distance_matrix () ;



	cluster ( &distance_martix )

}
int main ( int argc , char * argv [] ) {
	string input_file (argv[1]) ;
	UPGMA ( &input_file ) ;
	return 0 ;
}