using UINT = unsigned int;
namespace aligner{
    #if PRECOMPRESSED==1
        inline UINT m(AlignmentData& DT,UINT& x,UINT& y){return (x*DT.wd())+y;}
        inline UINT sq(AlignmentData& DT,UINT& i){}
    #else
        inline UINT m(AlignmentData& DT,UINT& x,UINT& y){return (x*DT.wd())+y;}
        inline UINT sq(AlignmentData& DT,UINT& i){}
    #endif

    struct AlignData{
        int* m;
        char* seqA;
        char* seqB;
        char* AL;
    };
    const int strlen(char* s){
        int n=0;
        while(s[n]!='\0') n++;
        return n;
    }
    enum score_model{MISMATCH=-1,MATCH=2,GAP_PENALTY=-2};
    
    const inline int min(const int a,const int b){ return a>b?b:a; }

    const inline int max(const int a,const int b){ return a>b?a:b; }

    const inline int score(AlignData& DT, const int a, const int b){ 
        return (DT.seqA[a-1]==DT.seqB[b-1]);
    }

    const inline int calculate_entry(AlignData& DT,const int x,const int y, const int wd ){
        return  (!x)*(score_model::GAP_PENALTY*y)+(!y)*(score_model::GAP_PENALTY*x)+
                ((x+y)!=0)*(max(DT.mat(x-1,y-1)+score(DT,x,y),
                                    max((DT.mat(x,y-1)+score_model::GAP_PENALTY),
                                        (DT.mat(x-1,y)+score_model::GAP_PENALTY))));
    }

    int build( AlignData& DT, const bool is_local );
    void get_size_of_alignment( AlignData& DT, const bool is_local );
    void traceback( AlignData& DT, const bool is_local );
    char* parse_alignment(char* alignment);
    char* needleman_wunsch(char* seqA,char* seqB);
    char* smith_waterman(char* seqA,char* seqB);
};