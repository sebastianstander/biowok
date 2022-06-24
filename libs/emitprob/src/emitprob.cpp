namespace viterbi {
    build()
    fill()
};
namespace frwd_bkwd {
    build()
    fill()
};

viterbi::build(){
    
}

void 




void forward( HMMData& HMD ){
    int prev_sum ;
    for( int ob=0; ob<sqlen; ob++){
        
    }
    for( int ob=0; ob<sqLen; ob++ ){
        for( int stt=0; stt<sttCount; stt++){
            if(Emission is 0) {
                prev_sum = start_prob_for_state
            } else {
                nmax
                for prev_state in states
                prev_sum = 
            } 
            tb[i][k] = emission[i+1][k] * prev_sum ;
        }      
    }
    p
}
void backward(HMMData& HMD,char* seq){
    for ( possible states )

}
void viterbi(HMMData& HMD,char* seq){
    multiple_optimal_paths = False
    for( states in 1st column )
        result[0] = start_prob[state] * em_prob[state][1st column] 
    for( i in sequence )
        max_total_prob = result[i-1]
        prev_selection = 
        for( state in each other column )
            total_prob = 
            if( total_prob > max_total_prob ){
                max_total_prob = total_prob
                prev_selection = prev_state
            } else if( total_prob == max_total_prob ){
                multiple_optimal_paths = True
            }
        max_prob = max_total_prob * emission_prob[state][seq[i]]
        m[i][state] = ( max_prob , prev_state )
    max_prob = nmax( m Last Column )
    

}
void posterior(HMMData& HMD,char* seq){
    forward()
    backward()
    

        

}