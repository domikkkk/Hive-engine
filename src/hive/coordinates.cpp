#include <hive/coordinates.hpp>


Coords movements(const Directions &direction) noexcept {
    switch (direction)
    {
    case Directions::N:  // N
        return {0, 2};
    case Directions::NE:  // NE
        return {1, 1};
    case Directions::SE:  // SE
        return {1, -1};
    case Directions::S:  // S
        return {0, -2};
    case Directions::SW:  // SW
        return {-1, -1};
    case Directions::NW:  // NW
        return {-1, 1};
    default:
        return {200, 200};  // unexpected error
    }
}


bool Coords::operator==(const Coords &c) const noexcept {
    return this->x == c.x && this->y == c.y && this->z == c.z;
}


Coords Coords::operator+(const Coords &c) const noexcept {
    return {this->x + c.x, this->y + c.y};
}


size_t HashFn::operator()(const Coords &c) const noexcept {
    std::size_t hash = (c.x + 23) << 16;
    hash ^= (c.y + 47) << 8;
    hash ^= c.z;
    return hash;
}


std::vector<Coords> Coords::get_surrounding_locations() const noexcept {
    std::vector<Coords> neighbors;
    neighbors.reserve(6);
    for (int i = static_cast<int>(Directions::N); i <= static_cast<int>(Directions::NW); ++i) {
        Directions dir = static_cast<Directions>(i);
        neighbors.push_back(Coords{this->x, this->y} + movements(dir));
    }
    return neighbors;
}
