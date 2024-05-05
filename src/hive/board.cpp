#include <hive/board.hpp>


void hive::Board::add_piece(const hive::Piece &p) {
    pieces[p.get_location()] = p;
}


bool hive::Board::is_empty() const {
    return pieces.empty();
}


hive::Piece hive::Board::get_piece(const Coords &c) {
    auto piece = this->pieces[c];
    return piece;
}


void hive::Board::move(const Coords &from, const Coords &to) {
    if (from == to) return;

    auto piece_from = this->pieces.find(from);
    if (piece_from == this->pieces.end()) return;

    auto piece_to = this->pieces.find(to);
    if (piece_to != this->pieces.end()) return;

    auto p = piece_from->second;
    p.move(to);
    this->pieces[to] = p;
    this->pieces.erase(piece_from);
}
