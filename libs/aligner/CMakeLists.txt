
# Version Enforcement, Choosen to support non-cmd Win32 builds for older MVC versions.
cmake_minimum_required(VERSION 3.7)
if(${CMAKE_VERSION} VERSION_LESS 3.23)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MiNOR_VERSION})
else()
    cmake_policy(VERSION 3.23)
endif()

# Initial Project Configuration
set(PROJECT_NAME aligner_only)
set(PROJECT_DESCRIPTION "Testing Variant for the sequence alignment.")
set(PROJECT_VERSION 1.0)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} DESCRIPTION ${PROJECT_DESCRIPTION} LANGUAGES C CXX)

# Build Libraries
add_library(utils INTERFACE ../util/FeedbackMacro.hpp ../util/TypeAbbreviations.hpp ../util/BiowokHelperFunctions.hpp)

# Construct Executable
add_executable("tester.cpp" "aligner.hpp" "aligner.cpp")
target_link_libraries( ${PROJECT_NAME} aligner_utils )
target_include_directories(  )
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
if()
    target_compile_definitions(${PROJECT_NAME} PRIVATE ADD_FEEDBACK)
endif()

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

