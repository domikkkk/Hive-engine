#include <hive/board.hpp>


void hive::Board::add_piece(hive::Piece *p) {
    this->pieces.push_back(std::make_unique<hive::Piece>(*p));
}


bool hive::Board::is_empty() const {
    return pieces.empty();
}
