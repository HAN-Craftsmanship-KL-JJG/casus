cmake_minimum_required(VERSION 3.25)
# The Threads check of the libraries needs a C compiler.
project(icde_api VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# One library per layer of the chapter Architectuur.
# target_link_libraries sets which layer may use which, so a wrong #include fails the build.
# Each library publishes only its own folder, so a layer cannot reach headers it does not link.
#
# domein and applicatie must link no vcpkg package.
# vcpkg puts the headers of all packages in one folder,
# so one package would make the Drogon headers reachable as well.

add_library(domein src/domein/Opleiding.cpp)
target_include_directories(domein PUBLIC src/domein)

add_library(applicatie src/applicatie/OpleidingHandler.cpp)
target_include_directories(applicatie PUBLIC src/applicatie)
target_link_libraries(applicatie PUBLIC domein)

add_library(datalaag src/datalaag/MockOpleidingRepository.cpp)
target_include_directories(datalaag PUBLIC src/datalaag)
target_link_libraries(datalaag PUBLIC domein PRIVATE Drogon::Drogon)

add_library(rest src/rest/status.cpp)
target_include_directories(rest PUBLIC src/rest)
target_compile_definitions(rest PRIVATE ICDE_VERSION="${PROJECT_VERSION}")
target_link_libraries(rest PUBLIC applicatie JsonCpp::JsonCpp PRIVATE Drogon::Drogon)

# main.cpp is the only place that knows both rest and datalaag.
add_executable(icde-api src/main.cpp)
target_link_libraries(icde-api PRIVATE rest datalaag Drogon::Drogon)

enable_testing()
add_executable(icde_tests
    tests/domein/opleiding_test.cpp
    tests/applicatie/opleiding_handler_test.cpp
    tests/rest/status_test.cpp)
target_link_libraries(icde_tests PRIVATE rest datalaag GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(icde_tests)
