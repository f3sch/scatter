configure_file(run.sh.in run.sh USE_SOURCE_PERMISSIONS @ONLY)
configure_file(plot.py plot.py USE_SOURCE_PERMISSIONS COPYONLY)

message(STATUS "Tests available: ${TESTS_AVAIL}")
message(STATUS "Benchmarks available: ${BENCHMARKS_AVAIL}")
