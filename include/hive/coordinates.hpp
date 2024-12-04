#ifndef COORDINATES_HPP
#define COORDINATES_HPP
#pragma once


#include <vector>


enum class Directions {
    N,
    NE,
    E,
    S,
    SW,
    W,
    UP,
    DOWN
};


struct Coords {
    int x = -1;
    int y = -1;
    int z = -1;
    Coords() noexcept = default;
    Coords(const int &x, const int &y) noexcept: x(x), y(y), z(0) {};
    Coords(const int &x, const int &y, const int &z) noexcept: x(x), y(y), z(z) {};
    Coords operator+(const Coords &c) const noexcept;
    const Coords get_neighbor(const Directions &direction) const noexcept;
    bool operator==(const Coords &c) const noexcept;
    bool operator!=(const Coords &c) const noexcept;
    std::vector<Coords> get_surrounding_locations() const noexcept;
    std::vector<Coords> get_in_Z() const noexcept;
};


class HashFn {
public:
    std::size_t operator()(const Coords &c) const noexcept;
};


#endif
