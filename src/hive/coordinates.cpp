#include <hive/coordinates.hpp>
#include <hive/namespaces.hpp>
#include <cmath>


bool Coords::operator==(const Coords &c) const noexcept {
    return this->x == c.x && this->y == c.y && this->z == c.z;
}

bool Coords::operator!=(const Coords &c) const noexcept {
    return this->x != c.x || this->y != c.y || this->z != c.z;
}


Coords Coords::operator+(const Coords &c) const noexcept {
    return {this->x + c.x, this->y + c.y};
}


Directions Coords::get_direction(const Coords &c) const noexcept {
    int diff_y = c.y - this->y;
    int diff_x = c.x - this->x;
    if (diff_y > 0) {
        if (diff_x > 0) return Directions::NE;
        else if (diff_x == 0) return Directions::N; 
    } else if (diff_y == 0) {
        if (diff_x > 0) return Directions::E;
        else if (diff_x < 0) return Directions::W;
    } else {
        if (diff_x == 0) return Directions::S;
        else if (diff_x < 0) return Directions::SW;
    }
    return Directions::DEFAULT;
}


const Coords Coords::get_ground() const noexcept {
    return {this->x, this->y, 0};
}


std::vector<Coords> Coords::get_surrounding_locations() const noexcept {
    std::vector<Coords> neighbors;
    neighbors.reserve(6);
    neighbors.emplace_back(this->x, this->y + 1, this->z);
    neighbors.emplace_back(this->x + 1, this->y + 1, this->z);
    neighbors.emplace_back(this->x + 1, this->y, this->z);
    neighbors.emplace_back(this->x, this->y - 1, this->z);
    neighbors.emplace_back(this->x - 1, this->y - 1, this->z);
    neighbors.emplace_back(this->x - 1, this->y, this->z);
    return neighbors;
}


std::vector<Coords> Coords::get_in_Z() const noexcept {
    std::vector<Coords> Z;
    if (this->z > 0) {
        Z.emplace_back(this->x, this->y, this->z - 1);
    }
    if (this->z < hive::Z) {
        Z.emplace_back(this->x, this->y, this->z + 1);
    }
    return Z;
}


float Coords::distance(const Coords &c) const noexcept {
    int d = hive::X/2 - 2 * std::abs(c.x - this->x) - 2 * std::abs(c.y - this->y);
    return (float)d / (float)hive::X;
}


std::size_t HashFn::operator()(const Coords &c) const noexcept {
    std::size_t hash = (c.x + hive::X) << 16;
    hash ^= (c.y + hive::Y) << 8;
    hash ^= c.z;
    return hash;
}
