# Biowok

# Goal
Created purely for learning reasons. The primary goal was to translate each algorithm into both streamlined, fast c/c++ implementations capable of handling high volumes of throughput, and verbose, visualization friendly implementations capable of being diplayed using
modern web technologies. 

Currently, the objective is to minimize the use of the C++ Standard Library or STL and write mostly just in the core language.

# Checklist
    Modules
        predict2ndy 
            Uses Nussinov's algorithm to predict
            RNA secondary structure.
            - Basic Nussinov (Needs cmake Integration)
            - Min-Energy Nussinov (Planned)
            - Nussinov-Scoring (Planned)
            - Visualization (Planned)
        aligner
            - Needleman-Wunsch (Refining)
            - Smith-Waterman (Refining)
            - Alignment-Scoring (Refining)
            - Visualization (Planned)
        seqprob
            - Forward-Backward (Framed)
            - Viterbi (Planned)
            - Posterior (Plannd)
            - Baum-Welch (Planned)
            - Visualization (Planned)
        upgma
            Uses unweighted pair group with arithmetic mean to create phenetic trees from DNA sequences. 
            - UPGMA (Planned)
            - Visualization (Planned)
    Tools

        - Sequence-Compression ()


# - A practice project to better aid my understanding of Software Development.
References :
    Pitchfork Documentation  -   https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs#tld.src
    Pitchfork Example?       -   https://github.com/vector-of-bool/pitchfork/blob/develop/tests/compare_fs.cpp
    Modern CMake Tutorials   -   https://www.siliceum.com/en/blog/post/cmake_01_cmake-basics         
                                 https://crascit.com/professional-cmake/
                                 https://www.internalpointers.com/post/modern-cmake-beginner-introduction