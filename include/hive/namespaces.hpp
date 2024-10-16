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
    static const char white_bee = 'Q';
    static const char white_beetle = 'B';
    static const char white_ant = 'A';
    static const char white_grasshopper = 'G';
    static const char white_spider = 'S';
    static const char white_ladybug = 'L';
    static const char white_mosquito = 'M';
    static const char white_pillbug = 'P';
    static const char black_bee = 'q';
    static const char black_beetle = 'b';
    static const char black_ant = 'a';
    static const char black_grasshopper = 'g';
    static const char black_spider = 's';
    static const char black_ladybug = 'l';
    static const char black_mosquito = 'm';
    static const char black_pillbug = 'p';
    static const char notexists = '\0';
};


namespace hive {
    static const int X = 53;
    static const int Y = 107;
    static const int Z = 8;
};


static const int possible_infinity = __INT_MAX__;

#endif
