#ifndef COORDINATES_HPP
#define COORDINATES_HPP
#pragma once


#include <vector>


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
    Coords(const int &x, const int &y) noexcept: x(x), y(y), z(0) {};
    Coords operator+(const Coords &c) const noexcept;
    const Coords get_neighbor(const Directions &direction) const noexcept;
    bool operator==(const Coords &c) const noexcept;
    std::vector<Coords> get_surrounding_locations() const noexcept;
};


class HashFn {
public:
    std::size_t operator()(const Coords &c) const noexcept;
};


#endif
