#ifndef NAMESPACES_HPP
#define NAMESPACES_HPP
#pragma once


// #define MOSQUITO_E
// #define LADYBUG_E

#define PLAYERS 2


#include <string>


enum Color {
    WHITE,
    BLACK,
    NONCOLOR,
};


const std::string colorToString[] = {
    "w",
    "b",
    "n"
};


enum class InsectType {
    ANT,
    BEETLE,
    GRASSHOPPER,
    SPIDER,
    BEE,
    PILLBUG,
    MOSQUITO,
    LADYBUG,
    NONTYPE,
};


namespace Instrucions {
    static const std::string start = "newgame";
    static const std::string info = "Info";
    static const std::string play = "play";
};


enum class State {
    INPROGRESS,
    NOTSTARTED,
    DRAW,
    WHITEWINS,
    BLACKWINS
};


namespace GameState {
    static const std::string inprogress = "InProgress";
    static const std::string notstarted = "NotStarted";
    static const std::string draw = "Draw";
    static const std::string whitewins = "WhiteWins";
    static const std::string blackwins = "BlackWins";
};


namespace Errors {
    static const std::string invalid_move = "invalid move";
};


namespace Insect {
    static const char bee = 'Q';
    static const char beetle = 'B';
    static const char ant = 'A';
    static const char grasshopper = 'G';
    static const char spider = 'S';
    static const char ladybug = 'L';
    static const char mosquito = 'M';
    static const char pillbug = 'P';
    static const char notexists = '\0';
};


namespace Insects {
    static const int bee = 1;
    static const int ant = 3;
    static const int beetle = 2;
    static const int grasshopper = 3;
    static const int spider = 2;
    static const int ladybug = 1;
    static const int mosquito = 1;
    static const int pillbug = 1;
};


namespace hive {
    static const int X = 100;
    static const int Y = 100;
    static const int Z = 8;
};


static const int possible_infinity = __INT_MAX__;

#endif
