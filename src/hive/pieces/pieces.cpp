#include <hive/pieces.hpp>


void Piece::move(const int &x, const int &y) {
    this->_x += x;
    this->_y += y;
}


int Piece::get_x() const {
    return this->_x;
}


int Piece::get_y() const {
    return this->_y;
}


int Piece::get_z() const {
    return this->_z;
}


void Beetle::move(const int &x, const int &y, const int &z) {
    this->_x += x;
    this->_y += y;
    this->_z += z;
}