#ifndef PIECES_HPP
#define PIECES_HPP
#pragma once

#include <string>
#include <vector>


enum Color {
    WHITE,
    BLACK,
    DEFAULT
};


struct Coords {
    int x;
    int y;
    int z;
    Coords() = default;
    Coords(const int &x, const int &y):x(x), y(y), z(0) {};
    Coords operator+(const Coords &c) const;
    bool operator==(const Coords &c) const;
};


Coords movements(int i);


class HashFn {
public:
    size_t operator()(const Coords &c) const;
};


namespace hive {
    class Piece{
    public:
        Piece() {this->_real = false;};
        Piece(const Coords &c):_c(c) {};
        Piece(const Coords &c, const int &color):_c(c), color(color) {};
        ~Piece() = default;
        Coords get_location() const;
        virtual int get_color() const;
        virtual void move(const int &x, const int &y);
        virtual std::string get_name() const;
        virtual std::vector<Coords> get_surrounding_locations();
        virtual bool can_move() const;
        virtual bool is_real() const;
        virtual bool operator==(const Piece &p) const;
    protected:
        int color;
        bool _move = false;
        bool _real = true;
        Coords _c;
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
