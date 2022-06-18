
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
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} DESCRIPTION ${PROJECT_DESCRIPTION} LANGUAGES CXX)

# Build Libraries
add_library(utils INTERFACE ../util/FeedbackMacro.hpp ../util/TypeAbbreviations.hpp ../util/BiowokHelperFunctions.hpp)

# Construct Executable
add_subdirectory()
set(INCLUDE aligner.hpp)
set(SOURCES tester.cpp aligner.hpp)
add_executable( ${PROJECT_NAME} ${INCLUDE} ${SOURCES} )
target_link_libraries( ${PROJECT_NAME} aligner_utils )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(  )