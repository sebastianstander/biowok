message(".<DEV>...Entering upgma/tests-CMakeLists.txt...<DEV>.")
add_executable(test_upgma)
target_sources(test_upgma PRIVATE upgma.test.cpp)
target_link_libraries(test_upgma PRIVATE upgma_only)
#add_test(upgma_test test_upgma)
message(".<DEV>...Concluding upgma/tests-CMakeLists.txt...<DEV>.")