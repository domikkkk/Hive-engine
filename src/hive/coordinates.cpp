#include <hive/coordinates.hpp>
#include <hive/namespaces.hpp>


bool Coords::operator==(const Coords &c) const noexcept {
    return this->x == c.x && this->y == c.y && this->z == c.z;
}

bool Coords::operator!=(const Coords &c) const noexcept {
    return this->x != c.x || this->y != c.y || this->z != c.z;
}


Coords Coords::operator+(const Coords &c) const noexcept {
    return {this->x + c.x, this->y + c.y};
}


const Coords Coords::get_neighbor(const Directions &direction) const noexcept {
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
        return {200, 200};  // unexpected error
    }
}


const Coords Coords::get_ground() const noexcept {
    return {this->x, this->y, 0};
}


std::vector<Coords> Coords::get_surrounding_locations() const noexcept {
    std::vector<Coords> neighbors;
    neighbors.reserve(6);
    for (int i = static_cast<int>(Directions::N); i <= static_cast<int>(Directions::W); ++i) {
        Directions dir = static_cast<Directions>(i);
        neighbors.push_back(this->get_neighbor(dir));
    }
    return neighbors;
}


std::vector<Coords> Coords::get_in_Z() const noexcept {
    std::vector<Coords> Z;
    if (this->z > 0) {
        Z.push_back({this->x, this->y, this->z - 1});
    }
    if (this->z < hive::Z) {
        Z.push_back({this->x, this->y, this->z + 1});
    }
    return Z;
};


std::size_t HashFn::operator()(const Coords &c) const noexcept {
    std::size_t hash = (c.x + hive::X) << 16;
    hash ^= (c.y + hive::Y) << 8;
    hash ^= c.z;
    return hash;
}
