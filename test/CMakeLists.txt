
add_executable(tst_scatter tst_scatter.cpp)
target_link_libraries(tst_scatter padscatter GTest::gtest GTest::gtest_main)
#target_compile_definitions(tst_scatter PRIVATE -DQT_NO_KEYWORDS)
add_test(NAME tst_scatter COMMAND tst_scatter)
