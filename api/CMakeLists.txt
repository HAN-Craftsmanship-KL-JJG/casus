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
# docs/layers.md explains the rules and how the build checks them.
#
# domein and applicatie must link no vcpkg package.
# vcpkg puts the headers of all packages in one folder,
# so one package would make the Drogon headers reachable as well.

add_library(domein src/domein/Opleiding.cpp)
target_include_directories(domein PUBLIC src/domein)

add_library(applicatie src/applicatie/OpleidingHandler.cpp)
target_include_directories(applicatie PUBLIC src/applicatie)
target_link_libraries(applicatie PUBLIC domein)

add_library(datalaag src/datalaag/PostgresOpleidingRepository.cpp)
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

# Two checks that keep the layer rules above enforced. docs/layers.md explains them.
#
# 1. domein and applicatie link only what the rules allow.
get_target_property(domein_links domein LINK_LIBRARIES)
if(domein_links)
    message(FATAL_ERROR "domein may link nothing, but links: ${domein_links}")
endif()
get_target_property(applicatie_links applicatie LINK_LIBRARIES)
if(NOT applicatie_links STREQUAL "domein")
    message(FATAL_ERROR "applicatie may link only domein, but links: ${applicatie_links}")
endif()

# 2. No include with ../ in it.
# The compiler looks in the folder of the file first, so "../datalaag/X.hpp" would reach a
# header of another layer and skip the include folders.
file(GLOB_RECURSE own_files CONFIGURE_DEPENDS src/*.hpp src/*.cpp tests/*.hpp tests/*.cpp)
foreach(own_file IN LISTS own_files)
    file(STRINGS "${own_file}" relative_includes REGEX "#[ \t]*include[ \t]*[\"<][.][.]/")
    if(relative_includes)
        message(FATAL_ERROR "${own_file}: include a header by its name, without ../")
    endif()
endforeach()
