#include "../../utils/FeedbackMacro.hpp"
#include "../../utils/TypeAbbreviations.hpp"
#include "../../utils/BiowokHelperFunctions.hpp"
struct AlignData {
    UINT ht,wd,mid;
    int highest;
    char* sqA,sqB,AL;
    int* m;
};
enum score {
    GAP_PENALTY=-2,
    MISMATCH=-1,
    MATCH=2
};
namespace aligner {
    inline void setm(AlignData& DT, const UINT x, const UINT y,const UINT value){ DT.m[(x*DT.wd)+y] = value; }

    const inline int getm(AlignData& DT, const UINT x, const UINT y){ return DT.m[(x*DT.wd)+y]; }

    const inline int match(AlignData& DT, const UINT a, const UINT b){ return (DT.sqA[a-1]==DT.sqB[b-1]); }

    const inline int calculate_entry(AlignData& DT,const int x,const int y ){
        return  (!x) * (GAP_PENALTY*y) + (!y) * (GAP_PENALTY*x) +
                (!(x+y)) * (max(    getm(DT,x-1,y-1)+match(DT,x,y),
                                    max(    (getm(DT,x,y-1)+GAP_PENALTY),
                                            (getm(DT,x-1,y)+GAP_PENALTY)))); }
    int build( AlignData& DT, const bool is_local );
    UINT get_size_of_alignment( AlignData& DT, const bool is_local );
    void traceback( const AlignData& DT, const bool is_local );
    char* needleman_wunsch(char* seqA,char* seqB);
    char* smith_waterman(char* seqA,char* seqB);
};