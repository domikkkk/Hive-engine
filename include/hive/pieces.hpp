#ifndef PIECES_HPP
#define PIECES_HPP
#pragma once

#include <hive/board.hpp>
#include <string>


enum Color {
    WHITE,
    BLACK
};


struct Coords {
    int x;
    int y;
    int z;
    Coords(const int &x, const int &y):x(x), y(y), z(0) {};
    Coords operator+(const Coords &c) const;
    bool operator==(const Coords &c) const;
};


namespace hive {
    class Board;  // forward declaration
    class Piece{
    public:
        Piece(const Coords &c, const int &color):_c(c), color(color) {};
        ~Piece() = default;
        Coords get_location() const;
        int get_color() const;
        std::string get_name() const;
        virtual void move(const int &x, const int &y);
        void set_board(const Board *b);
    protected:
        const Board *board;
        Coords _c;
        int color;
        bool can_move = false;
        std::string name;
    };


    class Bee : public Piece {
    public:
        using Piece::Piece;
    private:
        std::string name = "Bee";
    };

    class Ant : public Piece {
    public:
        using Piece::Piece;
    private:
        std::string name = "Ant";
    };

    class Beetle : public Piece {
    public:
        using Piece::Piece;
        void move(const int &x, const int &y, const int &z);
    private:
        std::string name = "Beetle";
    };

    class Grasshopper : public Piece {
    public:
        using Piece::Piece;
    private:
        std::string name = "Grasshopper";
    };

    class Spider : public Piece {
    public:
        using Piece::Piece;
    private:
        std::string name = "Spider";
    };
}

#endif
