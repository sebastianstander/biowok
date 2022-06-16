#include "sequence_aligner.hpp"
int aligner::build( AlignData& DT, const bool is_local ){
    int cur,prev=-1;
    for(int i=0;i<DT.len*DT.wd();i++){
        cur = calculate_entry(DT,i/DT.len,i%DT.wd);
        DT.mat(i/DT.len,i%DT.wd(),max(cur,cur*(!is_local)));
        prev = prev<cur?cur:prev;
    }
    return prev;
}
void aligner::get_size_of_alignment( AlignData& DT, const bool is_local ){
    int x = xmax, y = ymax;
    int cur = DT.m(x,y), size = 0;
    while( !(x+y) || (local)*(!x||!y) || !(DT.m(x,y)+score(DT,x,y)) ){
        if( (x+y) && cur==DT.m(x-1,y-1)+score(DT,x,y) ) {
            x--;
            y--;
        } else if( (x) && DT.m(x,y)==DT.m(x,y-1)+score_model::GAP_PENALTY ){
            size++;
            y--;
        } 
        else if( (y) && DT.m(x,y)==DT.m(x-1,y)+score_model::GAP_PENALTY ){
            size++;
            x--;   
        }
    }
    return size;
}
void aligner::traceback( AlignData& DT, const bool is_local ){
    int x = xmax, y = ymax;
    int cur = DT.m(x,y), size = 0;
    while( !(x+y) || (local)*(!x||!y) || !(DT.m(x,y)+score(DT,x,y)) ){
        if( (x+y) && cur==DT.m(x-1,y-1)+score(DT,x,y) ) {
            x--;
            y--;
        } else if( (x) && DT.m(x,y)==DT.m(x,y-1)+score_model::GAP_PENALTY ){
            size++;
            y--;
        } 
        else if( (y) && DT.m(x,y)==DT.m(x-1,y)+score_model::GAP_PENALTY ){
            size++;
            x--;   
        }
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
char* aligner::needleman_wunsch(char* seqA,char* seqB){
    AlignmentData DAT;
    DAT.seqA=seqA; DAT.seqB=seqB;
    int lenA,lenB=0;
    int mat[lenA*lenB]={};
    DAT.CMAT=CongruentMatrixAid(mat,seqBlen);
    int highest = build_matrix(DAT,false);
    return traceback_matrix(DAT,false);
}
char* aligner::smith_waterman(char* seqA,char* seqB){
    AlignmentData DAT;
    DAT.seqA=seqA;
    DAT.seqB=seqB;
    int lenA,lenB=0;
    int mat[lenA*lenB]={};
    DAT.CMAT=CongruentMatrixAid(mat,seqBlen,true);
    int highest = build_matrix(...);
    return traceback_matrix(...);
}
/*void traceback_matrix( AlignData& DT, bool is_local ){
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
}*/

/*
int aligner::build( AlignmentData& DT, bool is_local ){
    int cur,prev=-1;
    for(int i=0;i<DT.len*DT.wd();i++){
        cur = calculate_entry(DT,i/DT.len,i%DT.wd());
        DT.mat( i/DT.len , i%DT.wd() , min(cur,cur*(!is_local)) );
        prev = prev<cur ? cur : prev;
    }
    return prev;
}
void aligner::traceback( AlignmentData& DT , bool is_local ){
    while( !(x+y) || is_local*(!x||!y) || DT.m(x,y)+score(DT,x,y) ){
        if ( (!(x+y)>0) && DAT.m(x,y) == DAT.m(x-1,y-1)+score(DT,x,y) ){ 
            A+=sq[y-1]; B+=sq[x-1]; y--; x--; continue;
        } else if( (x>0) && DAT.m(x,y) == DAT.m(x,y-1)+scoring::GAP_PENALTY ){
            A+=sq[y-1]; B+="-"; x--; continue;
        } else if( (y>0) && DAT.m(x,y) == DAT.m(x-1,y)+scoring::GAP_PENALTY ){
            A+="-"; B+=sq[x-1]; y--; continue;
        }
    }
}*/