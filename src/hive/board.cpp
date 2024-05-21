#include <hive/board.hpp>
#include "board.tpp"


hive::Board::~Board() {
    // because shared_ptr
    // for (auto it = this->insects.begin(); it != this->insects.end(); ++it) {
    //     if (it->second != nullptr) {
    //         delete it->second;
    //         it->second = nullptr;
    //     }
    // }
    this->insects.clear();
}


void hive::Board::add_piece(std::shared_ptr<hive::Insect> i) {
    const auto& location = i->get_location();
    auto it = this->insects.find(location);
    if (it != this->insects.end()) return;  // Can't add. TODO make expection
    this->insects[location] = i;
}


void hive::Board::remove_piece(const Coords &c) {
    auto it = this->insects.find(c);
    if (it != this->insects.end()) {
        // delete it->second;  // because shared_ptr
        this->insects.erase(it);
    }
}


void hive::Board::remove_piece(std::shared_ptr<hive::Insect> i) {
    this->remove_piece(i->get_location());
}


bool hive::Board::is_empty() const {
    return insects.empty();
}



void hive::Board::move(const Coords &from, const Coords &to) {
    if (from == to) return;

    auto insect_from = this->insects.find(from);
    if (insect_from == this->insects.end()) return; // zrobić wyjątek

    auto insect_to = this->insects.find(to);
    if (insect_to != this->insects.end()) return; // zrobić wyjątek

    this->insects[to] = this->insects[from];
    this->insects.erase(insect_from);
    this->insects[to]->move(to);
}
