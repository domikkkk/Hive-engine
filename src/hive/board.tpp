#pragma once

#include <hive/board.hpp>


template <class T>
std::unique_ptr<T> hive::Board::get_piece_at(const Coords &c) {
    auto it = this->insects.find(c);
    if (it == this->insects.end()) return std::unique_ptr<T>(nullptr);
    return std::unique_ptr<T>(static_cast<T*>(it->second.get()));
}
