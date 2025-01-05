cmake_minimum_required( VERSION 3.8)

add_library(Hive STATIC "zobrist.cpp" "coordinates.cpp" "moves.cpp" "board.cpp" "gamecontroller.cpp" "game.cpp" "protocol.cpp")

target_include_directories(Hive PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_SOURCE_DIR})
