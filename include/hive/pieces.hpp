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
    class Insect{
    public:
        Insect() {this->_exist = false;};
        Insect(const Coords &c):_c(c) {this->color = DEFAULT;};
        Insect(const Coords &c, const int &color):_c(c), color(color) {};
        ~Insect() = default;
        Coords get_location() const;
        virtual int get_color() const;
        virtual void move(const Coords &c);
        virtual std::string get_name() const;
        virtual std::vector<Coords> get_surrounding_locations();
        virtual bool can_move() const;
        virtual bool is_exist() const;
        virtual bool operator==(const Insect &p) const;
    protected:
        Coords _c;
        int color;
        bool _move = false;
        bool _exist = true;
        std::string name = "";
    };


    class Bee : public Insect {
    public:
        using Insect::Insect;
        Bee(const Insect& piece) : Insect(piece) {};
    private:
        std::string name = "Bee";
    };

    class Ant : public Insect {
    public:
        using Insect::Insect;
        Ant(const Insect& piece) : Insect(piece) {};
    private:
        std::string name = "Ant";
    };

    class Beetle : public Insect {
    public:
        using Insect::Insect;
        Beetle(const Insect& piece) : Insect(piece) {};
    private:
        std::string name = "Beetle";
    };

    class Grasshopper : public Insect {
    public:
        using Insect::Insect;
        Grasshopper(const Insect& piece) : Insect(piece) {};
    private:
        std::string name = "Grasshopper";
    };

    class Spider : public Insect {
    public:
        using Insect::Insect;
        Spider(const Insect& piece) : Insect(piece) {};
    private:
        std::string name = "Spider";
    };
}

#endif
