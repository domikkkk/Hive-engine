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
    Coords() noexcept = default;
    Coords(const int &x, const int &y) noexcept: x(x), y(y) {};
    Coords operator+(const Coords &c) const noexcept;
    const Coords get_neighbor(const Directions &direction) const noexcept;
    bool operator==(const Coords &c) const noexcept;
    std::vector<Coords> get_surrounding_locations() const noexcept;
};


#endif
