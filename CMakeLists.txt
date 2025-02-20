cmake_minimum_required(VERSION 3.8)
include(FetchContent)

project("hive_engine" CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -g -O3 -ffast-math")

if(${DEBUG})
    add_compile_definitions(DEBUG)
endif()

if(${INFO})
    add_compile_definitions(INFO)
endif()

# add hive/files
add_subdirectory("src/hive")
add_subdirectory("src/engine")

set(DECORATORS_HPP "include/decorators.hpp")


add_executable(${PROJECT_NAME} src/main.cpp ${DECORATORS_HPP})
target_link_libraries(${PROJECT_NAME} PUBLIC Hive AlfaBeta)


FetchContent_Declare(
    gtest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG        "release-1.11.0"
)

FetchContent_MakeAvailable(Gtest)

# testing
add_executable(tests "test/test.cpp")

target_link_libraries(tests gtest gtest_main Hive)
