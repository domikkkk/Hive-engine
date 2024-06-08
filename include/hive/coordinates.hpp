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
    Coords() noexcept = default;
    Coords(const int &x, const int &y) noexcept:x(x), y(y), z(0) {};
    Coords operator+(const Coords &c) const noexcept;
    bool operator==(const Coords &c) const noexcept;
};


Coords movements(const Directions &direction) noexcept;


class HashFn {
public:
    size_t operator()(const Coords &c) const noexcept;
};


#endif
