#ifndef BESTMOVE_HPP
#define BESTMOVE_HPP
#pragma once

#include <iostream>
#include <hive/coordinates.hpp>


typedef struct EMove {
    std::string piece = "";
    Coords where;

    EMove() = default;
    EMove(const std::string &piece, const Coords &c): piece(piece), where(c) {};
} EMove;


#endif
