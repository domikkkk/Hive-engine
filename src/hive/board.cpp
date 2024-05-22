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


void hive::Board::add_piece(std::unique_ptr<hive::Insect> i) {
    const auto& location = i->get_location();
    auto it = this->insects.find(location);
    if (it != this->insects.end()) return;  // Can't add. TODO make expection
    this->insects[location] = std::move(i);
}


void hive::Board::remove_piece(const Coords &c) {
    auto it = this->insects.find(c);
    if (it != this->insects.end()) {
        // delete it->second;  // because unique_ptr
        this->insects.erase(it);
    }
}


void hive::Board::remove_piece(std::unique_ptr<hive::Insect> i) {
    this->remove_piece(i->get_location());
}


bool hive::Board::is_empty() const {
    return insects.empty();
}


void hive::Board::swap(const Coords &from, const Coords &to) {
    auto insect_from = this->insects.find(from);
    insect_from->second->move(to);
    this->insects[to] = std::move(insect_from->second);
    this->insects.erase(insect_from);
}


void hive::Board::move(const Coords &from, const Coords &to) {
    if (from == to) return;

    auto insect_from = this->insects.find(from);
    if (insect_from == this->insects.end()) return; // zrobić wyjątek

    auto insect_to = this->insects.find(to);
    if (insect_to != this->insects.end()) return; // zrobić wyjątek

    this->swap(from, to);
    this->moves.all.push_back({from, to});
}


Move hive::Board::unmove() {
    const Move m = this->moves.all.back();
    this->moves.all.pop_back();
    
    this->swap(m.to, m.from);
    return m;
}
