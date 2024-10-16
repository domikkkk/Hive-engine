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


namespace GameState {
    static const std::string inprogress = "InProgress";
    static const std::string notstarted = "NotStarted";
    static const std::string draw = "Draw";
    static const std::string whitewins = "WhiteWins";
    static const std::string blackwins = "BlackWins";
};


namespace Insect {
    static const char bee = 'q';
    static const char beetle = 'b';
    static const char ant = 'a';
    static const char grasshopper = 'g';
    static const char spider = 's';
    static const char ladybug = 'l';
    static const char mosquito = 'm';
    static const char pillbug = 'p';
    static const char notexists = '\0';
};


namespace hive {
    static const int X = 53;
    static const int Y = 107;
    static const int Z = 8;
};


static const int possible_infinity = __INT_MAX__;

#endif
