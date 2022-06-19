typedef class CongruentMatrixAid{
    int* m_ref;
    int m_wd;
    public :
        CongruentMatrixAid(int* ref,int wd) : m_ref{ref} , m_wd{wd}{}
        int operator()(int x,int y){ return ref[(x*wd)+y]; }
        void operator()(int x,int y,int val){ ref[(x*wd)+y] = val; }
        constexpr wd(){return m_wd}
} CMAT;