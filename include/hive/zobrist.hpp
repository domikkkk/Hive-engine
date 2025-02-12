#ifndef ZOBRIST_HPP
#define ZOBRIST_HPP
#pragma once

#include <cstdint>
#include <hive/namespaces.hpp>
#include <unordered_map>


class ZobristHash {
public:
    ZobristHash() noexcept;

    void switch_turn() noexcept;
    void Xor(const std::string &piece, const int &q, const int &c, const int &s) noexcept;
    
    void reset() noexcept {
        this->_hash = 0;
    }

    inline const uint64_t
    &value() const noexcept {
        return this->_hash;
    };  

private:
    uint64_t _next = 1;
    uint64_t _hash = 0;

    uint64_t hashByColor;
    uint64_t hashByPosition[number][hive::X][hive::Y][hive::Z];

    uint64_t rand64() noexcept;

    std::unordered_map<std::string, int> insect_index = { // pewnie lepiej dla samych radzajów zrobić zamiast rozdzielać do pojedyńczej figury
        {"wQ", 0},
        {"wS1", 1},
        {"wS2", 2},
        {"wB1", 3},
        {"wB2", 4},
        {"wG1", 5},
        {"wG2", 6},
        {"wG3", 7},
        {"wA1", 8},
        {"wA2", 9},
        {"wA3", 10},
        {"bQ", 11},
        {"bS1", 12},
        {"bS2", 13},
        {"bB1", 14},
        {"bB2", 15},
        {"bG1", 16},
        {"bG2", 17},
        {"bG3", 18},
        {"bA1", 19},
        {"bA2", 20},
        {"bA3", 21},
        {"wM", 22}, // dla rozszerzeń
        {"bM", 23},
        {"wL", 24},
        {"bL", 25},
        {"wP", 26},
        {"bP", 27},
    };    
};


#endif
