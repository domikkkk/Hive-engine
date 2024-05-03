#ifndef PIECES_HPP
#define PIECES_HPP
#pragma once

#include <hive/board.hpp>


enum Color {
    WHITE,
    BLACK
};


struct Coords {
    int x;
    int y;
    int z;
    Coords(const int &x, const int &y):x(x), y(y), z(0) {};
};


namespace hive {
    class Board;  // forward declaration
    class Piece{
    public:
        Piece(Board *b, const Coords &c, const int &color);
        ~Piece() = default;
        int get_x() const;
        int get_y() const;
        int get_z() const;
        int get_color() const;
        virtual void move(const int &x, const int &y);
    protected:
        Board *board;
        Coords _c;
        int color;
        bool can_move = false;
    };


    class Bee : public Piece {
    public:
        using Piece::Piece;
    };

    class Ant : public Piece {
    public:
        using Piece::Piece;
    };

    class Beetle : public Piece {
    public:
        using Piece::Piece;
        void move(const int &x, const int &y, const int &z);
    };

    class Grasshopper : public Piece {
    public:
        using Piece::Piece;
    };

    class Spider : public Piece {
    public:
        using Piece::Piece;
    };
}

#endif
