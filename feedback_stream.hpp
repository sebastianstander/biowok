#ifdef ADD_FEEDBACK  
    #include <iostream>
    #define fdbk(cstr) std::cout << cstr
#else 
    #define fdbk(cstr)
#endif