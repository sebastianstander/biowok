namespace bwok_math {
    inline unsigned int nsum( unsigned int n ){
        return (n*(n+1))/2;
    }   
    template<typename V>
    inline V max(const V a,const V b){ 
        return (a>b?a:b); 
    }
    template<typename V>
    inline V min(const V a,const V b){ 
        return (a>b?b:a); 
    }
    template<typename V>
    inline V abs(const V a){ 
        return (a>0?a:-a); 
    }
}