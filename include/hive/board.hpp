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
        void add_piece(Insect *p);
        bool is_empty() const;
        void move(const Coords &from, const Coords &to);
        Insect *get_piece_at(const Coords &c);
    private:
        std::unordered_map<Coords, Insect*, HashFn> insects;
    };
}


#endif
