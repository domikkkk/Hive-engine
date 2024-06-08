#pragma once


template <class T>
T* hive::Board::get_piece_at(const Coords &c) noexcept {
    auto it = this->insects.find(c);
    if (it == this->insects.end()) return nullptr;
    return dynamic_cast<T*>(it->second.get());
}
