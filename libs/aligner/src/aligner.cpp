#include "../include/aligner.hpp"
using namespace aligner;                     
void aligner::build( AlignData& DT, const bool is_local ){
    int cur,greatest=-1;
    for(int x=0;x<DT.ht;x++) setm(DT,x,0,x*DT.Gscr*(!is_local));
    for(int y=1;y<DT.wd;y++) setm(DT,0,y,y*DT.Gscr*(!is_local));
    for(int x=1;x<DT.ht;x++){
        for(int y=1;y<DT.wd;y++){
            cur = calculate_entry(DT,x,y);
            setm(DT,x,y,max(cur,cur*(!is_local)));
            DT.highest = greatest>cur?DT.highest:(y*DT.wd)+x;
        }
    } 
    return;
}
UINT aligner::get_alignment_size( AlignData& DT, const bool is_local ){
    int x,y,cur;                                                    fdbk("\n\tConducting Initial Trace to gage Alignment String Size :...\n");
    if(is_local){ x = DT.highest/DT.wd; y = DT.highest%DT.wd; } 
    else{ x = DT.wd-1; y = DT.ht-1; }                  
    UINT gap_count = 0;
    DT.ALmid = DT.wd-1;
    while( !!(x) && !!(y) ){                                        fdbk("\tTracing from <%d,%d>{%c,%c} :...",x,y,DT.sqA[x-1],DT.sqB[y-1]);
        cur=getm(DT,x,y);                                           fdbk("\n\t\t-----------\n\t\t| %d | %d |\n\t\t-----------\n\t\t| %d | %d <",getm(DT,x-1,y-1),getm(DT,x-1,y),getm(DT,x,y-1),cur);
        if( !!(x+y) && cur==getm(DT,x-1,y-1)+
                       ( match(DT,x,y)*DT.Xscr+
                        (!(match(DT,x,y))*DT.Oscr) )) {             fdbk("...Heading Diagonally (%s)\n",match(DT,x,y)?"MATCH":"MISMATCH");
            x--; y--;
        } else if( !!(x) && cur==getm(DT,x,y-1)+DT.Oscr ) {         fdbk("...Heading Left (GAP) \n");
            gap_count++; DT.ALmid++; y--;
        } else if( !!(y) && cur==getm(DT,x-1,y)+DT.Oscr ) {         fdbk("...Heading Up (GAP) \n");
            gap_count++; x--;
        } else {                                                    fdbk("...ERROR: No Case Found\n"); 
            break; 
        }                                                           fdbk("\t\t------\n");
    }
    while ( !(is_local) && !!(x+y) ){                               fdbk("\tTracing from <%d,%d>{%c,%c} :...",x,y,DT.sqA[x-1],DT.sqB[y-1]);
        if(!!(y)) {                                                 fdbk("...Heading Left (GAP) \n");                  
            gap_count++; DT.ALmid++; y--;                          
        } else if(!!(x)) {                                          fdbk("...Heading Up (GAP) \n");
            gap_count++; x--;
        }                                                           fdbk("\t\t------\n");
    }   
    return gap_count+(DT.ht-1)+(DT.wd-1)+1;
}
void aligner::traceback( AlignData& DT, const bool is_local ){
    int x,y,cur;
    for(int i=0;i<DT.ALsize+1;i++) DT.AL[i]='_';
    DT.AL[DT.ALsize]='\0';
    DT.AL[DT.ALmid]='.';
    if(is_local){ x = DT.highest/DT.wd; y = DT.highest%DT.wd; }
    else{ x = DT.wd-1; y = DT.ht-1; }
    int i=DT.ALmid-1,j=DT.ALsize-1;
    while( !!x && !!y ){                                            fdbk("\tTracing from <%d,%d>{%c,%c} :...",x,y,DT.sqA[x-1],DT.sqB[y-1]);
        cur=getm(DT,x,y);                                           fdbk("\n\t\t-----------\n\t\t| %d | %d |\n\t\t-----------\n\t\t| %d | %d <",getm(DT,x-1,y-1),getm(DT,x-1,y),getm(DT,x,y-1),cur);
        if( !!(x+y) && cur==getm(DT,x-1,y-1)+(match(DT,x,y)*DT.Xscr+(!(match(DT,x,y))*DT.Oscr)) ) {    fdbk("...Heading Diagonally (%s)\n\t\t------\n",match(DT,x,y)?"MATCH":"MISMATCH");
            DT.AL[i] = DT.sqA[x-1];                                 fdbk("\t\tAssigning DT.AL[%d] = \'%c\' (From sqA[%d],\'%c\'in\'%s\')\n",i,DT.AL[i],(x-1),DT.sqA[y-1],DT.sqA);
            DT.AL[j] = DT.sqB[y-1];                                 fdbk("\t\tAssigning DT.AL[%d] = \'%c\' (From sqB[%d],\'%c\'in\'%s\')\n",j,DT.AL[j],(y-1),DT.sqB[y-1],DT.sqB); 
            x--;
            y--;                                       
        } else if( !!(x) && cur==getm(DT,x,y-1)+DT.Oscr ){          fdbk("...Heading Left (GAP) \n\t\t------\n");
            DT.AL[i] = '-';                                         fdbk("\t\tAssigning DT.AL[%d] = \'%c\'\n",i,DT.AL[i]);
            DT.AL[j] = DT.sqB[y-1];                                 fdbk("\t\tAssigning DT.AL[%d] = \'%c\' (From sqB[%d],\'%c\'in\'%s\')\n",j,DT.AL[j],(y-1),DT.sqB[y-1],DT.sqB); 
            y--;                                               
        } else if( !!(y) && cur==getm(DT,x-1,y)+DT.Oscr ){          fdbk("...Heading Up (GAP) \n\t\t------\n");
            DT.AL[i] = DT.sqA[x-1];                                 fdbk("\t\tAssigning DT.AL[%d] = \'%c\' (From sqA[%d],\'%c\'in\'%s\')\n ",i,DT.AL[i],(x-1),DT.sqA[x-1],DT.sqA);
            DT.AL[j] = '-';                                         fdbk("\t\tAssigning DT.AL[%d] = \'%c\'\n",j,DT.AL[j]); 
            x--;
        } else {                                                    fdbk("...ERROR: No Case Found\n");
            break;
        }                                                           
        i--;j--;                                                    fdbk("\t\tCurrent Alignment : \"%s\"\n\n",DT.AL);
    }
    while ( !(is_local) && !!(x+y) ){
        if(!!(y)) {
            DT.AL[i] = '-';                                         fdbk("\t\tAssigning DT.AL[%d] = \'%c\'\n",i,DT.AL[i]);
            DT.AL[j] = DT.sqB[y-1];                                 fdbk("\t\tAssigning DT.AL[%d] = \'%c\' (From sqB[%d],\'%c\'in\'%s\')\n",j,DT.AL[j],(y-1),DT.sqB[y-1],DT.sqB); 
            y--;                                               
        } else if(!!(x)) {
            DT.AL[i] = DT.sqA[x-1];                                 fdbk("\t\tAssigning DT.AL[%d] = \'%c\' (From sqA[%d],\'%c\'in\'%s\')\n ",i,DT.AL[i],(x-1),DT.sqA[x-1],DT.sqA);
            DT.AL[j] = '-';                                         fdbk("\t\tAssigning DT.AL[%d] = \'%c\'\n",j,DT.AL[j]); 
            x--;
        }
        i--;j--;
    }                                                               fdbk("\t\tCurrent Alignment : \"%s\"\n\n",DT.AL);
    DT.AL[DT.ALmid]='\n';
}
char* aligner::align( char* seqA,char* seqB,const bool is_local,
                      const int gap_score,const int match_score,const int mismatch_score){
    AlignData DT;                                   fdbk("Initial Alignment Data :\n");
    DT.Gscr = gap_score;
    DT.Xscr = match_score;
    DT.Oscr = mismatch_score;                       fdbk("\tScore Model in Use : \n\t\t-GAP = %d\n\t\t-MATCH = %d\n\t\t-MISS = %d\n",DT.Gscr,DT.Xscr,DT.Oscr);
    DT.sqA = seqA;                                  fdbk("\tSequence A : \"%s\"\n",DT.sqA);
    DT.wd = len(seqA)+1;                            fdbk("\tLength of A / Matrix Width : \"%d\"\n",DT.wd);
    DT.sqB = seqB;                                  fdbk("\tSequence B : \"%s\"\n",DT.sqB);
    DT.ht = len(seqB)+1;                            fdbk("\tLength of B / Matrix Height : \"%d\"\n",DT.ht);
    int mat[DT.ht*DT.wd]; DT.m = mat;               print_as_matrix(DT.m,DT.ht*DT.wd,DT.wd);
    build(DT,is_local);                             print_as_matrix(DT.m,DT.ht*DT.wd,DT.wd);                  
    DT.ALsize = get_alignment_size(DT,is_local);    fdbk("\tLength of first half of Alignment : \"%d\"\n",DT.ALmid);
    char algnmt[DT.ALsize+1]; DT.AL = algnmt;       fdbk("\tLength of Alignment : \"%d\"\n",DT.ALsize);
    traceback(DT,is_local);                         fdbk("Final Alignment :... \n%s\n\n",DT.AL);
    return DT.AL;
}