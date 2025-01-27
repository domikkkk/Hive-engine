#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <hive/gamecontroller.hpp>
#include <hive/namespaces.hpp>

class Game {
public:
    Game() noexcept = default;
    explicit Game(const int &n) : created(n) {};
    void player_move(const struct Move_parameters &move);
    void pass() noexcept;
    void undo(const int &n = 1) noexcept;
    void update() noexcept;
    void new_game() noexcept;

    void set_valid_moves(std::unordered_map<std::string, std::vector<Coords>> &valid_moves) noexcept;

    bool is_finished() noexcept;

    inline Controller &get_controller() noexcept {
        return this->controller;
    }

    inline const std::string &get_gameType() noexcept {
        return this->gameType;
    }

    inline const State &get_gameState() noexcept {
        return this->state;
    }

    inline const std::vector<std::string> &get_moves() noexcept {
        return this->moves;
    }

    inline bool was_created() const noexcept {
        return this->created > 0;
    }

private:
    Controller controller;
    std::string gameType = GameType::base;
    State state = State::NOTSTARTED;
    std::vector<std::string> moves;
    int created = 0;
};


struct Move_parameters {
    std::string what_piece;
    std::string next_to_piece;
    Directions direction = Directions::DEFAULT;
    std::string str="";
};


#endif
