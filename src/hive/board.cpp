#include <hive/board.hpp>


void hive::Board::add_piece(const hive::Insect &p) {
    insects[p.get_location()] = p;
}


bool hive::Board::is_empty() const {
    return insects.empty();
}


hive::Insect hive::Board::get_piece(const Coords &c) {
    auto piece = this->insects[c];
    return piece;
}


void hive::Board::move(const Coords &from, const Coords &to) {
    if (from == to) return;

    auto piece_from = this->insects.find(from);
    if (piece_from == this->insects.end()) return; // zrobić wyjątek

    auto piece_to = this->insects.find(to);
    if (piece_to != this->insects.end()) return; // zrobić wyjątek

    hive::Insect &insect = piece_from->second;
    insect.move(to);
    this->insects[to] = insect;
    this->insects.erase(piece_from);
}
