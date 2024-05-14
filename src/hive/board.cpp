#include <hive/board.hpp>


void hive::Board::add_piece(hive::Insect *p) {
    const auto& location = p->get_location();
    hive::Insect *i = this->insects[location];
    if (i != nullptr && i->is_exist()) return;  // Can't add. TODO make expection
    this->insects[location] = p;
}


bool hive::Board::is_empty() const {
    return insects.empty();
}


hive::Insect *hive::Board::get_piece_at(const Coords &c) {
    hive::Insect *i = this->insects[c];
    if (i == nullptr || !i->is_exist()) return nullptr;
    return this->insects[c];
}


void hive::Board::move(const Coords &from, const Coords &to) {
    if (from == to) return;

    auto insect_from = this->insects.find(from);
    if (insect_from == this->insects.end()) return; // zrobić wyjątek

    auto insect_to = this->insects.find(to);
    if (insect_to != this->insects.end()) return; // zrobić wyjątek

    // hive::Insect *insect = this->insects[from];
    // insect->move(to);
    this->insects[to] = this->insects[from];
    this->insects.erase(insect_from);
    this->insects[to]->move(to);
}
