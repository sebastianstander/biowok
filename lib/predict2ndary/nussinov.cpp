/**
 * @file nuss.cpp
 * @author Sebastian Stander (sebastianstander@github.com)
 * @brief An implementation for Nuess's streamlined version of nussinov's algorthim.
 * @version 0.1
 * @date 2022-06-02
 * 
 */
#include "nussinov.hpp"
#if ADD_FEEDBACK==1
	#include <cstdio>
	#define fdbk(...) fprintf ( stdout , __VA_ARGS__ );	
	#define test_pass(nd)\
		for(int i=0;i<nd.len;i++){\
			for(int j=0;j<nd.len;j++) fdbk( "%d ",nussinov::gmat(nd,i,j));\
			fdbk("\n");\
		}fdbk("\n");   
#else
	#define test_pass(nd)
	#define fdbk(...)
#endif
char* nussinov::compress_sequence(char* fmt,const char* seq,const int n){
    char current;                       fdbk("Compressing Sequence:...\n");
    int i;
    for(int by=0;by<(n/4)+1;by++){ 
        fmt[by]=0b00000000;             fdbk("\tFor quad-batch %d :...\n",by);
        for(int c=0;c<4&&((by*4)+c)<n;c++){
            i=by*4+c;                   fdbk("\t\tFor item %d (\'%c\') : Eval= %d, Byte=",(by*4)+c,seq[i],!((seq[i]=='A')||(seq[i]=='U')||(seq[i]=='G')||(seq[i]=='C')));
            if( !((seq[i]=='A')||(seq[i]=='U')||(seq[i]=='G')||(seq[i]=='C')) ) return nullptr;
            fmt[by] = fmt[by]+((   (seq[i]=='U')*0b01+ 
                                   (seq[i]=='G')*0b10+ 
                                   (seq[i]=='C')*0b11)
                        <<((3-c)*2));      
             fdbk("%x :...\n",fmt[by]);
        }
        fdbk("\t%02X\n",fmt[by]);
    }
    fmt[n]='\0';
    return fmt;
}
void nussinov::build(NussData& nd,const int& m){
	int j,bi=0;                                                                 fdbk("Building Matrix:...\n");
    while(bi<nd.len*nd.len)nd.mat[bi++]=0;                                      fdbk("\n\n\"Cleaned\" Matrix:\n\n"); test_pass(nd);
    for(int k=1;k<nd.len;k++) {         
		for(int i=0;i<nd.len-k;i++){
			j=i+k;                                                              fdbk("\t for entry[%i][%d]: ",i,j);
			if(j-i>=m){
				bi=0;                                                           fdbk("condition met(%d-%d>=%d): ",j,i,m);
				for(int t= i;t<j;t++) bi=max(bi,gmat(nd,i,t)+gmat(nd,t+1,j));   fdbk("bifur=%d \n",bi);
                fdbk("\t\tm[%d,%d] = max( m[%d,%d](%d) , m[%d,%d](%d) , m[%d,%d](%d+%d) , bi(%d) )\n",i,j,i+1,j,gmat(nd,i+1,j),i,j-1,gmat(nd,i,j-1),i+1,j-1,gmat(nd,i+1,j-1),is_coupled( (gnuc(nd,i)<<2)+gnuc(nd,j) ),bi);           
                smat(nd,i,j,max(    max( gmat(nd,i+1,j),
                                         gmat(nd,i,j-1)
                                    ), 
                                    max( gmat(nd,i+1,j-1) + is_coupled( (gnuc(nd,i)<<2)+gnuc(nd,j) ),
                                         bi
                                    )    
                                ));                
                fdbk("\t\tindex assigned=%d \n",gmat(nd,i,j));
			} else smat(nd,i,j,0);
		}   
	} 
    return;
}
/*void nussinov::traceback(NussData& nd,int i,int j){
    nd.recur++;
	if( i<j ) {
        fdbk("For nd.mat[");fdbk(i);fdbk("][");fdbk(j);fdbk("]\n");
        if( nd.mat[i][j]==nd.mat[i+1][j] ) {
            fdbk("\tGoing Left to nd.mat[");fdbk(i+1);fdbk("][");fdbk(j);fdbk("]\n");
            traceback( nd , i+1 , j ); 
        } else if( nd.mat[i][j]==nd.mat[i][j-1] ) {
            fdbk("\tGoing Down to nd.mat[");fdbk(i);fdbk("][");fdbk(j-1);fdbk("]\n");
            traceback( nd , i , j-1 ); 

        } else if( nd.mat[i][j]== (nd.mat[i+1][j-1]+is_coupled((nd.seq[i]<<2)+nd.seq[j])) ) {
            fdbk("\tGoing Diag to nd.mat[");fdbk(i+1);fdbk("][");fdbk(j-1);fdbk("]\n");
            fdbk("\t...Adding Fold to nd.mat[");fdbk(i);fdbk("][");fdbk(j);fdbk("]\n");
            nd.fld[i] = 41*(i>j)+40*(i<j) ;
            nd.fld[j] = 40*(i>j)+41*(i<j) ;
			traceback( nd , i+1 , j-1 );
        } else {
            fdbk("\tRetracing Bifurication frond.mat[");fdbk(i);fdbk("][");fdbk(j-1);fdbk("]\n");
            for( int k = i+1 ; k < j ; k++ ) {
				if( nd.mat[i][j]==(nd.mat[i][k]+nd.mat[k+1][j]) ) {
                    fdbk("\tBifuricating Left to[");fdbk(i);fdbk("][");fdbk(k);fdbk("]\n");
					traceback( nd , i , k ); 
                    fdbk("\tBifuricating Right to[");fdbk(k+1);fdbk("][");fdbk(j);fdbk("]\n");
					traceback( nd , k+1 , j ); 
					break; 
				}
			} 
        }
    }
    return;
}*/
void nussinov::traceback(NussData& nd,int i,int j){
    while(i<j){                                                             fdbk("For m[%d,%d]:",i-1,j);
        if(gmat(nd,i,j)==gmat(nd,i+1,j)){ i++;                              fdbk("  Going Left to m[%d,%d]...\n",i-1,j);
        }else if(gmat(nd,i,j)==gmat(nd,i,j-1)){ j--;                        fdbk("  Going Down to m[%d,%d]...\n",i,j+1);
        }else if(gmat(nd,i+1,j-1)+is_coupled((gnuc(nd,i)<<2)+gnuc(nd,j))){  fdbk("  Going Diagonal to m[%d,%d]...\n",i-1,j+1);
            nd.fld[i]=41*(i>j)+40*(i<j); nd.fld[j]=40*(i>j)+41*(i<j);       fdbk("  ...Adding Fold at m[%d,%d]...\n",i,j);
            i++;j--;
        }else{                                                              fdbk("  Retracing Bifurication from m[%d,%d]...\n",i,j);
            for(int k=i+1;k<j;k++){
                if(gmat(nd,i,j)==gmat(nd,i,k)+gmat(nd,k+1,j)) {             fdbk("\tBifuricating Left to m[%d,%d]...\n",i,k);
                    traceback(nd,i,k);                                      fdbk("\tBifuricating Right to m[%d,%d]...\n",k-1,j);
                    traceback(nd,k+1,j);
                    break;
                }
            }
        }
    }
    return;
}
char* nussinov::predict(char* seq){
    
    // INITIALIZE -- Get the length of the c-string (without using the std or builtin libraries).

    NussData nd;                            
    nd.len=0;                                       
    while (seq[nd.len]!='\0') nd.len++;             fdbk("Confirming Sequence:\n\t\"%s\",length=%d\n\n",seq,nd.len);
    
    // COMPRESS -- Format the string literal into a compressed, 2 bits per nucleotide, c-string version.

    char fmt[(nd.len/4)+2];                        
    fmt[(nd.len/4)+1]='\0';                         fdbk("Confirming Formatted Sequence:\n\t\"%s\", len=%d, actual=%lu\n\n",fmt,(nd.len/4+2),sizeof(fmt));
    nd.seq = compress_sequence(fmt,seq,nd.len);     fdbk("Transcribing Formatted Sequence:\n"); for(int i=0;i<nd.len;i++) fdbk("\t- %i: %x\n",i,int(gnuc(nd,i))); fdbk("\n\n");

    // BUILD -- Fill in the Distance Matrix according the Nussinov's Algorithm.

    int mat[nd.len*nd.len];                                                    
    nd.mat = mat;                                   fdbk("\n\nPre-\"Build\" Matrix:\n\n"); test_pass(nd);
    build(nd,0);                                    fdbk("\nPost-\"Build\" Matrix:\n\n"); test_pass(nd);
    

    // TRACEBACK -- Traceback through the matrix to detemine & record the RNA Secondary Structure.

    char fold[nd.len+1];
    int c=0; 
    while(c<=nd.len) fold[c++]='.'; 
    fold[nd.len]='\0'; 
    nd.fld = fold ;                         fdbk("Structure(Prior) => %s\n\n",nd.fld);
    traceback(nd,0,nd.len-1);               fdbk("\n                   %s\nStructure(Post) => %s\n\n",seq,nd.fld);

    
    //fdbk("Recursive Calls = ");fdbk(nd.recur-1);fdbk(" \n\n\n");
    return nd.fld;
}