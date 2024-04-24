#include <hive/pieces.hpp>


void hive::Piece::move(const int &x, const int &y) {
    this->_x += x;
    this->_y += y;
}


int hive::Piece::get_x() const {
    return this->_x;
}


int hive::Piece::get_y() const {
    return this->_y;
}


int hive::Piece::get_z() const {
    return this->_z;
}


void hive::Beetle::move(const int &x, const int &y, const int &z) {
    this->_x += x;
    this->_y += y;
    this->_z += z;
}
