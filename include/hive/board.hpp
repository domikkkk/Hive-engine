#ifndef BOARD_HPP
#define BOARD_HPP
#pragma once
#include <vector>
#include <memory>
#include <hive/pieces.hpp>


struct Coords;  // forward declaration
namespace hive {
    class Piece;  // forward declaration
    class Board {
    public:
        Board() {this->pieces.reserve(22);};
        ~Board() = default;
        void add_piece(Piece *p);
        bool is_empty() const;
    private:
        std::vector<std::unique_ptr<Piece>> pieces;
    };
}


std::vector<Coords> get_surrounding_locations(const Coords &c);
Coords movements(int i);

#endif
