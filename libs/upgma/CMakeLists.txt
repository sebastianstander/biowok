message(".<DEV>...Entering upgma-CMakeLists.txt...<DEV>.")

# CMAKE Version Enforcement
#   Choosen to support non-cmd Win32 builds for older MVC versions.
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
if(${CMAKE_VERSION} VERSION_LESS 3.23)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.23)
endif()

# Project Declaration
project("upgma_module" 
        VERSION 0.1.0 
        DESCRIPTION "An attempt to build my own lightweight, efficent version of phylogentic tree construction via the UPGMA algorithm as part of a starter SENG project."
        LANGUAGES C CXX )
message(".<DEV>...project source directory:<${PROJECT_SOURCE_DIR}>...<DEV>.")

# Enable CTest (Requires more exploration)
include(CTest)
enable_testing()

# Compiler Options
if(MSVC)
    add_compile_options(/W4 /WX)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,--verbose")     #Non-Clang
    message(".<DEV>...compiling on MSVC...<DEV>.")
else()
    add_compile_options(-W -Wall -pedantic -ferror-limit=100 -std=c++17 -v)
    set(CMAKE_EXE_LINKER_FLAGS "-Xlinker -v -v")   #Clang, addtionally displaying how the liner is called
    message(".<DEV>...compiling on GCC/Clang...<DEV>.")
    message(".<DEV>...options activated:<${COMPILE_OPTIONS}>...<DEV>.") 
endif()
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# Compile "UPGMA-Only" Library
add_library(upgma_only STATIC)
target_sources(upgma_only PRIVATE src/upgma.cpp)
get_filename_component(PARENT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_include_directories(     
    upgma_only
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC ${PARENT_DIRECTORY}/utils )
target_compile_definitions(upgma_only PRIVATE ADD_FEEDBACK)

message(".<DEV>...parent directory : ${PARENT_DIRECTORY}...<DEV>.") 

# Compile "Aligner-Test" Tester Application
add_subdirectory(tests)

message(".<DEV>...Concluding upgma-CMakeLists.txt...<DEV>.")