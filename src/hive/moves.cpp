#include <hive/moves.hpp>
#include <hive/namespaces.hpp>


Move::Move(const Coords &f, const Coords &t): from(f), to(t) {};


Move::Move(const Coords &added): to(added), added(true) {};


Moves::~Moves() {
    this->all.clear();
}


hive::Ability::Ability(const char &type) {
    switch (type)
    {
    case Insect::beetle:
        this->can_crawl = true;
        this->how_far = 1;
        break;
    case Insect::bee:
        this->how_far = 1;
        break;
    case Insect::ant:
        this->how_far = infinity;
        break;
    case Insect::grasshopper:
        this->can_hop = true;
        break;
    case Insect::spider:
        this->how_far = 3;
        break;
    #ifdef MOSQUITO_E
    case Insect::mosquito:
        break;
    #endif
    #ifdef LADYBUG_E
    case Insect::ladybug:
        this->how_far = 3;
        this->can_crawl = true;
        break;
    #endif
    #ifdef PILLBUG_E
    case Insect::pillbug:
        this->how_far = 1;
        break;
    #endif
    default:
        break;
    }
}