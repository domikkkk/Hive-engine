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
    // Big letter for white and small for black...
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


namespace hive {
    static const int &X = 53;
    static const int &Y = 106;
    static const int &Z = 8;
};


static const int infinity = __INT_MAX__;

#endif
