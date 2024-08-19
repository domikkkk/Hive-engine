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
    class Ability {
    public:
        Ability() = default;
        Ability(const char &type);
        int how_far = 0;
        bool can_hop = false;
        bool can_crawl = false;
    };
};


#endif
