#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP
#pragma once

#include <hive/namespaces.hpp>
#include <hive/board.hpp>
#include <string>
#include <stdexcept>
#include <unordered_set>

class Controller {
public:
    Controller() {this->prepare_pieces();};
    explicit Controller(const hive::Board &board): board(board) {};
    const Color &get_player() const noexcept;
    void add_piece(const std::string &piece, const Coords &where) noexcept;
    bool is_finished() noexcept;
    bool validateQueen() const noexcept;
    bool can_move_on_board(const std::string &piece) noexcept;
    void move(const std::string &piece, const Coords &to);
    void engine_move(const std::string &piece, const Coords &to);
    void undo_move() noexcept;
    void prepare_pieces();
    bool check_destination(const Coords &destination);

    inline void switch_turn() noexcept {
        this->current = opposite[this->current];
    }

    inline std::unordered_map<std::string, Coords> &get_pieces() noexcept {
        return this->insects;
    }

    inline std::unordered_set<std::string> &get_hands() noexcept {
        return this->hands;
    }

    inline hive::Board &get_board() noexcept {
        return this->board;
    }

    inline const Color &get_current() const noexcept {
        return this->current;
    }

    inline std::size_t get_turns() const noexcept {
        return this->board.get_turns() / 2 + 1;
    }

    int count_queen_surrounded(const Color &c) noexcept;

    Coords find_destination(const std::string &piece, Directions direction) const;
    std::pair<std::string, Directions> find_adjacent(const Coords &coords) noexcept;

    void legal_piece_placement(std::vector<Coords> &places) noexcept;
    void hoppable_locations(const std::string &piece, std::vector<Coords> &places) noexcept;
    void beetle_locations(const std::string &piece, std::vector<Coords> &places) noexcept;
    void movable_locations(const std::string &piece, std::vector<Coords> &places, const int &distance) noexcept;
    void movable_locations(const Coords &coords, std::vector<Coords> &places, int distance, bool (&visited)[hive::X][hive::Y]) noexcept;
    
private:
    Color current = WHITE;
    hive::Board board;
    std::unordered_map<std::string, Coords> insects;
    std::unordered_set<std::string> hands;
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
        this->message = "Piece " + piece + " does not exist.";
    }

    const char* what() const noexcept override {
        return this->message.c_str();
    }

private:
    std::string message;
};


class PieceNotOnTheBoard : public std::exception {
public:
    explicit PieceNotOnTheBoard(const std::string& piece) {
        this->message = "Piece " + piece + " is not on the board.";
    }

    const char* what() const noexcept override {
        return this->message.c_str();
    }

private:
    std::string message;
};


class NotOneHive : public std::exception {
public:
    const char* what() const noexcept override {
        return "Board is not connected";
    }
};


#endif
