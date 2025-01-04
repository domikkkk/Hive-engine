#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP
#pragma once

#include <string>
#include <hive/namespaces.hpp>
#include <iostream>
#include <hive/game.hpp>
#include <HiveAI>


class Protocol {
public:
    void create_game() noexcept;
    std::string get_info() noexcept;
    void move(const struct Move_parameters &move);
    void unmove(const int &n) noexcept;
    std::string get_notation(const std::string &piece, const Coords &where) noexcept;
    std::string get_valid_moves() noexcept;
    std::string get_best_move(const int &n=0) noexcept;
    float get_mark() noexcept {
        return this->engine.evaluate();
    }


private:
    Game game;
    AlfaBeta engine;
    int n_game = 0;
};

typedef struct Command {
    std::string command_type;
    std::string arguments;
    void execute(Protocol &protocol);
    friend std::istream &operator>>(std::istream &is, Command &command);
} Command;


typedef struct _BestMove_Arguments {
    int depth = 0;
    int time = 0;
    bool is_time = false;
} _BestMove_Arguments;


Move_parameters create_move(const std::string &parameters) noexcept;

_BestMove_Arguments get_info_from_BestMove(const std::string &arguments) noexcept;


#endif
