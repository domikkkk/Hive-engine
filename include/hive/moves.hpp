#ifndef MOVES_HPP
#define MOVES_HPP
#pragma once

#include <vector>
#include <hive/coordinates.hpp>


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

    const std::size_t get_move_counts() const noexcept;
    void push_back(const Move &move) noexcept;
    void pop_back() noexcept;
    const Move &back() const noexcept;
private:
    std::vector<Move> all = {};
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
