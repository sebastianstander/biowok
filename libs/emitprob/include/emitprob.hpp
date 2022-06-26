#include "../../utils/BiowokHelperFunctions.hpp"
#include "../../utils/TypeAbbreviations.hpp"
#include "../../utils/FeedbackMacro.hpp"
struct HHM{
    char* emission;          // [ 00-A 01-T 10-C 11-G ]
    int m;
    char* states;            // stt_count / [ ]
    int k;
    //default all to 1/count, assert if _ does not equal 1
    float* pb_start;      // stt_count
    float* pb_trans;  // stt_count*stt_count [ H->H , H->L , L->H , L->H ]
    float* pb_emit;    // stt_count*emission_count
};
struct EPData{
    char* seq;
    int n;          // Length of the Observable Sequence
    float* tb;              // 2*stt_count*n
};

void forward(HMMData& HMD,char* seq);
void backward(HMMData& HMD,char* seq);
void viterbi(HMMData& HMD,char* seq);
void posterior(HMMData& HMD,char* seq);