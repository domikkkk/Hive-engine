#include <hive/pieces.hpp>



void hive::Piece::move(const int &x, const int &y) {
    this->_c.x += x;
    this->_c.y += y;
}


Coords hive::Piece::get_location() const {
    return this->_c;
}


Coords Coords::operator+(const Coords &c) const {
    return {this->x + c.x, this->y + c.y};
}


bool Coords::operator==(const Coords &c) const {
    if (this->x == c.x && this->y == c.y) return true;
    return false;
}


int hive::Piece::get_color() const {
    return this->color;
}


void hive::Piece::set_board(const hive::Board *b) {
    this->board = b;
}


std::string hive::Piece::get_name() const {
    return this->name;
}


void hive::Beetle::move(const int &x, const int &y, const int &z) {
    this->_c.x += x;
    this->_c.y += y;
    this->_c.z += z;
}
