#ifndef BOARD_HPP
#define BOARD_HPP
#pragma once
#include <vector>
#include <memory>
#include <hive/pieces.hpp>


namespace hive {
    class Piece;  // forward declaration
    class Board {
    public:
        Board() {};
        ~Board() = default;
        void add_piece(Piece *p);
        bool is_empty() const;
    private:
        std::vector<std::unique_ptr<Piece>> pieces;
    };
}

#endif
