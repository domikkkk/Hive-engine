#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <hive/gamecontroller.hpp>
#include <hive/namespaces.hpp>

class Game {
public:
    Game() noexcept = default;


private:
    Controller controller;
    State state = State::NOTSTARTED;
};



#endif
