using UINT = unsigned int;
typedef template<T> class CongruentMatrixHelper<T>{
    T* m_instance;
    UINT m_wd,m_size;
    public:
        CongruentMatrixHelper(T& instance,UINT wd,UINT n):
            m_instance{instance},
            m_wd{wd},
            m_size{n}{}
        ~FormattedMatrix(){}
        inline T operator()(int x,int y){
            return m_instance[(x*m_wd)+y];
        }
        inline void operator()(int val,int x,int y){
            m_instance[(x*m_wd)+y] = val;
        }
} CMAT ;