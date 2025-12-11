cmake_minimum_required( VERSION 3.8)

add_library(NNUE STATIC "FullyConnected.cpp" "activations.cpp")

target_include_directories(NNUE PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
