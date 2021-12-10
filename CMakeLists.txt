cmake_minimum_required(VERSION 3.16)

option(USE_VCPKG "Fetch dependencies using the vcpkg package manager" OFF)

if (USE_VCPKG)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")
endif()

project(pad-scatter)

option(LOCAL "Build for local architecture instead of skylake architecture" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})
include(ECMEnableSanitizers)

add_library(padscatter INTERFACE)
target_compile_features(padscatter INTERFACE cxx_std_20)

target_include_directories(padscatter
    INTERFACE $<INSTALL_INTERFACE:include/quantityland2> $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

set(HEADERS_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/include/padscatter)
message(STATUS "HEADERS_INSTALL_PATH : " ${HEADERS_INSTALL_PATH})


install(TARGETS padscatter EXPORT PadScatter LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include/padscatter)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/ DESTINATION include/padscatter FILES_MATCHING PATTERN "*.h*")
install(EXPORT PadScatter NAMESPACE PadScatter:: DESTINATION lib/cmake/padscatter FILE PadScatterConfig.cmake)


