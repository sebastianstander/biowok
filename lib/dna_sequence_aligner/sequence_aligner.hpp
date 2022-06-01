namespace sequence_aligner{
    struct Stack{
        Stack* head;
        Stack* prev;
        char* val;
        int len;
        Stack(Stack* p,char* s,int n):head{nullptr}prev{p},val{s},len{n}{
            
        }
        Stack(Stack* p,char* s,int n):head{nullptr}prev{p},val{s},len{n}{
            
        }
    }
    const int strlen(char* s){
        int n=0;
        while(s[n]!='\0') n++;
        return n;
    }
    inline  Stack push(Stack* p,char* s,int n){
        Stack node{p,s,n};
    }
    inline char* pop(Stack* cur){
        char* val = cur->val;
        Stack* 
        return
        
    }
    inline peek(){
        
    }


    enum score_model{MISMATCH=-1,MATCH=2,GAP_PENALTY=-2};
    typedef class CongruentMatrixAid{
        int* m_ref;
        int m_wd;
        public :
            CongruentMatrixAid(int* ref,int wd):m_ref{ref},m_wd{wd}{}
            int operator()(int x,int y){return ref[(x*wd)+y];}
            void operator()(int x,int y,int val){ref[(x*wd)+y] = val;}
            constexpr wd(){return m_wd}
    } CMAT;
    struct AlignData {
        CMAT mat ;
        int len ;
        char* seqA ;
        char* seqB ;  
        char* alignment ;
    };
    const inline int min(const int a,const int b){ return a>b?b:a; }
    const inline int max(const int a,const int b){ return a>b?a:b; }
    const inline int score(const AlignData& DAT, const int a, const int b){
        return (DAT.seqA[a-1]==DAT.seqA[b-1]);
    }
    const inline int calculate_entry(const AlignData& DAT,const int row,const int col, const int wd ){
        return  (!row)*(score_model::GAP_PENALTY*col)+(!col)*(score_model::GAP_PENALTY*row)+
                ((row+col)!=0)*(max(DAT.mat(row-1,col-1)+score(DAT,row,col),
                                    max((DAT.mat(row,col-1)+score_model::GAP_PENALTY),
                                        (DAT.mat(row-1,col)+score_model::GAP_PENALTY))));
    }
    int build_matrix( AlignData& DAT, bool is_local ){
        int cur,prev=-1;
        for(int i=0;i<DAT.len*DAT.wd();i++){
            cur = calculate_entry(DAT,i/DAT.len,i%DAT.wd());
            DAT.mat(i/DAT.len,i%DAT.wd(),min(cur,cur*(!is_local)));
            prev = prev<cur?cur:prev;
        }
        return prev;
    }
    void traceback_matrix( AlignData& DAT, bool is_local ){
        int current = DAT.mat(x,y) ;
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
