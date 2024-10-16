#ifndef MOVES_HPP
#define MOVES_HPP
#pragma once

#include <vector>
#include <hive/coordinates.hpp>


namespace hive {
    class Board;  // forward declaration
};


struct Move {
    Coords from;
    Coords to;
    bool added = false;
    Move() = default;
    Move(const Coords &f, const Coords &t);
    explicit Move(const Coords &added);
};


class Moves {
public:
    Moves() = default;
    ~Moves();
private:
    std::vector<Move> all = {};
    friend class hive::Board;
};


namespace hive {
    struct Ability {
        Ability() = default;
        Ability(const int &how_far, const bool &can_hop, const bool &can_crawl): how_far(how_far), can_hop(can_hop), can_crawl(can_crawl) {};
        int how_far = 0;
        bool can_hop = false;
        bool can_crawl = false;
    };

    struct Ability gen_possibility(const char &type);
};


#endif
