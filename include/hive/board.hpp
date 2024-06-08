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
        void remove_piece(const Coords &c) noexcept;
        void remove_piece(hive::Insect *i) noexcept;
        bool is_empty() const noexcept;
        bool is_connected() const noexcept;
        void swap(const Coords &from, const Coords &to) noexcept;
        void move(const Coords &from, const Coords &to);
        const Move unmove() noexcept;
        template <class T> T *get_piece_at(const Coords &c) const noexcept;
    private:
        std::unordered_map<Coords, std::unique_ptr<Insect>, HashFn> insects;  // TODO shared_pointers
        Moves moves;
    };
}


#include "src/hive/board.tpp"
#endif
