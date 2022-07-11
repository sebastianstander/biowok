#if ADD_FEEDBACK==1
    #ifdef fdbk
        #define print_mat(m,lg,wd)\
            for( int x=0 ; x<lg ; x++ ){\
                fdbk ("\t\t\t");\
                for( int y=0 ; y<wd ; y++ ){\
                    /*fdbk ("[%d,%d](%s%d):",x,y,(((x*wd)+y)>9)?"":" ",(x*wd)+y);*/\
                    if(x>y){\
                        fdbk (" -- ");\
                    } else if( m[(x*wd)+y]>-1 ){\
                        if( m[(x*wd)+y]>9 )\
                            fdbk (" %d ",int(m[(x*wd)+y]) );\
                        else\
                            fdbk ("  %d ",int(m[(x*wd)+y]) );\
                    } else {\
                        if( m[(x*wd)+y]>9 )\
                            fdbk ("%d ",int(m[(x*wd)+y]) );\
                        else\
                            fdbk (" %d ",int(m[(x*wd)+y]) );\
                    }\
                }\
                fdbk ("\n");\
            }
    #else
        #define print_mat(m,lg,wd)
    #endif
#else
    #define print_mat(m,ld,wd)
#endif
template <class T>
class bwokMat {
    private:    bool m_on_stack;
                unsigned int m_wd, m_lg;
    public:     T *m_mat;
    public:
        bwokMat( unsigned int lg , unsigned int wd , T *m ): m_mat{m} , m_wd{wd} , m_on_stack{true}{       fdbk("\t Typed <%dx%d> Matrix Established On Stack...\n",m_lg,m_wd);
        }
        bwokMat( unsigned int lg , unsigned int wd ): m_mat{new T[lg*wd]} , m_wd{wd} , m_on_stack{false}{  fdbk("\t Typed <%dx%d> Matrix Established On Heap...\n",m_lg,m_wd);
        }
        ~bwokMat(){
            if(!m_on_stack) delete[] m_mat;                                                                 fdbk("\t Typed <%dx%d> Matrix Discarded...\n",m_wd,m_wd);
        }
        inline T gt( unsigned int const x , unsigned int const y  ) const {
            return m_mat[(x*m_wd)+y] ;
        }
        inline void st( unsigned int const x , unsigned int const y , T const cur ){
            m_mat[(x*m_wd)+y] = cur ;
        }
        inline void display() const {
            print_rounded_pm(m_mat,m_lg,m_wd);
        }
};