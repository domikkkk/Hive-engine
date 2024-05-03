#include <hive/pieces.hpp>


hive::Piece::Piece(hive::Board *b, const Coords &c, const int &color):board(b), _c(c), color(color) {
    if (b != nullptr) {
        b->add_piece(this);
    }
}


void hive::Piece::move(const int &x, const int &y) {
    this->_c.x += x;
    this->_c.y += y;
}


int hive::Piece::get_x() const {
    return this->_c.x;
}


int hive::Piece::get_y() const {
    return this->_c.y;
}


int hive::Piece::get_z() const {
    return this->_c.z;
}


int hive::Piece::get_color() const {
    return this->color;
}


void hive::Beetle::move(const int &x, const int &y, const int &z) {
    this->_c.x += x;
    this->_c.y += y;
    this->_c.z += z;
}
