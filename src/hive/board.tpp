#ifndef BOARD_TPP
#define BOARD_TPP

#include <hive/board.hpp>


template <class T>
T* hive::Board::get_piece_at(const Coords &c) const noexcept {
    auto it = this->insects.find(c);
    if (it == this->insects.end()) return nullptr;
    return static_cast<T*>(it->second.get());
}


#endif
