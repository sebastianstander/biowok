# Biowok

## Goal
Created purely for learning reasons. The primary goal was to translate each algorithm into both streamlined, fast C/C++ implementations capable of handling somewhat high volumes of throughput, and verbose, visualization-friendly implementations capable of being diplayed using modern web tools. 

Currently, the objective is to minimize the use of the C++ Standard Library or STL and write mostly just in the core language if possible.

## Checklist
    Modules
        predict2ndy 
            Uses Nussinov's algorithm to predict
            RNA secondary structure.
            - Basic Nussinov (Restructuring with new Utilities)
            - Min-Energy Nussinov (Planned)
            - Nussinov-Scoring (Planned)
            - Visualization (Planned)
        aligner
            - Needleman-Wunsch (Restructuring with new Utilities)
            - Smith-Waterman (Restructuring with new Utilities)
            - Alignment-Ranking (Planned)
            - Visualization (Planned)
        seqprob
            - Forward-Backward (Partially Implemented)
            - Viterbi (Partially Implemented)
            - Posterior (Partially Implemented)
            - Baum-Welch (Partially Implemented)
            - Visualization (Planned)
        upgma
            Uses unweighted pair group with arithmetic mean to create phenetic trees from DNA sequences. 
            - UPGMA (Refining)
            - Visualization (Planned)
    Tools
        - Sequence Compression Format (Partially Implemented)
        - JSON Output Stream (Partially Implemented)
        - Unit Testing (Planned)
        
## References List
    References :
    - Pitchfork Documentation  
        -   https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs#tld.src
    - Pitchfork Example?       
        -   https://github.com/vector-of-bool/pitchfork/blob/develop/tests/compare_fs.cpp
    - Modern CMake Tutorials   
        -   https://www.siliceum.com/en/blog/post/cmake_01_cmake-basics
        -   https://crascit.com/professional-cmake/
        -   https://www.internalpointers.com/post/modern-cmake-beginner-introduction
