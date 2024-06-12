#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP
#pragma once

#include <hive/namespaces.hpp>
#include <unordered_map>
#include <string>

template <class T, class U>
class Controller {
public:
    Controller() = default;
    explicit Controller(const T &board);
    void switch_turn() noexcept;
    const Color &get_player() const noexcept;
    void add_piece(const std::string &name, const U &where) noexcept;

private:
    Color whos_turn = WHITE;
    T board;
    std::unordered_map<std::string, U> insects;
};


#include "src/hive/gamecontroller.tpp"

#endif
