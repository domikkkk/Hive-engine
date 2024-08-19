#ifndef BOARD_HPP
#define BOARD_HPP
#pragma once

#include <memory>
#include <hive/moves.hpp>
#include <hive/namespaces.hpp>


namespace hive {
    class Board {
    public:
        static const Coords first_location;
        static const Coords second_location;
        Board() = default;
        void add_piece(const char &insect, const Coords &where);
        void remove_piece(const Coords &c) noexcept;
        bool is_connected() noexcept;
        void swap(const Coords &from, const Coords &to) noexcept;
        void move(const Coords &from, const Coords &to) noexcept;
        const Move unmove() noexcept;
        char &operator()(const std::size_t &x, const std::size_t &y, const std::size_t &z=0) noexcept;
        char &operator[](const Coords &c) noexcept;
    private:
        char fields[Z][X][Y] = {0};
        Moves moves;
        std::size_t insects = 0;
    };
}


#endif
