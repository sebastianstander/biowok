message(".<DEV>...Entering predict2ndary/tests-CMakeLists.txt...<DEV>.")
add_executable(test_nussinov)
target_sources(test_nussinov PRIVATE nussinov.test.cpp)
target_link_libraries(test_nussinov PRIVATE nussinov_only)
#add_test(nuss_test test_nussinov)
message(".<DEV>...Concluding predict2ndary/tests-CMakeLists.txt...<DEV>.")