using UINT = unsigned int;
namespace bwok_cstr {
    static UINT glen( char* s ){
        UINT n=0;
        while(s[n]!='\0') n++;
        return n;
    }
    static void initstr( char* s , int n , char to ){
        s[n]='\0';
        while(n!=-1) s[n--] = to ;
        return;
    }
}