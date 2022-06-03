/**
 * @file nuss.hpp
 * @author Sebastian Stander (sebastianstander@github.com)
 * @brief The header for Nuess's streamlined version of nussinov's algorthim.
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
// A collection of references , to stack allocated data
struct NussData{
	//The length of the current RNA sequence being predicted upon.
	int len;
	//A reference to a c-string containing the RNA sequence.
	char* seq;
	//A c-string containing the RNA secondary structure in char form.
	char* fld;
	//A reference to the 1D array representing the distance matrix.
	int* mat;
};
namespace nussinov{
	/**
	 *	@brief i.e. "set value in matrix". Inline helper function used to set values via imitating 2D-Matrix set operation with a 1D, reduced integer array setup. 
	 *	@param nd refrence to the struct (NussData) of useful local integers and pointers to local variables. Provides a reference to the matrix.
	 *	@param x The approximate x-dimensional index.
	 *	@param y The approximate y-dimensional index.
	 *	@return A char, or byte, containing the value of the nucleotide at the corresponding 2-bit index of i. Wastes 6 bits.
	 *	@note Operation Count(abs): 4 per, 1 Access Call, 1 Multiplication, 1 Addition, 1 Assignment.
	 */
	inline void smat(NussData& nd,const int& val,int& x,int& y){nd.mat[x*nd.len+y]=val;}
	
	/**
	 *	@param nd refrence to the struct (NussData) of useful local integers and pointers to local variables. Provides a reference to the matrix.
	 *	@param x The approximate x-dimensional index.
	 *	@param y The approximate y-dimensional index.
	 *	@return An integer containing the numeric value at the equivalent 2D index.
	 *	@brief i.e. "get value in matrix". Inline helper function used to retrieve values via imitating 2D-Matrix set operation with a 1D, reduced integer array setup.
	 *	@note Operation Count(abs): 3 per, 1 Access Call, 1 Multiplication, 1 Addition.
	 */
	const inline int gmat(const NussData& nd,int& x,int& y){return nd.mat[x*nd.len+y];}

	/**
	 *	@brief i.e. "get nucleotide". Inline helper function to access nucleotide data form it's compressed, 2 bit format. 
	 *	@param nd refrence to the struct (NussData) of useful local integers and pointers to local variables.
	 *	@param i the index of a given nucluotide, ordered as the sequence was entered into the program.
	 *	@return A character (or byte) containing the value of the nucleotide at the corresponding 2-bit index of i. Wastes 6 bits.
	 *	@note Operation Count(abs): 23 per, 4 Modulos, 4 Divisions, 4 Comparisons, 4 Multiplications, 3 Additions, 4 Access Calls    
	 */
	const inline char gnuc(const NussData& nd,int& i){return (i%4==3)*(nd.seq[i/4]&&0x3F)+(i%4==2)*(nd.seq[i/4]&&0xCF)+(i%4==1)*(nd.seq[i/4]&&0xF3)+(!i%4)*(nd.seq[i/4]&&0xFC);}

	/**
	 *	@brief Inline helper function to get the max of two integers without using the STL, libstdc, or libstdc++.
	 *	@param a A simple integer for comparison.
	 *	@param b A simple integer for comparison.
	 *	@return An interger containing the larger of the two parameter-passed integers, a and b.
	 *	@note Operation Count(abs): 5 per, 2 Comparisons, 2 Multiplications, 1 Addition.
	 */	
	const inline int max(int& a,int& b){return (a<=b)*b+(a>b)*a;}

	/**
	 *	@brief Inline function that compares a pair of nucleotides to the legal pairings of nucleotides as dictated by RNA.
	 *	@param pair A character/byte containing a packed pair of nucleotides. Wastes 4 bits.
	 *	@return A boolean dictated whether the provided paramter passed pair of nucleotides, in compressed 2-bit form and packed into a single 1 byte chararacter/byte, matches any legal pairing.
	 *	@note Operation Count(abs): 7 per, 4 Comparisons, 3 Additions.
	 */
	const inline bool is_coupled(const char& pair){return (pair==0x01)+(pair==0x04)+(pair==0x0B)+(pair==0x0E);}

	/**
	 *	@brief .
	 *	@param fmt
	 *	@param seq
	 *	@param n 
	 *	@return .
	 *	@note Operation Count(abs): .
	 */
	char* compress_sequence(char* fmt,const char* seq,const int n);

	/**
	 *	@brief The matrix filling portion of nussinov's algorithm.
	 *	@param nd reference to the struct (NussData) of useful local integers and pointers to local variables. Provides a reference to the matrix, sequence, sequence length.
	 *	@param m An integer refering to the minimumally allowable size for a bifuricated loop.
	 *	@note Operation Count(abs): .
	 */
	void build(NussData& nd,const int& m);

	/**
	 *	@brief The traceback portion of nussinov's algorithm.
	 *	@param nd reference to the struct (NussData) of useful local integers and pointers to local variables. Provides a reference to the matrix, sequence, sequence length, and c-string to store the RNA secondary structure.
	 *	@param i A x-dimensional index. Use for the recursive bifurication portion of the algorithm.
	 *	@param j A y-dimensional index. Use for the recursive bifurication portion of the algorithm.
	 *	@return A c-string copy of the RNA sequence's predicted secondary structure.
	 *	@note Operation Count(abs): .
	 */
	void traceback(NussData& nd,int i,int j);

	/**
	 *	@brief A overarching method use to perform both sequence reformatting and all components of nussinov's algorithm.
	 *	@param seq A string literal of the RNA sequence whose structure is to be predicted. 
	 *	@return A c-string copy of the RNA sequence's predicted secondary structure.
	 *	@note Operation Count(abs): .
	 */
	char* predict(const char* seq);
};
