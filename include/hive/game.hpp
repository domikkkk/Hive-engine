#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <hive/gamecontroller.hpp>
#include <hive/namespaces.hpp>

class Game {
public:
    Game() noexcept = default;
    void change_state(const State &state) noexcept;
    const std::string get_gamestring() const noexcept;
    void move(bool player = true);

private:
    Controller controller;
    std::string gameType = GameType::base;
    State state = State::NOTSTARTED;
};



#endif
