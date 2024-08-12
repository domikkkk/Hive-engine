#include <hive/pieces.hpp>


hive::Insect::Insect(const Coords &c, const Color &color, const InsectType &type) noexcept:
    Insect(c, color) {
    this->type = type;
}


hive::Bee::Bee(const Coords &c, const Color &color) noexcept : Insect(c, color, InsectType::BEE) {}


hive::Ant::Ant(const Coords &c, const Color &color) noexcept : Insect(c, color, InsectType::ANT) {}


hive::Beetle::Beetle(const Coords &c, const Color &color) noexcept : Insect(c, color, InsectType::BEETLE) {}



hive::Grasshopper::Grasshopper(const Coords &c, const Color &color) noexcept : Insect(c, color, InsectType::GRASSHOPPER) {
    this->_jump = true;
}


hive::Spider::Spider(const Coords &c, const Color &color) noexcept : Insect(c, color, InsectType::SPIDER) {}


#ifdef LADYBUG_E
hive::LadyBug::LadyBug(const Coords &c, const Color &color) noexcept : Insect(c, color, InsectType::LADYBUG) {}
#endif


#ifdef MOSQUITO_E
hive::Mosquito::Mosquito(const Coords &c, const Color &color) noexcept : Insect(c, color, InsectType::MOSQUITO) {}
#endif


#ifdef PILLBUG_E
hive::PillBug::PillBug(const Coords &c, const Color &color) noexcept : Insect(c, color, InsectType::PILLBUG) {}
#endif


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


std::vector<Coords> hive::Insect::get_surrounding_locations() const noexcept {
    return this->_c.get_surrounding_locations();;
}


bool hive::Insect::operator==(const Insect &p) const noexcept {
    return p.get_color() != NONCOLOR && this->_c == p._c && this->color == p.color && this->type == p.type;
}


const Color &hive::Insect::get_color() const noexcept {
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
