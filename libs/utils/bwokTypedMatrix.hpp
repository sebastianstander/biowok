#ifdef fdbk
    #define print_rounded_mat(m,wd,lg)\
        for( int x=0 ; x<wd ; x++ ){\
            fdbk ("\t\t\t");\
            for( int y=0 ; y<lg ; y++ ){\
                fdbk ("[%d,%d](%d): ",x,y,(x*lg)+y);\
                if( m[(x*lg)+y]>-1 ){\
                    if( m[(x*lg)+y]>9 )\
                        fdbk (" %fd ",int(m[(x*lg)+y]) );\
                    else\
                        fdbk ("  %d ",int(m[(x*lg)+y]) );\
                } else {\
                    if( m[(x*lg)+y]<-9 )\
                        fdbk ("%d ",int(m[(x*lg)+y]) );\
                    else\
                        fdbk (" %d ",int(m[(x*lg)+y]) );\
                }\
            }\
            fdbk ("\n");\
        }
#else
    #define print_rounded_mat(m,ld,wd)
#endif
template <class T>
class bwokMat {
    private:    bool m_on_stack;
                unsigned int m_wd, m_lg;
    public:     T *m_mat;
    public:
        bwokMat( unsigned int wd , unsigned int lg , T *m ): m_on_stack{true} , m_wd{wd} , m_lg{lg} , m_mat{m} {       
            fdbk("\t Typed <%dx%d> Matrix Established On Stack...\n",m_lg,m_wd);
        }
        bwokMat( unsigned int wd , unsigned int lg ): m_on_stack{false} , m_wd{wd} , m_lg{lg} , m_mat{new T[lg*wd]}{  
            fdbk("\t Typed <%dx%d> Matrix Established On Heap...\n",m_lg,m_wd);
        }
        ~bwokMat(){
            if(!m_on_stack) delete[] m_mat;                                                                 
            fdbk("\t Typed <%dx%d> Matrix Discarded...\n",m_wd,m_wd);
        }
        inline T gt( unsigned int const x , unsigned int const y  ) const {
            return m_mat[(x*m_lg)+y] ;
        }
        inline void st( unsigned int const x , unsigned int const y , T const cur ){
            m_mat[(x*m_lg)+y] = cur ;
        }
        inline void display() {                                                                             
            fdbk("\t Displaying Typed <%dx%d> Matrix ...\n",m_wd,m_lg);
            print_rounded_mat(m_mat,m_wd,m_lg);                                                             
            fdbk("\t Typed <%dx%d> Matrix Displayed...\n",m_wd,m_lg);
        }
};