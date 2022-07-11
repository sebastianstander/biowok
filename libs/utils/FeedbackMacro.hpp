#if ADD_FEEDBACK==1
	#include <cstdio>
	#define fdbk(...) fprintf ( stdout , __VA_ARGS__ )	
	#define print_as_matrix_i(m,n,w)\
		for(auto i=0;i<n;i+=w){\
			for(auto j=0;j<w;j++){\
				if(m[i+j]>-1){ fdbk( "  %d ",m[i+j]); }\
				else{ fdbk( " %d ",m[i+j]); }\
			}\
			fdbk("\n");\
		}
	#define print_as_matrix_f(m,n,w)\
		for(auto i=0;i<n;i+=w){\
			for(auto j=0;j<w;j++){\
				if(m[i+j]>-1){ fdbk( "  %f ",m[i+j]); }\
				else{ fdbk( " %f ",m[i+j]); }\
			}\
			fdbk("\n");\
		}
#else
	#define print_as_matrix_d(m,n,w)
	#define print_as_matrix_f(m,n,w)
	#define fdbk(...)
#endif

/*
   GCATGCG.7
   GATTACA.7
   xxxxxGCGxxxxxxACAq
   0123456789A123456
   GCATG-CG.G-ATTACA
   DT.mid = AL[8]
   
*/