#ifndef GAMECONTROLLER_TPP
#define GAMECONTROLLER_TPP

#include <hive/gamecontroller.hpp>


template <class T, class U>
Controller<T, U>::Controller(const T &board): board(board) {}


template <class T, class U>
void Controller<T, U>::switch_turn() noexcept {
    if (this->whos_turn == WHITE) {
        this->whos_turn = BLACK;
    } else {
        this->whos_turn = WHITE;
    }
}


template <class T, class U>
const Color &Controller<T, U>::get_player() const noexcept {
    return this->whos_turn;
}


template <class T, class U>
void Controller<T, U>::add_piece(const std::string &name, const U &where) noexcept {
    this->insects[name] = where;
}

#endif
