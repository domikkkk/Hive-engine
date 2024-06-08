#include <hive/moves.hpp>


Move::Move(const Coords &f, const Coords &t): from(f), to(t) {};


Move::Move(const Coords &added): to(added), added(true) {};


Moves::~Moves() {
    this->all.clear();
}
