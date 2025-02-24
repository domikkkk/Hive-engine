#ifndef TRANSPOSITIONTABLE_HPP
#define TRANSPOSITIONTABLE_HPP
#pragma once


#include <cstdint>
#include <engine/bestmove.hpp>
#include <map>
#include <hive/namespaces.hpp>


struct TranspositionTableEntry {
    TranspositionTableEntry() = default;
    TranspositionTableEntry(const float &v, const int &d, const EMove &b, const EntryType &t):
        Value(v), Depth(d), BestMove(b), Type(t) {};
    float Value;
    int Depth = -1;
    EMove BestMove;
    EntryType Type = EntryType::Exact;
    // static constexpr size_t SizeInBytes = sizeof(float) + sizeof(int) + sizeof(BestMove);
};


class TransposistionTable {
public:
    using iterator = std::map<uint64_t, TranspositionTableEntry>::iterator;

    inline TranspositionTableEntry
    &operator[](const uint64_t &__key) noexcept {
        return this->table_[__key];
    }

    inline iterator
    find(const uint64_t &__key) noexcept {
        return this->table_.find(__key);
    };

    inline iterator
    end() noexcept {
        return this->table_.end();
    };


    void _delete() noexcept;

private:
    // size_t capacity_;

    std::map<uint64_t, TranspositionTableEntry> table_;
};


#endif
