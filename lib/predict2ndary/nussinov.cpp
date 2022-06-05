/**
 * @file nuss.cpp
 * @author Sebastian Stander (sebastianstander@github.com)
 * @brief An implementation for Nuess's streamlined version of nussinov's algorthim.
 * @version 0.1
 * @date 2022-06-02
 * 
 */
#include "nussinov.hpp"
#include <iostream>
/*char* nussinov::compress_sequence(char* fmt,const char* seq,const int n){
    char current;
    int i;
    for(int by=0;by<n/4;by++){
        fmt[by]=0b00000000;
        for(int c=0;c<4;c++){
            i=by*4+c;
            if( !((seq[i]=='A')||(seq[i]=='U')||(seq[i]=='A')||(seq[i]=='A')) )
                return nullptr;
            fmt[by]=fmt[by]+
                    (   (   (seq[i]=='U')*0x01+ 
                            (seq[i]=='G')*0x02+ 
                            (seq[i]=='C')*0x03)
                        <<(c*2));
        }
    }
    fmt[n]='\0';
    return fmt;
}*/
/*void nussinov::build(NussData& nd,const int& m){
	int j,bi=0;
    for(int k=1;k<nd.len;k++) {
		for(int i=0;i<nd.len-k;i++){
			j=i+k;
			if(j-i>=m){
				bi=0;
				for(int t= i;t<j;t++) bi=max(   bi, 
                                                gmat(nd,i,t)+gmat(nd,t+1,j) 
                                            );
                smat(nd,i,j,max(    max( gmat(nd,i+1,j),
                                         gmat(nd,i,j-1)
                                    ), 
                                    max( gmat(nd,i+1,j-1) + is_coupled( (gnuc(nd,i)<<2)+gnuc(nd,j) ),
                                         bi
                                    )    
                                ));
			} else 
                smat(nd,i,j,0);
		}   
	} 
    return;
}*/
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
/*void nussinov::traceback(NussData& nd,int i,int j){
    while(i<j){                                                             fdbk("For nd.mat[");fdbk(i);fdbk("][");fdbk(j);fdbk("]\n");
        if(gmat(nd,i,j)==gmat(nd,i+1,j)){ i++;                              fdbk("\tGoing Left to nd.mat[");fdbk(i-1);fdbk("][");fdbk(j);fdbk("]\n");
        }else if(gmat(nd,i,j)==gmat(nd,i,j-1)){ j--;                        fdbk("\tGoing Down to nd.mat[");fdbk(i);fdbk("][");fdbk(j+1);fdbk("]\n");
        }else if(gmat(nd,i+1,j-1)+is_coupled((gnuc(nd,i)<<2)+gnuc(nd,j))){  fdbk("\tGoing Diag to nd.mat[");fdbk(i+1);fdbk("][");fdbk(j-1);fdbk("]\n");
            nd.fld[i]=41*(i>j)+40*(i<j); nd.fld[j]=40*(i>j)+41*(i<j);       fdbk("\t...Adding Fold to nd.mat[");fdbk(i);fdbk("][");fdbk(j);fdbk("]\n"); 
            i++;j--;
        }else{                                                              fdbk("\tRetracing Bifurication frond.mat[");fdbk(i);fdbk("][");fdbk(j-1);fdbk("]\n");
            for(int k=i+1;k<j;k++){
                if(gmat(nd,i,j)==gmat(nd,i,k)+gmat(nd,k+1,j)) {             fdbk("\tBifuricating Left to[");fdbk(i);fdbk("][");fdbk(k);fdbk("]\n");
                    traceback(nd,i,k);                                      fdbk("\tBifuricating Right to[");fdbk(k+1);fdbk("][");fdbk(j);fdbk("]\n");
                    traceback(nd,k+1,j);
                    break;
                }
            }
        }
    }
    return;
}*/
char* nussinov::predict(char* seq){
    
    // INITIALIZE -- Get the length of the c-string (without using the std or builtin libraries).

    NussData nd;                            
    nd.len=0; 
    while (seq[nd.len]!='\0') nd.len++;     
    fdbk(seq);fdbk(" ");fdbk(nd.len);fdbk("\n\n");
    
    // COMPRESS -- Format the string literal into a compressed, 2 bits per nucleotide, c-string version.

    //char fmt[(nd.len/4)+2];                                                                     // 
    //fmt[(nd.len/4)+1]='\0';                 
    //nd.seq = compress_sequence(fmt,seq,nd.len);     for(int i=0;i<nd.len;i++) fdbk(int(gnuc(nd,i)));


    // BUILD -- Fill in the Distance Matrix according the Nussinov's Algorithm.

    /*int mat[nd.len*nd.len];                                                    
    nd.mat = mat;                           test_pass(nd);
    build(nd,0);                            test_pass(nd);*/
    

    // TRACEBACK -- Traceback through the matrix to detemine & record the RNA Secondary Structure.

    /*char fold[nd.len+1];
    int c=0; 
    while(c<=nd.len) fold[c++]='.'; 
    fold[nd.len]='\0'; 
    nd.fld = fold ;                         fdbk("Structure(Prior) => ");fdbk(nd.fld);fdbk("\n\n");
    traceback(nd,0,nd.len-1);               fdbk("\n                  ");fdbk(seq);fdbk("\n");  
                                            fdbk("Structure(Post)  => ");fdbk(nd.fld);fdbk("\n\n");*/
    
    //fdbk("Recursive Calls = ");fdbk(nd.recur-1);fdbk(" \n\n\n");
    char* isthisusfficentdouchebagcompiler = "VSC wastes my time.";
    return isthisusfficentdouchebagcompiler;//nd.fld;
}
void nussinov::cpp_echo(){
    std::cout<<"I am able to conduct the bare minimum required of me and detect multiple fucking files.\n";
    fdbk("nussinov.cpp is accessible.\n");
}