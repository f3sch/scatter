# External dependencies

# ECMSanitizers
include(ECMEnableSanitizers)
option(ECM_ENABLE "Enable the ECMSanitizers" OFF)
if(ECM_ENABLE)
    set(ECM_ENABLE_SANITIZERS address;leak;undefined CACHE STRING "ECMSanitizers")
    set_property(CACHE ECM_ENABLE_SANITIZERS PROPERTY STRINGS
            address;leak;undefined;fuzzer
            memory;undefined;fuzzer
            thread;undefined;fuzzer
    )
    set(CMAKE_CXX_COMPILER clang++)
endif()
