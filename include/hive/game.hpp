#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <hive/gamecontroller.hpp>
#include <hive/board.hpp>

class Game {
public:
    Game() noexcept = default;


private:
    Controller<hive::Board, Coords> controller;
    hive::Board board;
};



#endif
