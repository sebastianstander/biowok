#include "sequence_aligner.hpp"




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
}



GGGG---
----AAA
4 3 = 7 * 2 = 14

(A.len+B.len)*2



8 8     64

8 9     72

16 16 32
16 18 34

9*4 = 36
8*4 = 32

