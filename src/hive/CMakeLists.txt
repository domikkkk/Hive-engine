cmake_minimum_required( VERSION 3.8)

add_library(Hive STATIC "board.cpp" "moves.cpp" "coordinates.cpp" "game.cpp" "gamecontroller.cpp" "protocol.cpp")

target_include_directories(Hive PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_SOURCE_DIR})
