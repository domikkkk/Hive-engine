cmake_minimum_required( VERSION 3.8)

add_library(Pieces STATIC "pieces.cpp")

target_include_directories(Pieces PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
