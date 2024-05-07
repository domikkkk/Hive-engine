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


enum class InsectType {
    ANT,
    BEETLE,
    GRASSHOPPER,
    SPIDER,
    BEE
};


namespace hive {
    class Insect{
    public:
        Insect() {this->_exist = false;};
        Insect(const Coords &c):_c(c) {this->color = DEFAULT;};
        Insect(const Coords &c, const int &color):_c(c), color(color) {};
        ~Insect() = default;
        Coords get_location() const;
        virtual int get_color() const;
        virtual void move(const Coords &c);
        virtual InsectType get_type() const;
        virtual std::vector<Coords> get_surrounding_locations();
        virtual bool can_move() const;
        virtual bool is_exist() const;
        virtual bool operator==(const Insect &p) const;
    protected:
        Coords _c;
        int color;
        bool _move = false;
        bool _exist = true;
        InsectType type;
    };


    class Bee : public Insect {
    public:
        Bee(const Coords &c, const int &color);
        Bee(const Insect& piece) : Insect(piece) {};
    };

    class Ant : public Insect {
    public:
        Ant(const Coords &c, const int &color);
        Ant(const Insect& piece) : Insect(piece) {};
    };

    class Beetle : public Insect {
    public:
        Beetle(const Coords &c, const int &color);
        Beetle(const Insect& piece) : Insect(piece) {};
    };

    class Grasshopper : public Insect {
    public:
        Grasshopper(const Coords &c, const int &color);
        Grasshopper(const Insect& piece) : Insect(piece) {};
    };

    class Spider : public Insect {
    public:
        Spider(const Coords &c, const int &color);
        Spider(const Insect& piece) : Insect(piece) {};
    };
}

#endif
