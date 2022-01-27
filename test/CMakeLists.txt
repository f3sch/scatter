find_package(GTest)

# Custom add_my_test
set(TESTS_AVAIL_TMP "")
function(add_my_test targetName)
  add_executable(${targetName} ${ARGN})
  target_link_libraries(${targetName} PRIVATE padscatter padbench GTest::GTest GTest::gtest_main)
  target_include_directories(${targetName} PRIVATE ${CMAKE_SOURCE_DIR}/src/benchmarks)
  gtest_add_tests(
    TARGET ${targetName}
    EXTRA_ARGS ""
    AUTO
    TEST_SUFFIX .test
  )
  set(TESTS_AVAIL_TMP "${TESTS_AVAIL_TMP} ${targetName}" PARENT_SCOPE)
endfunction()

# Add test here
add_my_test(tst_scatter tst_scatter.cpp)
add_my_test(tst_bench tst_benchmark.cpp)

# Add to cached variable
set(TESTS_AVAIL ${TESTS_AVAIL_TMP} CACHE INTERNAL ${TESTS_AVAIL_TMP})
