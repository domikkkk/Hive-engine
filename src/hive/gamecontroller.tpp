#ifndef GAMECONTROLLER_TPP
#define GAMECONTROLLER_TPP

#include <hive/gamecontroller.hpp>


template <class T, class U>
Controller<T, U>::Controller(const T &board): board(board) {}


template <class T, class U>
void Controller<T, U>::switch_turn() noexcept {
    switch (this->current)
    {
    case WHITE:
        this->current = BLACK;
        break;
    case BLACK:
        this->current = WHITE;
        break;
    default:
        this->current = WHITE;
        break;
    }
}


template <class T, class U>
const Color &Controller<T, U>::get_player() const noexcept {
    return this->current;
}


template <class T, class U>
void Controller<T, U>::add_piece(const std::string &name, const U &where) noexcept {
    this->insects[name] = where;
}

#endif
