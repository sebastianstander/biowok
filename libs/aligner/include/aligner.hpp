#include "../../utils/bwokFeedback.hpp"
#include "../../utils/bwokMath.hpp"
#include "../../utils/bwokCString.hpp"
#include "../../utils/bwokTypedMatrix.hpp"
using UINT = unsigned int;

struct ScoreModel { 
    int gap , match , mismatch; 
    ScoreModel( int gap_=-1 , int match_=1 , int mismatch_=-1 ):
        gap{gap_} , match{match_} , mismatch{mismatch_}{}
} ;
class Aligner {
    private:    bool m_is_local , m_mat_on_heap, m_alignment_on_heap ;
                int m_m , m_n , m_ALmid , m_ALsize , m_highest ;
                ScoreModel m_SM ;
    public:     char *m_sqA , *m_sqB , *m_AL ;
                bwokMat<int> *m_mat ;
    public:
        Aligner( char* seqA , char* seqB , bool is_local_ , char* alignment = nullptr ,  bwokMat<int>* matrix = nullptr , ScoreModel={-1,1,-1} ): 
            m_mat_on_heap{(matrix==nullptr)?true:false} , m_alignment_on_heap{(alignment==nullptr)?true:false} , m_is_local{is_local_} , 
            m_sqA{seqA} , m_n{bwok_cstr::glen(seqA)+1}, m_sqB{seqB} , m_m{bwok_cstr::glen(seqB)+1} ,
            m_mat{(matrix==nullptr)?new bwokMat<int>{bwok_cstr::glen(seqA),bwok_cstr::glen(seqB)}:matrix} , 
            m_AL(aligment==nullptr)?nullptr:alignment{} { align(); }
        ~Aligner(){
            if( m_mat_on_heap ) delete[] m_mat ;
            if( m_alignment_on_heap ) delete[] m_AL ;
        }
    private:
        inline int match( const UINT a , const UINT b ) const { return (m_sqA[a-1]==m_sqB[b-1]); }
        inline int calculate_entry( const int x , const int y ) const {
            int choice = (bwok_math::max( m_mat->gt(x-1,y-1) + (match(x,y)*m_SM.match) + (!(match(x,y))*m_SM.mismatch),
                              bwok_math::max( (m_mat->gt(x,y-1)+m_SM.gap) , (m_mat->gt(x-1,y)+m_SM.gap))));
            fdbk("\t<%d,%d>...\n\t\t| (%d+(%d)) | (%d+(%d)) |\n\t\t| (%d+(%d)) |  ->%d\n",x,y,m_mat->gt(x-1,y-1),m_mat->gt(x,y)?m_SM.match:m_SM.mismatch,m_mat->gt(x-1,y),m_SM.gap,m_mat->gt(x,y-1),m_SM.gap,choice);
            return choice;
        }
        void build();
        UINT get_alignment_size();
        void traceback();
        void align();
};
