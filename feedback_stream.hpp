#ifdef ADD_FEEDBACK  
    #include <iostream>
    #define fdbk(...) std::cout << __VA_ARGS__
#else 
    #define fdbk(...)
#endif