#include <hive/moves.hpp>
#include <hive/namespaces.hpp>


Move::Move(const Coords &f, const Coords &t): from(f), to(t) {};


Move::Move(const Coords &added): to(added), added(true) {};


Moves::~Moves() {
    this->all.clear();
}


struct hive::Ability hive::gen_ability(const char &type) {
    switch (type)
    {
    case Insect::beetle:
        return Ability(1, false, true);
    case Insect::bee:
        return Ability(1, false, false);
    case Insect::ant:
        return Ability(possible_infinity, false, false);
    case Insect::grasshopper:
        return Ability(0, true, false);
    case Insect::spider:
        return Ability(3, false, false);
    #ifdef MOSQUITO_E
    case Insect::mosquito:
        break;
    #endif
    #ifdef LADYBUG_E
    case Insect::ladybug:
        return Ability(3, false, true);
    #endif
    #ifdef PILLBUG_E
    case Insect::pillbug:
        return Ability(1, false, false);
    #endif
    default:
        return Ability();
    }
}


void Moves::push_back(const Move &move) noexcept {
    this->all.push_back(move);
}


void Moves::pop_back() noexcept {
    this->all.pop_back();
}


const Move &Moves::back() const noexcept {
    return this->all.back();
}


std::size_t Moves::get_move_counts() const noexcept {
    return this->all.size();
}
