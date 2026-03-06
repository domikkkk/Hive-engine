cmake_minimum_required( VERSION 3.8)

add_library(NNUE STATIC "FullyConnected.cpp" "activations.cpp" "ndarray.cpp" "sequential.cpp" "loss.cpp")

set_target_properties(NNUE PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_include_directories(NNUE PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
