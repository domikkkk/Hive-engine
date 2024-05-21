#pragma once

#include <hive/board.hpp>


template <class T>
std::shared_ptr<T> hive::Board::get_piece_at(const Coords &c) {
    auto it = this->insects.find(c);
    if (it == this->insects.end()) return nullptr;
    return std::dynamic_pointer_cast<T>(it->second);
    // return std::shared_ptr<T>(static_cast<T*>(it->second.get()));
}