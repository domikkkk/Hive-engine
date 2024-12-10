#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP
#pragma once

#include <string>
#include <hive/namespaces.hpp>
#include <iostream>
#include <hive/game.hpp>


typedef struct Command {
    std::string command_type;
    std::string parameters;
    void execute(Game &game);
    friend std::istream &operator>>(std::istream &is, Command &command);
} Command;


Move_parameters create_move(std::string &parameters);


#endif
