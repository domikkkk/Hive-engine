#include <hive/moves.hpp>


Move::Move(const Coords &f, const Coords &t): from(f), to(t) {};


Moves::~Moves() {
    this->all.clear();
}
