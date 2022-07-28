using UINT = unsigned int ;
template <class T>
class bwokStack {
    private:    bool m_is_on_heap , m_is_tail ;
                T* m_stack ;
                UINT m_top , m_cap ;
                bwokStack *m_next, *m_tail ;
    public:
        bwokStack( UINT initial_capacity , char* str = nullptr ): 
                m_str{ (str==nullptr) ? new char[initial_capacity] : str } , 
                m_cap{ initial_capacity } , 
                m_is_on_heap{ (str==nullptr) ? true : false } , 
                m_is_tail{ false } {
            fdbk("\t CString %s Established On %s...\n",m_str,((str==nullptr)?"Stack":"Heap"));
        }
        ~bwokStack(){
            if(!m_on_stack) delete[] m_stack;                                                                 
            fdbk("\t Typed <%dx%d> Matrix Discarded...\n",m_wd,m_wd);
        void operator=( const char* cstr ){
            
        }
        void operator=( bwokCString str ){
            
        }
        void operator+=( const char* cstr ){
            
        }
        void operator+=( bwokCString str ){
            
        }
        void operator[]( UINT i ){
            
        }
        char operator[]( UINT i ){
            return 
        }
};