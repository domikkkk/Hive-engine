#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP
#pragma once

#include <hive/namespaces.hpp>
#include <hive/board.hpp>
#include <string>
#include <stdexcept>

class Controller {
public:
    Controller() = default;
    explicit Controller(const hive::Board &board): board(board) {};
    void switch_turn() noexcept;
    const Color &get_player() const noexcept;
    void add_piece(const std::string &piece, const Coords &where) noexcept;
    bool is_finished(const Color &color) noexcept;
    void move(const std::string &piece, const Coords &c);
    void prepare_pieces() noexcept;
    std::unordered_map<std::string, Coords> &get_map();

private:
    Color current = WHITE;
    hive::Board board;
    int moves_counter = 0;
    std::unordered_map<std::string, Coords> insects;
};


class PieceNotExisting : public std::exception {
public:
    const char* what() const noexcept override {
        return "This piece does not exist";
    }
};



class InvalidMove : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid move";
    }
};


#endif
