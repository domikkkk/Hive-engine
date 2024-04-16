cmake_minimum_required( VERSION 3.8)

add_library(Board STATIC "board.cpp")

target_include_directories(Board PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
