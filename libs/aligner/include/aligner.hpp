#include "../../utils/FeedbackMacro.hpp"
#include "../../utils/TypeAbbreviations.hpp"
#include "../../utils/BiowokHelperFunctions.hpp"
struct AlignData {
    int Gscr,Xscr,Oscr;
    int ht,wd,ALmid,ALsize,highest;
    int* m;
    char* sqA;char* sqB;char* AL;
};
inline void setm(AlignData& DT,const UINT x,const UINT y,const int value){ 
    DT.m[(x*DT.wd)+y] = value;
}
inline int getm(AlignData& DT,const UINT x,const UINT y){ 
    return DT.m[(x*DT.wd)+y];
}
inline int match(AlignData& DT,const UINT a,const UINT b){
    return (DT.sqA[a-1]==DT.sqB[b-1]);
}
inline int calculate_entry(AlignData& DT,const int x,const int y){
    int choice = (max(    getm(DT,x-1,y-1) + (match(DT,x,y)*DT.Xscr) + (!(match(DT,x,y))*DT.Oscr),
                                max(    (getm(DT,x,y-1)+DT.Gscr),
                                        (getm(DT,x-1,y)+DT.Gscr))));
    fdbk("\t<%d,%d>...\n\t\t| (%d+(%d)) | (%d+(%d)) |\n\t\t| (%d+(%d)) |  ->%d\n",x,y,getm(DT,x-1,y-1),match(DT,x,y)?DT.Xscr:DT.Oscr,getm(DT,x-1,y),DT.Gscr,getm(DT,x,y-1),DT.Gscr,choice);
    return choice;
}     
namespace aligner {
    void build(AlignData& DT,const bool is_local);
    UINT get_alignment_size(AlignData& DT,const bool is_local);
    void traceback(AlignData& DT,const bool is_local);
    char* align(char* seqA,char* seqB,const bool is_local, 
                const int gap_score=-1, const int match_score=1, const int mismatch_score=-1);
}
