#ifndef BOARD_HPP
#define BOARD_HPP
#pragma once

#include <unordered_map>
#include <hive/pieces.hpp>
#include <memory>
#include <hive/moves.hpp>


namespace hive {
    class Board {
    public:
        Board() = default;
        ~Board();
        void add_piece(std::unique_ptr<hive::Insect> i);
        void remove_piece(const Coords &c);
        void remove_piece(std::unique_ptr<hive::Insect> i);
        bool is_empty() const;
        void swap(const Coords &from, const Coords &to);
        void move(const Coords &from, const Coords &to);
        Move unmove();
        template <class T> std::unique_ptr<T> get_piece_at(const Coords &c);
    private:
        std::unordered_map<Coords, std::unique_ptr<Insect>, HashFn> insects;  // TODO shared_pointers
        Moves moves;
    };
}


#endif
