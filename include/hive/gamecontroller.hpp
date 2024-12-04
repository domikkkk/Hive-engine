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
    bool is_finished() noexcept;
    bool validateQueens() const noexcept;
    bool can_move_on_board() const noexcept;
    std::vector<Coords> legal_piece_placement() noexcept;
    void move(const std::string &piece, const Coords &c);
    void prepare_pieces() noexcept;
    std::unordered_map<std::string, Coords> &get_pieces() noexcept;
    hive::Board &get_board() noexcept;
    
private:
    Color current = WHITE;
    hive::Board board;
    int moves_counter = 0;
    std::unordered_map<std::string, Coords> insects;
};



Color color_from_string(const char &c) noexcept;


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
