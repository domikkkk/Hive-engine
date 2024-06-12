#ifndef GAMECONTROLLER_TPP
#define GAMECONTROLLER_TPP

#include <hive/gamecontroller.hpp>


template <class T, class U>
Controller<T, U>::Controller(const T &board): board(board) {}


template <class T, class U>
void Controller<T, U>::switch_turn() noexcept {
    switch (this->whos_turn)
    {
    case WHITE:
        this->whos_turn = BLACK;
        break;
    case BLACK:
        this->whos_turn = WHITE;
        break;
    default:
        this->whos_turn = WHITE;
        break;
    }
}


template <class T, class U>
const Color &Controller<T, U>::get_player() const noexcept {
    return this->whos_turn;
}


template <class T, class U>
void Controller<T, U>::add_piece(const std::string &name, const U &where) noexcept {
    auto c = std::make_unique<U>(where);
    this->insects[name] = std::move(c);
}

#endif
