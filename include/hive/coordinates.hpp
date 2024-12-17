#ifndef COORDINATES_HPP
#define COORDINATES_HPP
#pragma once


#include <vector>
#include <cassert>


enum class Directions {
    N,
    NE,
    E,
    S,
    SW,
    W,
    UP,
    DOWN,
    DEFAULT,  // not existing -> error
};


struct Coords {
    int x = -1;
    int y = -1;
    int z = -1;
    Coords() noexcept = default;
    Coords(const int &x, const int &y) noexcept: x(x), y(y), z(0) {};
    Coords(const int &x, const int &y, const int &z) noexcept: x(x), y(y), z(z) {};
    Coords operator+(const Coords &c) const noexcept;
    const Coords get_ground() const noexcept;
    bool operator==(const Coords &c) const noexcept;
    bool operator!=(const Coords &c) const noexcept;
    Directions get_opposite(const Coords &c) const noexcept;
    std::vector<Coords> get_surrounding_locations() const noexcept;
    std::vector<Coords> get_in_Z() const noexcept;
    inline const Coords get_neighbor(const Directions &direction) const noexcept {
        switch (direction)
        {
        case Directions::N:  // N
            return {this->x, this->y + 1};
        case Directions::NE:  // NE
            return {this->x + 1, this->y + 1};
        case Directions::E:  // SE
            return {this->x + 1, this->y};
        case Directions::S:  // S
            return {this->x, this->y - 1};
        case Directions::SW:  // SW
            return {this->x - 1, this->y - 1};
        case Directions::W:  // NW
            return {this->x - 1, this->y};
        case Directions::UP:
            return {this->x, this->y, this->z + 1};
        case Directions::DOWN:
            return {this->x, this->y, this->z - 1};
        default:
            assert(false && "Unexpected direction");
            return {};  // unexpected error
        }
    }
};


class HashFn {
public:
    std::size_t operator()(const Coords &c) const noexcept;
};


#endif
