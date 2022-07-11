#if ADD_FEEDBACK==1
    #ifdef fdbk
        #define print_rounded_pm(m,lg,wd)\
            for( int x=0 ; x<lg ; x++ ){\
                fdbk ("\t\t\t");\
                for( int off=0 ; off<x ; off++ ){\
                    fdbk ("              ");\
                }\
                for( int y=x ; y<wd ; y++ ){\
                    fdbk ("[%d,%d](%s%d):",x,y,(((x*wd)-bwok_math::nsum(x)+y)>9)?"":" ",(x*wd)-bwok_math::nsum(x)+y);\
                    if(x>y){\
                        fdbk (" -- ");\
                    } else if( m[(x*wd)-bwok_math::nsum(x)+y]>-1 ){\
                        if( m[(x*wd)+y]>9 )\
                            fdbk (" %d ",int(m[(x*wd)-bwok_math::nsum(x)+y]) );\
                        else\
                            fdbk ("  %d ",int(m[(x*wd)-bwok_math::nsum(x)+y]) );\
                    } else {\
                        if( m[(x*wd)+y]>9 )\
                            fdbk ("%d ",int(m[(x*wd)-bwok_math::nsum(x)+y]) );\
                        else\
                            fdbk (" %d ",int(m[(x*wd)-bwok_math::nsum(x)+y]) );\
                    }\
                }\
                fdbk ("\n");\
            }
    #else
        #define print_rounded_pm(m,lg,wd)
    #endif
#else
    #define print_rounded_pm(m,ld,wd)
#endif
template <typename T>
class bwokPMat {
    private:    T *m_mat;
                unsigned int m_wd;
                bool m_on_stack;
    public:
        bwokPMat( unsigned int wd , T *m ): m_mat{m} , m_wd{wd} , m_on_stack{true}{         fdbk("\tPartial Typed <%dx%d> Matrix Established On Stack...\n",m_wd,m_wd);
        }
        bwokPMat( unsigned int wd ): m_mat{new T[bwok_math::nsum(wd)]} , m_wd{wd} , m_on_stack{false}{   fdbk("\tPartial Typed <%dx%d> Matrix Established On Heap...\n",m_wd,m_wd);
        }
        ~bwokPMat(){
            if(!m_on_stack) delete[] m_mat;                                   fdbk("\tPartial Typed <%dx%d> Matrix Discarded...\n",m_wd,m_wd);
        }
        inline T gt( unsigned int const x , unsigned int const y  ) const {
            return m_mat[(x*m_wd)-bwok_math::nsum(x)+y] ;
        }
        inline void st( unsigned int const x , unsigned int const y , T const cur ){
            m_mat[(x*m_wd)-bwok_math::nsum(x)+y] = cur ;
        }
        inline void display() const {
            print_rounded_pm(m_mat,m_wd,m_wd);
        }
};