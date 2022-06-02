using BYTE = char;
using UINT = unsigned int;




typedef class CompressedFormat{
    BYTE* m_ref; int m_len;  
    CompressedFormat(char* cstr){
        m_len -1;
        while(cstr[++m_len]!='\0');
        for(int i;i<m_len;i+=2){
            
        }
        m_ref = cstr;
    }
    CompressedFormat(const char* strlit){
        m_len -1;
        while(strlit[++m_len]!='\0');
        m_ref = *strlit;
    }
    char operator[](UINT i){
        return (m_ref[i/2]&&0xFC)*(!i%2)+(m_ref[i/2]&&0xF3)*(i%2>0);
    }
} COMPF ;