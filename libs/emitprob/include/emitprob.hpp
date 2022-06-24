#include "../../utils/BiowokHelperFunctions.hpp"
#include "../../utils/TypeAbbreviations.hpp"
#include "../../utils/FeedbackMacro.hpp"
struct HMMData{
    char* emission
    char* states
    
    char* start_prob
    char* emission_prob
    int* tble
};
void forward(HMMData& HMD,char* seq);
void backward(HMMData& HMD,char* seq);
void viterbi(HMMData& HMD,char* seq);
void posterior(HMMData& HMD,char* seq);