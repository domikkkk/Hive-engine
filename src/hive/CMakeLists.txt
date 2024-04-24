cmake_minimum_required( VERSION 3.8)

add_library(Hive STATIC "board.cpp" "pieces.cpp")

target_include_directories(Hive PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
