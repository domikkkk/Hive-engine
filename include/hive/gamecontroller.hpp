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
    bool validateQueen() const noexcept;
    bool can_move_on_board() const noexcept;
    void move(const std::string &piece, const Coords &to);
    void engine_move(const std::string &piece, const Coords &to);
    void undo_move() noexcept;
    void prepare_pieces();
    bool check_destination(const Coords &destination);
    std::unordered_map<std::string, Coords> &get_pieces() noexcept;
    std::unordered_map<std::string, bool> &get_all_pieces() noexcept;
    hive::Board &get_board() noexcept;
    std::size_t get_turns() const noexcept;
    const Color &get_current() const noexcept;
    Coords find_destination(const std::string &piece, Directions direction) const;
    Directions find_adjacent(const Coords &coords) noexcept;

    void legal_piece_placement(std::vector<Coords> &places) noexcept;
    void hoppable_locations(const std::string &piece, std::vector<Coords> &places) noexcept;
    void crawlable_locations(const std::string &piece, std::vector<Coords> &places) noexcept;
    void dropable_locations(const std::string &piece, std::vector<Coords> &places) noexcept;
    void movable_locations(const std::string &piece, std::vector<Coords> &places, const int &distance) noexcept;
    void movable_locations(const Coords &coords, std::vector<Coords> &places, int distance, bool (&visited)[hive::X][hive::Y]) noexcept;
    
private:
    Color current = WHITE;
    hive::Board board;
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
