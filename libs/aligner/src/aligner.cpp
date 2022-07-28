#include "../include/aligner.hpp"
#define ROUTE_OFFSET = 10 ;
#define ITERATION_OFFSET = 100 ;
void Align::Aligner::build(){                                                           fdbk("\t Establishing Distance Matrix...\n");
    int cur = -1, grst = 0;     
        //
    m_mat->display();
    m_mat->st( 0 , 0 , 0 );                                     
    for( UINT x=1 ; x<m_n ; x++ ){                              
        m_mat->st( x , 0 , (((x*m_SM.gap)*10)-TraceStep::UP)*(!m_local) ) ;             fdbk("\t\t Case A : <%d,0> to %d via (((%d*%d)*10)-%d)*(!%d))...\n",x,m_mat->gt(x,0),x,m_SM.gap,TraceStep::LEFT,m_local);
    }
    for( UINT y=1 ; y<m_m ; y++ ){                              
        m_mat->st( 0 , y , (((y*m_SM.gap)*10)-TraceStep::LEFT)*(!m_local)  );           fdbk("\t\t Case B : <0,%d> to %d via (%d*%d(!%d))...\n",y,m_mat->gt(0,y),y,m_SM.gap,m_local);
    }                        
    for( UINT x=1 ; x<m_n ; x++ ){
        for( UINT y=1 ; y<m_m ; y++){
            cur = calculate_entry( x , y );
            m_mat->st( x , y , bwok_math::max(cur,cur*(!m_local)) );
            m_highest = (grst>cur) ? m_highest : (y*m_n)+x ;                            fdbk( "\t\t Case C : <%d,%d>... ( %c , %c )\t| (%d+(%d)) | (%d+(%d)) |\n\t\t                         \t| (%d+(%d)) |  ->%d\n", x , y , m_sqA[x-1] , m_sqB[y-1] , m_mat->gt(x-1,y-1) , m_mat->gt(x,y)?m_SM.match:m_SM.mismatch , m_mat->gt(x-1,y) , m_SM.gap , m_mat->gt(x,y-1) , m_SM.gap, m_mat->gt(x,y) );
        }
    }                                                                                   fdbk("\t Distance Matrix Completed...\n");
    m_mat->display();                                                                                                                                  
    return;
}
/*
    items in trace_stack (trstk)
        format :    ...xxxx y z
        x : (*100)  index recorded
        y : (*10)   remaining routes
        z : (*1)    direction taken (to next index)
*/

void Align::Aligner::update_alignment( UINT* trace_stack , UINT& stack_head ){
    UINT a = m_n , b = m_m , path_taken ;
        //
    for( UINT i=0 ; i<m_wc_len ; i++ ){
        path_taken = (trace_stack[i]/10)%10 ;
        m_AL[i] = (path_taken==TraceStep::LEFT)*('-') + (path_taken==TraceStep::DIAG)*(m_sqA[a]) ;
        a = (path_taken==TraceStep::LEFT) ? a-1 : a ;
        m_AL[i+stack_head+1] = (path_taken==TraceStep::UP)*('-') + (path_taken==TraceStep::DIAG)*(m_sqB[b]) ;
        b = (path_taken==TraceStep::UP) ? b-1 : b ;
    }
}
void Align::Aligner::traceback(){                                                           fdbk("\t Tracing Back Distance Matrix...");
    bool tracing_back = true , use_fork = false ;
    UINT stack_head , last_fork , last_fork_score ;
    int x , y , route , cur_score ;
    UINT trace_stack[m_wc_len] ;
        //
    while( tracing_back ){
        route = ( use_fork ) ? 
                    trace_stack[stack_head]%10 : 
                    m_mat->gt(x,y)%10 ;
        cur_score += m_mat->gt(x,y) / 10 ;                                                 fdbk("\t\t For Entry <%d,%d>(%d), score(%d)",x,y,route,cur_score);
        switch( route ) {             
            case TraceStep::CEASE :     tracing_back = false ; break ;                                                     
            case TraceStep::UP :        stack_head++;                                      
                                        trace_stack[stack_head] = ((x*m_n)+y)*100;
                                        trace_stack[stack_head] += TraceStep::UP ;
                                        y--; 
                                        break ;                                            fdbk("\t\t For Entry <%d,%d>(%d), score(%d)",x,y,route,cur_score);
            case TraceStep::DIAG :      stack_head++;
                                        trace_stack[stack_head] = ((x*m_n)+y)*100;
                                        trace_stack[stack_head] += TraceStep::DIAG ;
                                        x-- ; y-- ; break ;
            case TraceStep::LEFT :      stack_head++ ;
                                        trace_stack[stack_head] = ((x*m_n)+y)*100 ;
                                        trace_stack[stack_head] += TraceStep::LEFT ;
                                        x-- ; break ;
            case TraceStep::LEFT_DIAG : stack_head++ ;
                                        trace_stack[stack_head] = ((x*m_n)+y)*100 ;
                                        trace_stack[stack_head] += TraceStep::LEFT ;
                                        x-- ; y-- ; break ;
            case TraceStep::UP_DIAG :   stack_head++ ;
                                        trace_stack[stack_head] = ((x*m_n)+y)*100 ;
                                        trace_stack[stack_head] += TraceStep::DIAG ;
                                        x-- ; y-- ; break ;
            case TraceStep::UP_LEFT :   stack_head++ ;
                                        trace_stack[stack_head] = ((x*m_n)+y)*100 ;
                                        trace_stack[stack_head] += TraceStep::LEFT ;
                                        x-- ; break ;
            case TraceStep::ALL:        stack_head++;
                                        trace_stack[stack_head] = ((x*m_n)+y)*100;
                                        trace_stack[stack_head] += TraceStep::UP_LEFT ;
                                        x-- ; y-- ; break ;
            case TraceStep::REVERSE :   while( !!(trace_stack[stack_head]%10) ) {
                                            stack_head-- ;
                                            if(stack_head<0) return;
                                        }
                                        x = (trace_stack[stack_head]/100) / m_n ;
                                        y = (trace_stack[stack_head]/100) % m_n ;
                                        if( m_final_score > cur_score ){
                                            update_alignment( trace_stack , stack_head );
                                            m_final_score = cur_score ;   
                                        }
                                        use_fork = true ; break ;
            default:                    break;
        }
        use_fork = false ;
    }                                                                                       fdbk("\t Traceback Complete...");
}

