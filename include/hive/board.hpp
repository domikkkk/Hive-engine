#ifndef BOARD_HPP
#define BOARD_HPP
#pragma once

#include <memory>
#include <hive/moves.hpp>
#include <hive/namespaces.hpp>


namespace hive {
    struct Piece {
        Piece() noexcept = default;
        Piece(const int &id, const char &type) noexcept: id(id), type(type) {};
        Piece(const int &id, const char &type, const Color &c) noexcept: id(id), type(type), color(c) {};
        int id;
        char type;
        Color color = Color::NONCOLOR;
        bool inPlay = false;
        bool operator==(const Piece &p) noexcept;
    };
    class Board {
    public:
        static const Coords first_location;
        static const Coords second_location;
        static const Piece notExisting;
        Board() = default;
        void add_piece(const Piece &insect, const Coords &where);
        void remove_piece(const Coords &c) noexcept;
        bool is_connected() noexcept;
        void swap(const Coords &from, const Coords &to) noexcept;
        void move(const Coords &from, const Coords &to) noexcept;
        const Move unmove() noexcept;
        Piece &operator()(const std::size_t &x, const std::size_t &y, const std::size_t &z=0) noexcept;
        Piece &operator[](const Coords &c) noexcept;
    private:
        struct Piece fields[Z][X][Y] = {};
        Moves moves;
        std::size_t insects = 0;
        // std::vector<>
    };
}


#endif
