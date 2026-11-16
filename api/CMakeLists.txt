cmake_minimum_required(VERSION 3.25)
# The Threads check of the libraries needs a C compiler.
project(icde_api VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Logic without Drogon, so the unit tests need no web server.
add_library(icde_core src/example.cpp src/status.cpp)
target_include_directories(icde_core PUBLIC src)
target_compile_definitions(icde_core PRIVATE ICDE_VERSION="${PROJECT_VERSION}")
target_link_libraries(icde_core PUBLIC JsonCpp::JsonCpp)

add_executable(icde-api src/main.cpp)
target_link_libraries(icde-api PRIVATE icde_core Drogon::Drogon)

enable_testing()
add_executable(icde_tests tests/example_test.cpp tests/status_test.cpp)
target_link_libraries(icde_tests PRIVATE icde_core GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(icde_tests)
