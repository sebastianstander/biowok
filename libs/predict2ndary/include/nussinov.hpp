/**
 * @file nuss.hpp
 * @author Sebastian Stander (sebastianstander@github.com)
 * @brief A header of nussinov's algorthim for biowok.
 * @version 0.1
 * @date 2022-06-02
 */
using UINT = unsigned int;
struct NussData{	//A collection of references, preferrablely to stack allocated data
	UINT len; 			//The length of the current RNA sequence being predicted upon.
	char* seq; 			//A reference to a c-string containing the RNA sequence.
	char* fld;			//A c-string containing the RNA secondary structure in char form.
	int* mat;			//A reference to the 1D array representing the distance matrix.
};
namespace nussinov{
	/**
	 *	@brief i.e. "set value within matrix". Inline helper function used to set values via imitating 2D-Matrix set operation with a 1D, reduced integer array setup. 
	 *	@param nd refrence to the struct (NussData) of useful local integers and pointers to local variables. Provides a reference to the matrix.
	 *	@param x The approximate x-dimensional index.
	 *	@param y The approximate y-dimensional index.
	 *	@return A char, or byte, containing the value of the nucleotide at the corresponding 2-bit index of i. Wastes 6 bits.
	 *	@note Operation Count(abs): 4 per, 1 Access Call, 1 Multiplication, 1 Addition, 1 Assignment.
	 */
	inline UINT smat(NussData& nd,const UINT& x,const UINT& y,const UINT& val){
		nd.mat[(x*nd.len)+y] = val;
		return nd.mat[(x*nd.len)+y] ;
	}
	
	/**
	 *	@brief i.e. "get value from matrix". Inline helper function used to retrieve values via imitating 2D-Matrix set operation with a 1D, reduced integer array setup.
	 *	@param nd refrence to the struct (NussData) of useful local integers and pointers to local variables. Provides a reference to the matrix.
	 *	@param x The approximate x-dimensional index.
	 *	@param y The approximate y-dimensional index.
	 *	@return An integer containing the numeric value at the equivalent 2D index.
	 *	@note Operation Count(abs): 3 per, 1 Access Call, 1 Multiplication, 1 Addition.
	 */
	const inline UINT gmat(const NussData& nd,const UINT& x,const UINT& y){
		return nd.mat[(x*nd.len)+y];
	}

	/**
	 *	@brief i.e. "get nucleotide". Inline helper function to access nucleotide data form it's compressed, 2 bit format. 
	 *	@param nd refrence to the struct (NussData) of useful local integers and pointers to local variables.
	 *	@param i the index of a given nucluotide, ordered as the sequence was entered into the program.
	 *	@return A character (or byte) containing the value of the nucleotide at the corresponding 2-bit index of i. Wastes 6 bits.
	 *	@note Operation Count(abs): 30 per, 4 Modulos, 4 Divisions, 4 Comparisons, 4 Multiplications, 3 Additions, 4 Access Calls, 4 ANDs, 3 Bitshifts)   
	 */
	const inline char gnuc(const NussData& nd,const int i){
		return (i%4==0)*((nd.seq[i/4]&0xC0)>>6)+(i%4==1)*((nd.seq[i/4]&0x30)>>4)+
				(i%4==2)*((nd.seq[i/4]&0x0C)>>2)+(i%4==3)*((nd.seq[i/4]&0x03));
	}

	/**
	 *	@brief Inline helper function to get the max of two integers without using the STL, libstdc, or libstdc++.
	 *	@param a A simple integer for comparison.
	 *	@param b A simple integer for comparison.
	 *	@return An interger containing the larger of the two parameter-passed integers, a and b.
	 *	@note Operation Count(abs): 5 per, 2 Comparisons, 2 Multiplications, 1 Addition.
	 */	
	const inline int max(const UINT& a,const UINT& b){
		return (a<=b)*b+(a>b)*a;
	}

	/**
	 *	@brief Inline function that compares a pair of nucleotides to the legal pairings of nucleotides as dictated by RNA.
	 *	@param pair A character/byte containing a packed pair of nucleotides. Wastes 4 bits.
	 *	@return A boolean dictated whether the provided paramter passed pair of nucleotides, in compressed 2-bit form and packed into a single 1 byte chararacter/byte, matches any legal pairing.
	 *	@note Operation Count(abs): 7 per, 4 Comparisons, 3 Additions.
	 */
	const inline bool is_coupled(const char& pair){
		return (pair==0x01)+(pair==0x04)+(pair==0x0B)+(pair==0x0E);
	}

	/**
	 *	@brief .
	 *	@param fmt
	 *	@param seq
	 *	@param n 
	 *	@return .
	 *	@note Operation Count(abs): .
	 */
	void compress_sequence(char* fmt,const char* seq,const UINT n);

	/**
	 *	@brief The matrix filling portion of nussinov's algorithm.
	 *	@param nd reference to the struct (NussData) of useful local integers and pointers to local variables. Provides a reference to the matrix, sequence, sequence length.
	 *	@param m An integer refering to the minimumally allowable size for a bifuricated loop.
	 *	@note Operation Count(abs): .
	 */
	void build(NussData& nd,const UINT& m);

	/**
	 *	@brief The traceback portion of nussinov's algorithm.
	 *	@param nd reference to the struct (NussData) of useful local integers and pointers to local variables. Provides a reference to the matrix, sequence, sequence length, and c-string to store the RNA secondary structure.
	 *	@param i A x-dimensional index. Use for the recursive bifurication portion of the algorithm.
	 *	@param j A y-dimensional index. Use for the recursive bifurication portion of the algorithm.
	 *	@return A c-string copy of the RNA sequence's predicted secondary structure.
	 *	@note Operation Count(abs): .
	 */
	void traceback(NussData& nd,UINT i,UINT j);

	/**
	 *	@brief A overarching method use to perform both sequence reformatting and all components of nussinov's algorithm.
	 *	@param seq A string literal of the RNA sequence whose structure is to be predicted. 
	 *	@return A c-string copy of the RNA sequence's predicted secondary structure.
	 *	@note Operation Count(abs): .
	 */
	void predict(char* seq,char*fold);
};