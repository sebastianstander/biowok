/**
 * @file aligner.hpp
 * @author Sebastian Stander (sebastianstander@github.com)
 * @brief The header of sequence alignment suite for biowok.
 * @version 0.2
 * @date 2022-07-25
 */
#include "../../utils/bwokFeedback.hpp"
#include "../../utils/bwokMath.hpp"
#include "../../utils/bwokCString.hpp"
#include "../../utils/bwokTypedMatrix.hpp"
using UINT = unsigned int ;

namespace Align {
    struct ScoreModel { 
        int gap , match , mismatch; 
        ScoreModel( int gap_ , int match_ , int mismatch_ ) : gap{gap_} , match{match_} , mismatch{mismatch_}{}
    } ;
    inline UINT worst_case_alignment_size( UINT m, UINT n ){ 
        return (2*n)+(2*m)-2 ;
    }

    /**
	 *	@brief Contains both the data (or references/pointers to the data) alongside the means for conducting Needleman-Wunsch (Global Alignment) or Smith-Waterman (Local Alignment) on any set of UTF-8 characters.
	 */
    class Aligner {
        enum TraceStep {
                REVERSE = 0 , UP = 1 , LEFT = 2 , UP_LEFT = 3 , DIAG = 4 , UP_DIAG = 5 , LEFT_DIAG = 6 , ALL = 7 , CEASE = 8 
        };
        private:    bool m_mat_on_heap ;            // Flag, denotes whether dynamic allocation for the distance matrix is nessisary or not.
                    bool m_alignment_on_heap ;      // Flag, denotes whether dynamic allocation for the alignment string is nessisary.
                    bool m_local ;                  // Flag, denotes whether Needlemen-Wunsch (Global Alignment) or Smith-Waterman (Local Alignment) is being conducted.
                    //UINT m_ALmid ;                  // Marker, denotes the index of the '.' middle of the alignment c-string, ex. C-A.-AA
                    //UINT m_ALsize ;                 // Size, denotes the size of the alignment c-string.
                    int m_highest ;                 // Marker, for Smith-Waterman (Local Alignment), denotes the highest index.
        public:     char *m_sqA ;                   // C-String Pointer, points to the first of the two parameter sequences.
                    char *m_sqB ;                   // C-String Pointer, points to the second of the two parameter sequences.
                    char *m_AL ;                    // C-String Pointer, can either be allocated in the local scope, or defaulted to dynamic allocation upon construction.
                    UINT m_m ;                      // Size, denotes the size of the first of the two parameter sequences.
                    UINT m_n ;                      // Size, denotes the size of the first of the two parameter sequences.
                    UINT m_wc_len ;                 // Size, denotes length of the alignment in the worst case. Used by record the alignment.
                    int m_final_score ;            // 
                    ScoreModel m_SM ;               // Model, contains the s(adjustable) scoring model for the alignment.
                    bwokMat<int> *m_mat ;           // A 1D "Distance Matrix" used to conduct to conduct the algorithm.
        public:
            /**
             *	@brief Default and only constructor for the Aligner Class. 
                        Allows pointers to class-external instances of the distance matrix, forking stack, and alignment c-string.
                        If no pointers are provided, each of the objects are allocated on the heap during class construction.
            *	@param seqA char*, a pointer to a the first of the two sequences to be aligned. Should be pre-allocated outside the Class.
            *	@param seqA char*, a pointer to a the first of the two sequences to be aligned. Should be pre-allocated outside the Class.
            *	@param local bool, a flag dicating whether the intial alignment will be global or local.
            *	@param SM Struct, A "stack allocated on initalization" instance of the ScoreModel for usage with the aligner.
            *	@param alignment char*, a pointer to 
            *	@param matrix The approximate y-dimensional index.
            */
            Aligner( char* seqA , char* seqB , bool local , ScoreModel SM = {-2,1,-1} , 
                        char* alignment = nullptr ,  bwokMat<int>* matrix = nullptr ) : 
                    m_mat_on_heap{ (matrix==nullptr) ? true : false } , 
                    m_alignment_on_heap{ (alignment==nullptr) ? true : false } , 
                    m_local{ local } , 
                    m_sqA{ seqA } , 
                    m_sqB{ seqB } , 
                    m_AL{  (alignment!=nullptr)  ? alignment : new char[2*(bwok_cstr::glen(seqA)+1)+2*(bwok_cstr::glen(seqB)+1)-2] } ,
                    m_m{ bwok_cstr::glen(seqB)+1 } ,
                    m_n{ bwok_cstr::glen(seqA)+1 } , 
                    m_wc_len{ 2*(bwok_cstr::glen(seqA)+1)+2*(bwok_cstr::glen(seqB)+1)-2 } ,
                    m_SM{ SM } ,
                    m_mat{  (matrix!=nullptr) ? matrix : new bwokMat<int>{bwok_cstr::glen(seqA)+1,bwok_cstr::glen(seqB)+1} } { 
                fdbk("<Aligner::Aligner> Testing variables : (matrix==nullptr) = %d , (alignment==nullptr) = %d , m_mat_on_heap = %d , m_alignment_on_heap = %d",
                        (matrix==nullptr),(alignment==nullptr),m_mat_on_heap,m_alignment_on_heap);
                build();
                
                //traceback();
            }

             /**
             *	@brief Default and only deconstructor for the Aligner Class.
             *         If the distance matrix and alignment cstring were on the heap, 
             *         deallocates the both of them. 
             */
            ~Aligner(){
                if( m_mat_on_heap ) {   
                    fdbk("<Aligner::~Aligner> Releasing from Stack.");
                    delete m_mat ;        
                }
                if( m_alignment_on_heap ) {
                    fdbk("<Aligner::~Aligner> Releasing from Heap.");
                    delete m_AL ;         
                }
            }

            inline void redo_as_local_or_global() {
                m_local = (m_local)?false:true;
                build();
                traceback();
            }
        private:
            void build(); 
            inline int match( const UINT a , const UINT b ) const { return (m_sqA[a-1]==m_sqB[b-1]); }
            inline int calculate_entry( const int x , const int y ) const {
                int diagonal = (m_mat->gt(x-1,y-1))/10 + ((match(x,y))?m_SM.match:m_SM.mismatch) ;  
                int left = (m_mat->gt(x,y-1)/10)+m_SM.gap ;                                         
                int up = (m_mat->gt(x-1,y)/10)+m_SM.gap ;                                           
                int route = bwok_math::max(diagonal,bwok_math::max (left,up));                      
                int result = route*10 ;                                                             
                result += ((route==diagonal)*((result>0)?TraceStep::DIAG:-TraceStep::DIAG));
                result += ((route==up)*((result>0)?TraceStep::UP:-TraceStep::UP));
                result += ((route==left)*((result>0)?TraceStep::LEFT:-TraceStep::LEFT));            
                return result;
            }
            void update_alignment( UINT* trace_stack , UINT& stack_head );
            void traceback();
    };
}