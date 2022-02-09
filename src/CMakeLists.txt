# Interface Library
add_library(padscatter INTERFACE)
target_link_libraries(padscatter INTERFACE TBB::tbb Threads::Threads OpenMP::OpenMP_CXX range-v3)
target_include_directories(
  padscatter
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/padscatter
  INTERFACE ${PROJECT_SOURCE_DIR}/dependencies/umesimd
)

# Benchmarks
## benchmark library
add_library(padbench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/benchmarks.cpp)
target_link_libraries(padbench PUBLIC padscatter benchmark::benchmark)
target_compile_options(padbench PRIVATE -Wno-unused-function)

## Add costum add_benchmark
set(BENCHMARKS_AVAIL_TMP "")
function(add_my_benchmark targetName)
  add_executable(${targetName} ${ARGN})
  target_link_libraries(${targetName} PRIVATE padscatter benchmark::benchmark_main padbench)
  set(BENCHMARKS_AVAIL_TMP "${BENCHMARKS_AVAIL_TMP} ${targetName}" PARENT_SCOPE)
endfunction()

## Add Benchmarks here
add_my_benchmark(serialBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/serial.cpp)
add_my_benchmark(serialUnrolledLoopBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/serial_unrolled_loop.cpp)
add_my_benchmark(serialSimdBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/serial_simd.cpp)
add_my_benchmark(serialNTStoreBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/serial_ntstore.cpp)
add_my_benchmark(serialScanBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/serial_scan.cpp)
add_my_benchmark(serialBinningBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/serial_binning.cpp)
add_my_benchmark(stlBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/stl.cpp)
add_my_benchmark(tbbSimpleBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/tbb_simple.cpp)
add_my_benchmark(tbbPresortBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/tbb_presort.cpp)
add_my_benchmark(tbbScanBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/tbb_scan.cpp)
add_my_benchmark(tbbBinningBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/tbb_binning.cpp)
add_my_benchmark(ompParallelBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/omp.cpp)
add_my_benchmark(ompSerialBench ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/serial_omp_simd.cpp)

## Add costum add_benchmark
function(add_my_opt targetName)
  add_executable(${targetName} ${ARGN})
  target_link_libraries(${targetName} PRIVATE padscatter benchmark::benchmark_main padbench)
  target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks)
endfunction()

## Add optimization here
add_my_opt(serialScanOpt ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/optimization/serial_scan.cpp)
add_my_opt(tbbSimpleOpt ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/optimization/tbb_simple.cpp)
add_my_opt(tbbScanOpt ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/optimization/tbb_scan.cpp)

# Add to chached variable
set(BENCHMARKS_AVAIL ${BENCHMARKS_AVAIL_TMP} CACHE INTERNAL ${BENCHMARKS_AVAIL_TMP})
