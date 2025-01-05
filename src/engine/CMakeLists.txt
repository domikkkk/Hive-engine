cmake_minimum_required( VERSION 3.8)

add_library(AlfaBeta STATIC "alfabeta.cpp" "evaluations.cpp" "transpositionTable.cpp")

target_include_directories(AlfaBeta PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
