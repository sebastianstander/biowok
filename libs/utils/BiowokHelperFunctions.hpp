static int len(char* s){
    int n=0;
    while(s[n]!='\0') n++;
    return n;
}
inline int max(const int a,const int b){ 
    return (a>b?a:b); 
}
inline int min(const int a,const int b){ 
    return (a>b?b:a); 
}