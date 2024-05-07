#include <hive/pieces.hpp>


void hive::Insect::move(const Coords &c) {
    this->_c.x = c.x;
    this->_c.y = c.y;
    this->_c.z = c.z;
}


Coords hive::Insect::get_location() const {
    return this->_c;
}


Coords Coords::operator+(const Coords &c) const {
    return {this->x + c.x, this->y + c.y};
}


std::vector<Coords> hive::Insect::get_surrounding_locations() {
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


bool hive::Insect::operator==(const Insect &p) const {
    return p.get_color() != DEFAULT && this->_c == p._c && this->color == p.color && this->name == p.name;
}


size_t HashFn::operator()(const Coords &c) const {
#ifdef DEBUG
    return c.x + 23 * (c.y + 47 * c.z);
#endif
    size_t hash = (c.x + 22) << 16;
    hash ^= (c.y + 44) << 8;
    hash ^= c.z;
    return hash;
}


int hive::Insect::get_color() const {
    return this->color;
}


std::string hive::Insect::get_name() const {
    return this->name;
}


bool hive::Insect::can_move() const {
    return this->_move;
}


bool hive::Insect::is_exist() const {
    return this->_exist;
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
