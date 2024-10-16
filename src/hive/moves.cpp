#include <hive/moves.hpp>
#include <hive/namespaces.hpp>


Move::Move(const Coords &f, const Coords &t): from(f), to(t) {};


Move::Move(const Coords &added): to(added), added(true) {};


Moves::~Moves() {
    this->all.clear();
}


struct hive::Ability hive::gen_possibility(const char &type) {
    switch (type)
    {
    case Insect::white_beetle:
        return Ability(1, false, true);
    case Insect::black_beetle:
        return Ability(1, false, true);
    case Insect::white_bee:
        return Ability(1, false, false);
    case Insect::black_bee:
        return Ability(1, false, false);
    case Insect::white_ant:
        return Ability(possible_infinity, false, false);
    case Insect::black_ant:
        return Ability(possible_infinity, false, false);
    case Insect::white_grasshopper:
        return Ability(0, true, false);
    case Insect::black_grasshopper:
        return Ability(0, true, false);
    case Insect::white_spider:
        return Ability(3, false, false);
    case Insect::black_spider:
        return Ability(3, false, false);
    #ifdef MOSQUITO_E
    case Insect::white_mosquito:
        break;
    case Insect::black_mosquito:
        break;
    #endif
    #ifdef LADYBUG_E
    case Insect::white_ladybug:
        return Ability(3, false, true);
    case Insect::black_ladybug:
        return Ability(3, false, true);
    #endif
    #ifdef PILLBUG_E
    case Insect::white_pillbug:
        return Ability(1, false, false);
    case Insect::black_pillbug:
        return Ability(1, false, false);
    #endif
    default:
        return Ability();
    }
}