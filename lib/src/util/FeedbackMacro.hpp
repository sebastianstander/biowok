#if ADD_FEEDBACK==1
	#include <cstdio>
	#define fdbk(...) fprintf ( stdout , __VA_ARGS__ );	
	#define test_pass(nd)\
		for(auto i=0;i<nd.len;i++){\
			for(auto j=0;j<nd.len;j++) fdbk( "%d ",nussinov::gmat(nd,i,j));\
			fdbk("\n");\
		}fdbk("\n");   
#else
	#define test_pass(nd)
	#define fdbk(...)
#endif