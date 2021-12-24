find_package(GTest)

# Custom add_my_test
function(add_my_test targetName)
        add_executable(${targetName} ${ARGN})
        target_link_libraries(${targetName} PRIVATE padscatter GTest::GTest GTest::gtest_main)
        gtest_add_tests(TARGET ${targetName}
                EXTRA_ARGS ""
                AUTO
                TEST_SUFFIX .test
        )
endfunction()

add_my_test(tst_scatter tst_scatter.cpp)
