#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP
#pragma once

#include <hive/namespaces.hpp>
#include <hive/board.hpp>
#include <string>
#include <stdexcept>

class Controller {
public:
    Controller() {this->prepare_pieces();};
    explicit Controller(const hive::Board &board): board(board) {};
    void switch_turn() noexcept;
    const Color &get_player() const noexcept;
    void add_piece(const std::string &piece, const Coords &where) noexcept;
    bool is_finished() noexcept;
    bool validateQueens() const noexcept;
    bool can_move_on_board() const noexcept;
    std::vector<Coords> legal_piece_placement() noexcept;
    void move(const std::string &piece, const Coords &to);
    void prepare_pieces();
    bool check_destination(const Coords &destination);
    std::unordered_map<std::string, Coords> &get_pieces() noexcept;
    hive::Board &get_board() noexcept;
    std::size_t get_turns() const noexcept;
    const Color &get_current() const noexcept;
    Coords find_destination(const std::string &piece, Directions direction) const;
    
private:
    Color current = WHITE;
    hive::Board board;
    int moves_counter = 0;
    std::unordered_map<std::string, Coords> insects;
    std::unordered_map<std::string, bool> insects_off;
};


Color color_from_piece(const char &c) noexcept;
int get_id_from_piece(const std::string &piece) noexcept;


class InvalidMove : public std::exception {
public:
    explicit InvalidMove(const std::string &mess) {
        this->message = "Invalid move: " + mess;
    }

    const char* what() const noexcept override {
        return this->message.c_str();
    }

private:
    std::string message;
};


class PieceNotExisting : public std::exception {
public:
    explicit PieceNotExisting(const std::string& piece) {
        this->message = "Piece " + piece + " does not exist or it's not on the board";
    }

    const char* what() const noexcept override {
        return this->message.c_str();
    }

private:
    std::string message;     // Przechowuje gotowy komunikat błędu
};


#endif
