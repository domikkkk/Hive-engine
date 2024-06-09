#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP
#pragma once

#include <hive/namespaces.hpp>


class Controller {
public:
    void switch_turn();
    const int &get_player() const;

private:
    int whos_turn = Color::WHITE;
};


#endif
