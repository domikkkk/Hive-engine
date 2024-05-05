#include <hive/pieces.hpp>


void hive::Piece::move(const int &x, const int &y) {
    this->_c.x = x;
    this->_c.y = y;
}


Coords hive::Piece::get_location() const {
    return this->_c;
}


Coords Coords::operator+(const Coords &c) const {
    return {this->x + c.x, this->y + c.y};
}


std::vector<Coords> hive::Piece::get_surrounding_locations() {
    std::vector<Coords> neighbors;
    neighbors.reserve(6);
    for (int i = 0; i < 6; ++i) {
        neighbors.push_back(this->_c + movements(i));
    }
    return neighbors;
}


bool Coords::operator==(const Coords &c) const {
    return this->x == c.x && this->y == c.y && this->z == c.z;
}


bool hive::Piece::operator==(const Piece &p) const {
    return this->_c == p._c && this->color == p.color && this->name == p.name;
}


size_t HashFn::operator()(const Coords &c) const {
#ifndef DEBUG
    return c.x + 23 * (c.y + 47 * c.z);
#endif
    size_t hash = (c.x + 22) << 16;
    hash ^= (c.y + 44) << 8;
    hash ^= c.z;
    return hash;
}


int hive::Piece::get_color() const {
    return this->color;
}


std::string hive::Piece::get_name() const {
    return this->name;
}


bool hive::Piece::can_move() const {
    return this->_move;
}


bool hive::Piece::is_real() const {
    return this->_real;
}


void hive::Beetle::move(const int &x, const int &y, const int &z) {
    Piece::move(x, y);
    this->_c.z = z;
}


Coords movements(int i) {
    switch (i)
    {
    case 0:  // N
        return {0, 2};
    case 1:  // NE
        return {1, 1};
    case 2:  // SE
        return {1, -1};
    case 3:  // S
        return {0, -2};
    case 4:  // SW
        return {-1, -1};
    case 5:  // NW
        return {-1, 1};
    default:
        return {200, 200};  // unexpected error
    }
}
