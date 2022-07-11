
void forward( HMM& MD , EPData& EP ){
    int pd_frwd=0;
    for( int st=0 ; st<k ; st++) 
        EP.tb[st] = HMM.pb_start[st] * HMM.pb_emit[DT.sq[0]+st];
    for( int ob=1 ; ob<EP.n ; ob++ ){
        for( int st=0 ; st<HMM.k ; st++ ){
            for( int prev ; prev<HHM.k ; prev++ )
                EP.tb[ob+st] += EP.tb[(ob-1)+prev] 
                              * HMM.p b_trans[prev+st];
            EP.tb[ob+st] *= HMM.pb_emit[DT.sq[ob]+st];
        }      
    }
    for( int st=0 ; st<HMM.k ; stt++ )
        pd_frwd *= HMM.pb_trans[(n-1)+st];
    return pd_frwd;
}
void backward( HMM& MD , EPData& EP ){
    int pd_bkwd=0;
    for( int st=0 ; st<k ; st++ ) 
        EP.tb[(n-1)+st] = HMM.pb_trans[DT.sq[n-1]+st];
    for( int ob=EP.n-1 ; ob>0 ; ob-- ){
        for( int stt=0 ; stt<sttCount ; stt++ ){
            for( int prev ; prev < EP.k ; prev++ )
                tb[ob+stt] += EP.tb[(ob-1)+prev] 
                            * HMM.pb_trans[stt+prev]
                            * HMM.pb_emit[DT.sq[ob-1]+prev] ;
        }      
    }
    for( int st=0; st<k; st++) 
        pd_bkwd = HMM.pb_start[st] * HMM.pb_emit[DT.sq[0]+st];
    return pd_bkwd;
}
void posterior( HMM& MD , EPData& EP ){
    pd_frwd = forward( MD , EP );
    pd_bkwd = backward( MD , EP );
    ASSERT( pd_frwd==pd_bkwd );
    for( int ob=0 ; ob<n ; ob++ ){
        for ( int st=0 ; st<k ; st++ )
           EP.tb_post[ob+st] += (EP.tb[ob+st] 
                             * EP.tb[mid+ob+st])/pd_frwd ;
    }
    return;
}
void viterbi( HMM& MD , char* seq ){
    int cur = 0; 
    for( int st=0 ; st<k ; st++ ){ 
        EP.tbA[st] = HMM.pb_start[st] * pb_emit[DT.sq[0]+st];
        EP.tbB[st] = 0;
    }
    for( int ob=1 ; ob<n ; ob++ ){
        for( int st=0 ; st<k ; st++ ){
            cur = (EP.tba[(ob-1)+st]*pb_trans[st]*pb_emit[DT.sq[j]+st]);
            EP.tbA[ob+st] = max(cur,EP.tbA[ob+st]);
            EP.tbB[ob+st] = cur>EP.tbA[ob+st]?ob:EP.tbB[ob+st];
        }
    }

}
void viterbi( HMM& MD , char* seq ){
    for( int st=0 ; st<k ; st++ ) 
        EP.tb[(n-1)+st] = HMM.pb_trans[DT.sq[n-1]+st];
    for( int ob=1 ; ob<n ; ob++ ){
        for ( int st=0 ; st<k ; st++ ){
            pb_trb_max = tb ?? * pb_trans[st+??]
            for( int prev ; prev < EP.k ; prev++ ){
                pb_trb = EB.tb[??] * pb_trans[prev+st];
                pb_trb_max = max(pb_trb,pb_trb_max);
                prev_slct = (pb_trb>pb_trb_max) ? prev : prev_slct;
            }
            pb_max = pb_trb_max * pb_emit[st+PB.sq[ob]];
            EP.tb[ob+st] = pb_trb_max;
            EP.tb[ob+st+?] = prev_slct;
        }
    }
    float pb_max=0.0;
    int best_st=-1;
    for( int _=0 ; _<n ; _++ ){ 
        pb_max = max(max_prob,data["prob"]);
        best_st = (data["prob"]>pb_max)?st:best_st;
    }
    previous = best_st ;
    for( int _=0 ; _<n ; _++ ){
        previous = ? ;
    }
}


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

     int prev_sum ;
    for( int stt=0; stt<sqlen; stt++){
        tb[stt] = start_prob[stt] * em_prob[stt+DT.sq[0]]
        tb[MD.n+stt] = 0;
    }
    for( int ob=1; ob<sqLen; ob++ ){
        for( int stt=0; stt<sttCount; stt++){
            

            tb[ob+stt] = 0;
            for( int prevstt;prevstt<sttCount; prevstt++){
                tb[ob+prevstt] += tb[(ob-1)+stt] * transition_prob[prevstt] ;
            }
            tb[ob+stt] *= emission_prob * ;
            
            tb[i][k] = emission[i+1][k] * prev_sum ;
        }      
    }
}