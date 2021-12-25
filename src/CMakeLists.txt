# Interface Library
add_library(padscatter INTERFACE)
target_link_libraries(padscatter INTERFACE TBB::tbb Threads::Threads)
target_include_directories(padscatter
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/padscatter)

# Benchmarks
## benchmark library
add_library(padbench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/benchmarks.cpp)
target_link_libraries(padbench PUBLIC padscatter benchmark::benchmark)
target_compile_options(padbench PRIVATE -Wno-unused-function)

## Add costum add_benchmark
function(add_my_benchmark targetName)
        add_executable(${targetName} ${ARGN} )
        target_link_libraries(${targetName} PRIVATE padscatter benchmark::benchmark padbench)
        if(NOT DEFINED LOCAL)
                message(STATUS "Building with compiler machine features for target ${targetName}")
                target_compile_options(${targetName} PRIVATE -xSKYLAKE_AVX512)
        endif()
endfunction()

## Add Benchmarks here
add_my_benchmark(serialSimple ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/serial_simple.cpp)
add_my_benchmark(stdSimple ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/std_simple.cpp)
add_my_benchmark(tbbSimple ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/tbb_simple.cpp)
