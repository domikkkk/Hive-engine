#include <hive/board.hpp>


void hive::Board::add_piece(const hive::Piece &p) {
    pieces[p.get_location()] = p;
}


bool hive::Board::is_empty() const {
    return pieces.empty();
}
