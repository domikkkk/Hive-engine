#include <hive/coordinates.hpp>


bool Coords::operator==(const Coords &c) const noexcept {
    return this->x == c.x && this->y == c.y;
}


Coords Coords::operator+(const Coords &c) const noexcept {
    return {this->x + c.x, this->y + c.y};
}


const Coords Coords::get_neighbor(const Directions &direction) const noexcept {
    switch (direction)
    {
    case Directions::N:  // N
        return {this->x, this->y + 2};
    case Directions::NE:  // NE
        return {this->x + 1, this->y + 1};
    case Directions::SE:  // SE
        return {this->x + 1, this->y - 1};
    case Directions::S:  // S
        return {this->x, this->y - 2};
    case Directions::SW:  // SW
        return {this->x - 1, this->y - 1};
    case Directions::NW:  // NW
        return {this->x - 1, this->y + 1};
    default:
        return {200, 200};  // unexpected error
    }
}


std::vector<Coords> Coords::get_surrounding_locations() const noexcept {
    std::vector<Coords> neighbors;
    neighbors.reserve(6);
    for (int i = static_cast<int>(Directions::N); i <= static_cast<int>(Directions::NW); ++i) {
        Directions dir = static_cast<Directions>(i);
        neighbors.push_back(this->get_neighbor(dir));
    }
    return neighbors;
}
