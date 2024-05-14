#include <hive/board.hpp>


void hive::Board::add_piece(const hive::Insect &p) {
    insects[p.get_location()] = p;
}


bool hive::Board::is_empty() const {
    return insects.empty();
}


hive::Insect &hive::Board::get_piece(const Coords &c) {
    return this->insects[c];
}


void hive::Board::move(const Coords &from, const Coords &to) {
    if (from == to) return;

    auto insect_from = this->insects.find(from);
    if (insect_from == this->insects.end()) return; // zrobić wyjątek

    auto insect_to = this->insects.find(to);
    if (insect_to != this->insects.end()) return; // zrobić wyjątek

    hive::Insect &insect = this->insects[from];
    insect.move(to);
    this->insects[to] = insect;
    this->insects.erase(insect_from);
}
