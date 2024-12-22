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
    const std::string get_valid_moves() noexcept;
    void player_move(const struct Move_parameters &move);
    void undo(const int &n = 1) noexcept;
    void update() noexcept;

    void set_valid_moves(std::unordered_map<std::string, std::vector<Coords>> &valid_moves) noexcept;

    Controller &get_controller() noexcept;

private:
    Controller controller;
    std::string gameType = GameType::base;
    State state = State::NOTSTARTED;
    std::vector<std::string> moves;
};


struct Move_parameters {
    std::string what_piece;
    std::string next_to_piece;
    Directions direction = Directions::DEFAULT;
    std::string str="";
};


#endif
