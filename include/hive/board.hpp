#ifndef BOARD_HPP
#define BOARD_HPP
#pragma once

#include <unordered_map>
#include <hive/pieces.hpp>


namespace hive {
    class Board {
    public:
        Board() = default;
        ~Board() = default;
        void add_piece(const Piece &p);
        bool is_empty() const;
    private:
        std::unordered_map<Coords, Piece, HashFn> pieces;
    };
}


#endif
