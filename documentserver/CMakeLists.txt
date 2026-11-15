cmake_minimum_required(VERSION 3.25)
# The Threads check of the libraries needs a C compiler.
project(icde_documentserver VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Logic without Drogon, so the unit tests need no web server.
add_library(icde_convert src/convert.cpp)
target_include_directories(icde_convert PUBLIC src)

add_executable(icde-documentserver src/main.cpp)
target_link_libraries(icde-documentserver PRIVATE icde_convert Drogon::Drogon)

enable_testing()
add_executable(icde_tests tests/convert_test.cpp)
target_link_libraries(icde_tests PRIVATE icde_convert GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(icde_tests)
