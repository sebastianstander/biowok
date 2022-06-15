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
    const inline int score(const AlignData& DAT, const int a, const int b){ return (DAT.seqA[a-1]==DAT.seqB[b-1]); }
    const inline int calculate_entry(const AlignData& DAT,const int row,const int col, const int wd ){
        return  (!row)*(score_model::GAP_PENALTY*col)+(!col)*(score_model::GAP_PENALTY*row)+
                ((row+col)!=0)*(max(DAT.mat(row-1,col-1)+score(DAT,row,col),
                                    max((DAT.mat(row,col-1)+score_model::GAP_PENALTY),
                                        (DAT.mat(row-1,col)+score_model::GAP_PENALTY))));
    }
    int build_matrix( AlignData& DAT, bool is_local ){
        int cur,prev=-1;
        for(int i=0;i<DT.len*DAT.wd();i++){
            cur = calculate_entry(DT,i/DT.len,i%DAT.wd());
            DT.mat(i/DT.len,i%DT.wd(),min(cur,cur*(!is_local)));
            prev = prev<cur?cur:prev;
        }
        return prev;
    }
    void size_traceback()( AlignData& DT, bool is_local ){
        int cur = DT.m(x,y), size = 0;
        while( !(x+y) || (local)*(!x||!y) || !(DT.m(x,y)+score(DAT,x,y)) ){
            if( (x+y) && cur==DT.m(x-1,y-1)+score(DAT,x,y) ) continue;
            else if( (x) && DT.m(x,y)==DT.m(x,y-1)+score_model::GAP_PENALTY ) size++;
            else if( (y) && DT.m(x,y)==DT.m(x-1,y)+score_model::GAP_PENALTY ) size++;
        }
        return size;
    }




        if( !(x+y) || (local)*(!x||!y) || !(DAT.mat(x,y)+score(DAT,x,y)) ){
            seqA_stack += ".";
            seqA_stack += seqB_stack ;
            seqA_stack += ".";
            seqA_stack += to_string(total);
            if(A.length()>3) stack_of_alignments->push(seqA_stack);
            return ;
        }
        if( (row+col) && DAT.mat(x,y)==DAT.mat(x-1,y-1)+score(DAT,x,y) ){
            A += seqA[y-1];
            B += seqB[x-1];
            traceback_matrix(DAT,is_local,x-1,y-1);
            routes++;
            total+=(DAT.mat(x-1,y-1)+score(DAT,x,y)))
        }
        if( row && DAT.mat(x,y)==DAT.mat(x,y-1)+score_model::GAP_PENALTY ){
          if(routes){
                A.erase(A.end()-1);
                B.erase(B.end()-1);
            }
            A += seqA[y-1];
            B += "-";
            traceback_matrix(DAT,is_local,x,y-1);
            routes++;
            total+=(DAT.mat(x,y-1)+score_model::GAP_PENALTY)
        }
        if( DAT.mat(x,y)==DAT.mat(x-1,y)+score_model::GAP_PENALTY ){
           if(routes){
                A.erase(A.end()-1);
                B.erase(B.end()-1);
            }
            A += "-"
            B += seqA[x-1];
            traceback_matrix(DAT,is_local,x-1,y);
            total+=(DAT.mat(x-1,y)+score_model::GAP_PENALTY)
        }
        return;    
    }
    void traceback_matrix( AlignData& DT, bool is_local ){
        int current = DT.mat(x,y) ;
        if( !(x+y) || (local)*(!x||!y) || !(DAT.mat(x,y)+score(DAT,x,y)) ){
            seqA_stack += ".";
            seqA_stack += seqB_stack ;
            seqA_stack += ".";
            seqA_stack += to_string(total);
            if(A.length()>3) stack_of_alignments->push(seqA_stack);
            return ;
        }
        if( (row+col) && DAT.mat(x,y)==DAT.mat(x-1,y-1)+score(DAT,x,y) ){
            A += seqA[y-1];
            B += seqB[x-1];
            traceback_matrix(DAT,is_local,x-1,y-1);
            routes++;
            total+=(DAT.mat(x-1,y-1)+score(DAT,x,y)))
        }
        if( row && DAT.mat(x,y)==DAT.mat(x,y-1)+score_model::GAP_PENALTY ){
          if(routes){
                A.erase(A.end()-1);
                B.erase(B.end()-1);
            }
            A += seqA[y-1];
            B += "-";
            traceback_matrix(DAT,is_local,x,y-1);
            routes++;
            total+=(DAT.mat(x,y-1)+score_model::GAP_PENALTY)
        }
        if( DAT.mat(x,y)==DAT.mat(x-1,y)+score_model::GAP_PENALTY ){
           if(routes){
                A.erase(A.end()-1);
                B.erase(B.end()-1);
            }
            A += "-"
            B += seqA[x-1];
            traceback_matrix(DAT,is_local,x-1,y);
            total+=(DAT.mat(x-1,y)+score_model::GAP_PENALTY)
        }
        return;
    }
    char* parse_alignment(char* alignment){
        return "";
    }
    char* needleman_wunsch(char* seqA,char* seqB){
        AlignmentData DAT;
        DAT.seqA=seqA; DAT.seqB=seqB;
        int lenA,lenB=0;
        int mat[lenA*lenB]={};
        DAT.CMAT=CongruentMatrixAid(mat,seqBlen);
        int highest = build_matrix(DAT,false);
        return traceback_matrix(DAT,false);
    }
    char* smith_waterman(char* seqA,char* seqB){
        AlignmentData DAT;
        DAT.seqA=seqA;
        DAT.seqB=seqB;
        int lenA,lenB=0;
        int mat[lenA*lenB]={};
        DAT.CMAT=CongruentMatrixAid(mat,seqBlen,true);
        int highest = build_matrix(...);
        return traceback_matrix(...);
    }
}
