/**
 * @file nuss.hpp
 * @author Sebastian Stander (sebastianstander@github.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-02
 */
#ifdef ADD_FEEDBACK
	#include <iostream>
	#define fdbk(...) std::cout << __VA_ARGS__
	#define test_pass(nd)\
		int(*m)[nd.len]=(int(*)[nd.len])nd.mat;\
		for(int i=0;i<nd.len;i++){\
			for(int j=0;j<nd.len;j++){ fdbk(m[i][j]); fdbk(" ");}\
			fdbk("\n");\
		}fdbk("\n");   
#else
	#define test_pass(nd)
	#define fdbk(...)
#endif
struct NussData {
	int recur;
	int len;
	char* seq;
	char* fld;
	int* mat;
};
namespace nussinov {
	/**
	 *	@brief i.e. "set value in matrix". Inline helper function used to set values via imitating 2D-Matrix set operation with a 1D, reduced integer array setup. 
	 *	@param nd refrence to the struct (NussData) of useful local integers and pointers to local variables. Provides a reference to the matrix.
	 *	@param x The approximate x-dimensional index.
	 *	@param y The approximate y-dimensional index.
	 *	@return A char, or byte, containing the value of the nucleotide at the corresponding 2-bit index of i. Wastes 6 bits.
	 *	@note Operation Count(abs): 4 per, 1 Access Call, 1 Multiplication, 1 Addition, 1 Assignment.
	 */
	const inline void smat(NussData& nd,int val,int x,int y){nd.mat[x*nd.len+y]=val;};
	
	/**
	 *	@param nd refrence to the struct (NussData) of useful local integers and pointers to local variables. Provides a reference to the matrix.
	 *	@param x The approximate x-dimensional index.
	 *	@param y The approximate y-dimensional index.
	 *	@return An integer containing the numeric value at the equivalent 2D index.
	 *	@brief i.e. "get value in matrix". Inline helper function used to retrieve values via imitating 2D-Matrix set operation with a 1D, reduced integer array setup.
	 *	@note Operation Count(abs): 3 per, 1 Access Call, 1 Multiplication, 1 Addition.
	 */
	const inline int gmat(NussData& nd,int x,int y){return nd.mat[x*nd.len+y];};

	/**
	 *	@brief i.e. "get nucleotide". Inline helper function to access nucleotide data form it's compressed, 2 bit format. 
	 *	@param nd refrence to the struct (NussData) of useful local integers and pointers to local variables.
	 *	@param i the index of a given nucluotide, ordered as the sequence was entered into the program.
	 *	@return A character (or byte) containing the value of the nucleotide at the corresponding 2-bit index of i. Wastes 6 bits.
	 *	@note Operation Count(abs): 23 per, 4 Modulos, 4 Divisions, 4 Comparisons, 4 Multiplications, 3 Additions, 4 Access Calls    
	 */
	const inline char gnuc(NussData& nd,int i){return (i%4==3)*(nd.seq[i/4]&&0x3F)+(i%4==2)*(nd.seq[i/4]&&0xCF)+(i%4==1)*(nd.seq[i/4]&&0xF3)+(!i%4)*(nd.seq[i/4]&&0xFC);}

	/**
	 *	@brief Inline helper function to get the max of two integers without using the STL, libstdc, or libstdc++.
	 *	@param a A simple integer for comparison.
	 *	@param b A simple integer for comparison.
	 *	@return An interger containing the larger of the two parameter-passed integers, a and b.
	 *	@note Operation Count(abs): 5 per, 2 Comparisons, 2 Multiplications, 1 Addition.
	 */	
	const inline int max(const int a, const int b){return (a<=b)*b+(a>b)*a;}

	/**
	 *	@brief Inline function that compares a pair of nucleotides to the legal pairings of nucleotides as dictated by RNA.
	 *	@param pair A character/byte containing a packed pair of nucleotides. Wastes 4 bits.
	 *	@return A boolean dictated whether the provided paramter passed pair of nucleotides, in compressed 2-bit form and packed into a single 1 byte chararacter/byte, matches any legal pairing.
	 *	@note Operation Count(abs): 7 per, 4 Comparisons, 3 Additions.
	 */
	const inline bool is_coupled(char pair){return (pair==0x01)+(pair==0x04)+(pair==0x0B)+(pair==0x0E); }

	char* compress_sequence(char* formatted,const char* seq,int n);

	void build_matrix( NussData& nd , const int& min_loop_len );
	void traceback_matrix( NussData& nd , int i , int j );

	char* run( const char* seq );
};
/*
- - - - - - 21	len 6
  - - - - -
    - - - - 
	  - - -
	    - -
		  -

- - - - - 15	len 5
  - - - -
    - - -
      - -
	    -
- - - - 10		len 4
  - - -
    - -
      -
- - - 6			len 3
  - -
    -

n(n-1)/2		3(2)/2 = 3
				4(3)/2 = 6
				5(4)/2 = 10
				6(5)/2 = 15
				7(6)/2 = 21

n 

21 /2  = 10.5 = 10


0b00000000 4 per byte
00 A
01 U
10 C
11 G


*/
