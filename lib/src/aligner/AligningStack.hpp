struct AligningStackNode {
    int len;
    char* val;
    AligningStackNode* next;
};
class AligningStack {
    AligningStackNode* m_head;
    AligningStackNode* m_prev;
    AligningStackNode* m_top;
    int m_len; int m_blen;
    void* m_buffer;
    public:
        AligningStack(){
            m_len=0;
        }
        AligningStack(int units){
            m_buffer = malloc(sizeof(AligningStackNode)*units);
            m_len=0;
        }        
        ~AligningStack(){
            purge();
        }
        bool is_empty(){
            return (!m_len);
        }
        char* peek(){
            return m_top->val;
        }
        char* pop(){
            char* val = m_top->val;
            free(m_top);
            m_top = m_prev;
            return val;
        }
        void push(char* s){
            int slen=0;
            while(str[slen]!='\0') slen++;
            AligningStackNode* newNode = malloc(sizeof(AligningStackNode));
            newNode->len=slen;
            newNode->val=s;
            newNode->next=m_head;
            m_prev=m_top; 
            m_top->next=newNode;  
            m_top=newNode;
            m_len++;
        } 
        void purge(){
            for(int i=0;i<m_len;i++){
                AligningStackNode* tmp = m_head->next;
                free(m_head);
                m_head = tmp ; 
            } 
        }
};