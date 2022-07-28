#include "../include/aligner.hpp"
void Aligner::align(){                                              
                                                                    m_mat->display();
    build();                                                        fdbk("\tScore Model in Use : \n\t\t-GAP = %d\n\t\t-MATCH = %d\n\t\t-MISS = %d\n",m_SM.gap,m_SM.match,m_SM.mismatch);
                                                                    fdbk("\tSequence A : \"%s\"\n\tLength of A \"%d\" | Matrix Width : \n",m_sqA,m_n);
                                                                    fdbk("\tSequence B : \"%s\"\n\tLength of B \"%d\" | Matrix Length : \n",m_sqB,m_m);
                                                                    m_mat->display();
    m_ALsize = get_alignment_size();                                fdbk("\tLength of first half of Alignment : \"%d\"\n",m_ALmid);
    char algnmt[m_ALsize+1]; 
    m_AL = algnmt;                                                fdbk("\tLength of Alignment : \"%d\"\n",m_ALsize);
    traceback();                                                  fdbk("\tFinal Alignment :... \n%s\n\n",m_AL);
    return;
}                  
void Aligner::build(){                                              fdbk("\t Building Distance Matrix...\n");
    int cur,greatest=-1;                            
    for( int x=0 ; x<m_n ; x++ ){
        m_mat->st( x , 0 , x*m_SM.gap*(!m_is_local) );              fdbk("\t\t Case A : <%d,0> to %d via (%d*%d(!%d))...\n",x,m_mat->gt(x,0),x,m_SM.gap,m_is_local);
    }
    for( int y=1 ; y<m_m ; y++ ){ 
        m_mat->st( 0 , y , y*m_SM.gap*(!m_is_local) );              fdbk("\t\t Case B : <0,%d> to %d via (%d*%d(!%d))...\n",y,m_mat->gt(0,y),y,m_SM.gap,m_is_local);
    }
    for( int x=1 ; x<m_n ; x++ ){
        for( int y=1 ; y<m_m ; y++){
            cur = calculate_entry( x , y );
            m_mat->st( x , y , bwok_math::max(cur,cur*(!m_is_local)) );
            m_highest = (greatest>cur) ? m_highest : (y*m_n)+x;     
        }
    }                                                               fdbk("\t Distance Matrix Completed...\n");
    return;
}
UINT Aligner::get_alignment_size(){
    int x , y , cur ;                                               fdbk("\n\tConducting Initial Trace to gage Alignment String Size :...\n");
    UINT gap_count = 0 ;
    m_ALmid = m_n-1 ;
    if(m_is_local){                                                 fdbk("\n\tLooking for a LOCAL alignment :...\n");
        x = m_highest / m_n ;
        y = m_highest % m_n ; 
    } else {                                                        fdbk("\n\tLooking for a GLOBAL alignment :...\n");
        x = m_n-1 ; 
        y = m_m-1 ; 
    }                  
    while( !!(x) && !!(y) ){                                        fdbk("\tTracing from <%d,%d>{%c,%c} :...",x,y,m_sqA[x-1],m_sqB[y-1]);
        cur = m_mat->gt(x,y);                                       fdbk("\n\t\t-------------------------\n\t\t| %d (%d-%s) | %d (%d-%s) |\n\t\t-------------------------\n\t\t| %d (%d-%s) | \"%d\" <", 
                                                                                m_mat->gt(x-1,y-1) , m_mat->gt(x-1,y-1)+(match(x,y)*m_SM.match+(!(match(x,y))*m_SM.mismatch)) , (m_mat->gt(x,y)==m_mat->gt(x-1,y-1)+((match(x,y)*m_SM.match)+(!(match(x,y))*m_SM.mismatch)))?"T":"F" ,
                                                                                m_mat->gt(x-1,y) , m_mat->gt(x-1,y)+m_SM.gap , (m_mat->gt(x,y)==m_mat->gt(x-1,y)+m_SM.gap)?"T":"F" ,
                                                                                m_mat->gt(x,y-1) , m_mat->gt(x,y-1)+m_SM.gap , (m_mat->gt(x,y)==m_mat->gt(x,y-1)+m_SM.gap)?"T":"F" ,
                                                                                m_mat->gt(x,y) );
        if( !!(x+y) && cur==m_mat->gt(x-1,y-1)+
                       ( match(x,y)*m_SM.match+
                        (!(match(x,y))*m_SM.mismatch) )) {          fdbk("...Heading Diagonally (%s)\n" , match(x,y)?"MATCH":"MISMATCH");
            x--; y--;
        } else if( !!(x) && cur==m_mat->gt(x,y-1)+m_SM.gap ) {    fdbk("...Heading Left (GAP) \n");
            gap_count++; m_ALmid++; y--;
        } else if( !!(y) && cur==m_mat->gt(x-1,y)+m_SM.gap) {     fdbk("...Heading Up (GAP) \n");
            gap_count++; x--;
        } else {                                                    fdbk("...ERROR: No Case Found\n"); 
            break; 
        }                                                           fdbk("\t\t-------------\n");
    }
    while ( !(m_is_local) && !!(x+y) ){                             fdbk("\tTracing from <%d,%d>{%c,%c} :..." , x , y , m_sqA[x-1] , m_sqB[y-1]);
        if(!!(y)) {                                                 fdbk("...Heading Left (GAP) \n");                  
            gap_count++; m_ALmid++; y--;                          
        } else if(!!(x)) {                                          fdbk("...Heading Up (GAP) \n");
            gap_count++; x--;
        }                                                           fdbk("\t\t-------------\n");
    }   
    return gap_count+(m_m-1)+(m_n-1)+1;
}
void Aligner::traceback(){
    int x,y,cur;
    for(int i=0;i<m_ALsize+1;i++) m_AL[i]='_';
    m_AL[m_ALsize]='\0';
    m_AL[m_ALmid]='.';
    if(m_is_local){ x = m_highest/m_n; y = m_highest%m_n; }
    else{ x = m_n-1; y = m_m-1; }
    int i=m_ALmid-1,j=m_ALsize-1;
    while( !!x && !!y ){                                                                fdbk("\tTracing from <%d,%d>{%c,%c} :...",x,y,m_sqA[x-1],m_sqB[y-1]);
        cur =  m_mat->gt(x,y);                                                          fdbk("\n\t\t-----------\n\t\t| %d | %d |\n\t\t-----------\n\t\t| %d | %d <",m_mat->gt(x-1,y-1),m_mat->gt(x-1,y),m_mat->gt(x,y-1),cur);
        if( !!(x+y) && cur==m_mat->gt(x-1,y-1)+(match(x,y)*m_SM.match+(!(match(x,y))*m_SM.mismatch)) ) {    fdbk("...Heading Diagonally (%s)\n\t\t------\n",match(x,y)?"MATCH":"MISMATCH");
            m_AL[i] = m_sqA[x-1];                                                       fdbk("\t\tAssigning m_AL[%d] = \'%c\' (From sqA[%d],\'%c\'in\'%s\')\n",i,m_AL[i],(x-1),m_sqA[y-1],m_sqA);
            m_AL[j] = m_sqB[y-1];                                                       fdbk("\t\tAssigning m_AL[%d] = \'%c\' (From sqB[%d],\'%c\'in\'%s\')\n",j,m_AL[j],(y-1),m_sqB[y-1],m_sqB); 
            x--;
            y--;                                       
        } else if( !!(x) && cur==m_mat->gt(x,y-1)+m_SM.gap ){                           fdbk("...Heading Left (GAP) \n\t\t------\n");
            m_AL[i] = '-';                                                              fdbk("\t\tAssigning m_AL[%d] = \'%c\'\n",i,m_AL[i]);
            m_AL[j] = m_sqB[y-1];                                                       fdbk("\t\tAssigning m_AL[%d] = \'%c\' (From sqB[%d],\'%c\'in\'%s\')\n",j,m_AL[j],(y-1),m_sqB[y-1],m_sqB); 
            y--;                                               
        } else if( !!(y) && cur==m_mat->gt(x-1,y)+m_SM.gap ){                           fdbk("...Heading Up (GAP) \n\t\t------\n");
            m_AL[i] = m_sqA[x-1];                                                       fdbk("\t\tAssigning m_AL[%d] = \'%c\' (From sqA[%d],\'%c\'in\'%s\')\n ",i,m_AL[i],(x-1),m_sqA[x-1],m_sqA);
            m_AL[j] = '-';                                                              fdbk("\t\tAssigning m_AL[%d] = \'%c\'\n",j,m_AL[j]); 
            x--;
        } else {                                                                        fdbk("...ERROR: No Case Found\n");
            break;
        }                                                           
        i--;j--;                                                                        fdbk("\t\tCurrent Alignment : \"%s\"\n\n",m_AL);
    }
    while ( !(m_is_local) && !!(x+y) ){
        if(!!(y)) {
            m_AL[i] = '-';                                                              fdbk("\t\tAssigning m_AL[%d] = \'%c\'\n",i,m_AL[i]);
            m_AL[j] = m_sqB[y-1];                                                       fdbk("\t\tAssigning m_AL[%d] = \'%c\' (From sqB[%d],\'%c\'in\'%s\')\n",j,m_AL[j],(y-1),m_sqB[y-1],m_sqB); 
            y--;                                               
        } else if(!!(x)) {
            m_AL[i] = m_sqA[x-1];                                                       fdbk("\t\tAssigning m_AL[%d] = \'%c\' (From sqA[%d],\'%c\'in\'%s\')\n ",i,m_AL[i],(x-1),m_sqA[x-1],m_sqA);
            m_AL[j] = '-';                                                              fdbk("\t\tAssigning m_AL[%d] = \'%c\'\n",j,m_AL[j]); 
            x--;
        }
        i--;j--;
    }                                                                                   fdbk("\t\tCurrent Alignment : \"%s\"\n\n",m_AL);
    m_AL[m_ALmid]='\n';
}