# External dependencies

# VCPKG
option(USE_VCPKG "Fetch dependencies using the vcpkg package manager" OFF)
if (USE_VCPKG)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")
endif()

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
