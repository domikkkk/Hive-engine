#include <hive/pieces.hpp>


hive::Bee::Bee(const Coords &c, const int &color) noexcept : Insect(c, color) {
    this->type = InsectType::BEE;
}


hive::Bee::Bee(const Insect &insect) noexcept : Insect(insect) {
    this->type = InsectType::BEE;
}


hive::Ant::Ant(const Coords &c, const int &color) noexcept : Insect(c, color) {
    this->type = InsectType::ANT;
}


hive::Ant::Ant(const Insect &insect) noexcept : Insect(insect) {
    this->type = InsectType::ANT;
}


hive::Beetle::Beetle(const Coords &c, const int &color) noexcept : Insect(c, color) {
    this->type = InsectType::BEETLE;
}


hive::Beetle::Beetle(const Insect &insect) noexcept : Insect(insect) {
    this->type = InsectType::BEETLE;
}


hive::Grasshopper::Grasshopper(const Coords &c, const int &color) noexcept : Insect(c, color) {
    this->type = InsectType::GRASSHOPPER;
    this->_jump = true;
}


hive::Grasshopper::Grasshopper(const Insect &insect) noexcept : Insect(insect) {
    this->type = InsectType::GRASSHOPPER;
    this->_jump = true;
}


hive::Spider::Spider(const Coords &c, const int &color) noexcept : Insect(c, color) {
    this->type = InsectType::SPIDER;
}


hive::Spider::Spider(const Insect &insect) noexcept : Insect(insect) {
    this->type = InsectType::SPIDER;
}


void hive::Insect::move(const Coords &c) noexcept {
    this->_c.x = c.x;
    this->_c.y = c.y;
    this->_c.z = c.z;
}


void hive::Insect::set_move(const bool &m) noexcept {
    this->_move = m;
}


const Coords &hive::Insect::get_location() const noexcept {
    return this->_c;
}


std::vector<Coords> hive::Insect::get_surrounding_locations() noexcept {
    std::vector<Coords> neighbors;
    neighbors.reserve(6);
    for (int i = static_cast<int>(Directions::N); i <= static_cast<int>(Directions::NW); ++i) {
        Directions dir = static_cast<Directions>(i);
        neighbors.push_back(this->_c + movements(dir));
    }
    return neighbors;
}


bool hive::Insect::operator==(const Insect &p) const noexcept {
    return p.get_color() != DEFAULT && this->_c == p._c && this->color == p.color && this->type == p.type;
}


const int &hive::Insect::get_color() const noexcept {
    return this->color;
}


const InsectType &hive::Insect::get_type() const noexcept {
    return this->type;
}


const bool &hive::Insect::can_move() const noexcept {
    return this->_move;
}


const bool &hive::Insect::is_exist() const noexcept {
    return this->_exist;
}


const bool &hive::Insect::can_jump() const noexcept {
    return this->_jump;
}
