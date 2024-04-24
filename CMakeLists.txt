cmake_minimum_required(VERSION 3.8)
include(FetchContent)

project("hive_engine" CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")


add_executable(${PROJECT_NAME} src/main.cpp)

# add hive/files
target_link_libraries(${PROJECT_NAME})
add_subdirectory("src/hive")
add_subdirectory("src/engine")

target_link_libraries(${PROJECT_NAME} PRIVATE Hive AlfaBeta)


FetchContent_Declare(
    gtest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG        "release-1.11.0"
)

FetchContent_MakeAvailable(Gtest)

# testing
add_executable(tests "test/test.cpp")

target_link_libraries(tests gtest gtest_main Hive)
