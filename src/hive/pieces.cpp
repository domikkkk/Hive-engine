#include <hive/pieces.hpp>


hive::Bee::Bee(const Coords &c, const int &color) {
    this->_c = c;
    this->color = color;
    this->type = InsectType::BEE;
}


hive::Bee::Bee(const Insect &insect) : Insect(insect) {
    this->type = InsectType::BEE;
}


hive::Ant::Ant(const Coords &c, const int &color) {
    this->_c = c;
    this->color = color;
    this->type = InsectType::ANT;
}


hive::Ant::Ant(const Insect &insect) : Insect(insect) {
    this->type = InsectType::ANT;
}


hive::Beetle::Beetle(const Coords &c, const int &color) {
    this->_c = c;
    this->color = color;
    this->type = InsectType::BEETLE;
}


hive::Beetle::Beetle(const Insect &insect) : Insect(insect) {
    this->type = InsectType::BEETLE;
}


hive::Grasshopper::Grasshopper(const Coords &c, const int &color) {
    this->_c = c;
    this->color = color;
    this->type = InsectType::GRASSHOPPER;
    this->_jump = true;
}


hive::Grasshopper::Grasshopper(const Insect &insect) : Insect(insect) {
    this->type = InsectType::GRASSHOPPER;
    this->_jump = true;
}


hive::Spider::Spider(const Coords &c, const int &color) {
    this->_c = c;
    this->color = color;
    this->type = InsectType::SPIDER;
}


hive::Spider::Spider(const Insect &insect) : Insect(insect) {
    this->type = InsectType::SPIDER;
}


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
    for (int i = static_cast<int>(Directions::N); i <= static_cast<int>(Directions::NW); ++i) {
        Directions dir = static_cast<Directions>(i);
        neighbors.push_back(this->_c + movements(dir));
    }
    return neighbors;
}


bool Coords::operator==(const Coords &c) const {
    return this->x == c.x && this->y == c.y && this->z == c.z;
}


bool hive::Insect::operator==(const Insect &p) const {
    return p.get_color() != DEFAULT && this->_c == p._c && this->color == p.color && this->type == p.type;
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


InsectType hive::Insect::get_type() const {
    return this->type;
}


bool hive::Insect::can_move() const {
    return this->_move;
}


bool hive::Insect::is_exist() const {
    return this->_exist;
}


bool hive::Insect::can_jump() const {
    return this->_jump;
}


Coords movements(const Directions &direction) {
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
