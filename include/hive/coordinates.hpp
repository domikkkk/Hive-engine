#ifndef COORDINATES_HPP
#define COORDINATES_HPP
#pragma once


#include <stddef.h>


enum class Directions {
    N,
    NE,
    SE,
    S,
    SW,
    NW
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


Coords movements(const Directions &direction);


class HashFn {
public:
    size_t operator()(const Coords &c) const;
};


#endif
