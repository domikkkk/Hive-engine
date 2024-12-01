#ifndef BOARD_HPP
#define BOARD_HPP
#pragma once

#include <hive/moves.hpp>
#include <hive/namespaces.hpp>
#include <unordered_map>
#include <string>


namespace hive {
    struct Piece {
        Piece() noexcept = default;
        Piece(const int &id, const char &type) noexcept: id(id), type(type) {};
        Piece(const int &id, const char &type, const Color &c) noexcept: id(id), type(type), color(c) {};
        int id = -1;
        char type = 0;
        Color color = Color::NONCOLOR;
        bool inPlay = false;
        bool operator==(const Piece &p) const noexcept;
        const std::string to_str() const noexcept;
    };

    class Board {
    public:
        static const Coords first_location;
        static const Coords second_location;
        struct Piece notExist = {0, Insect::notexists};
        Board() = default;
        void add_piece(const Piece &insect, const Coords &where);
        void remove_piece(const Coords &c) noexcept;
        bool is_connected(const Coords &from, const Coords &without={}) noexcept;
        void swap(const Coords &from, const Coords &to) noexcept;
        bool move(const Coords &from, const Coords &to) noexcept;
        const Move unmove() noexcept;
        Piece &operator()(const std::size_t &x, const std::size_t &y) noexcept;
        Piece &operator[](const Coords &c) noexcept;
    private:
        struct Piece fields[X][Y] = {};
        std::unordered_map<Coords, Piece, HashFn> z_fields;  // dla z > 0 czyli tylko dla chrząszczy
        Moves moves;
        std::size_t count_insects = 0;
    };
}


hive::Piece create_piece(const std::string &piece) noexcept;


#endif
