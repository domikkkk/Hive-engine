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


const Color opposite[] = {
    Color::BLACK,
    Color::WHITE,
    Color::WHITE,
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
    static const std::string newgame = "newgame";
    static const std::string info = "info";
    static const std::string play = "play";
    static const std::string undo = "undo";
    static const std::string validmoves = "validmoves";
    static const std::string bestmove = "bestmove";
    static const std::string help = "help";
    static const std::string options = "options";
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


namespace GameType {
    static const std::string base = "Base";
};


namespace Errors {
    static const std::string invalid_move = "invalid move";
};


namespace Insect {
    static constexpr char bee = 'Q';
    static constexpr char beetle = 'B';
    static constexpr char ant = 'A';
    static constexpr char grasshopper = 'G';
    static constexpr char spider = 'S';
    static constexpr char ladybug = 'L';
    static constexpr char mosquito = 'M';
    static constexpr char pillbug = 'P';
    static constexpr char notexists = '\0';
};


namespace Insects {
    static constexpr int bee = 1;
    static constexpr int ant = 3;
    static constexpr int beetle = 2;
    static constexpr int grasshopper = 3;
    static constexpr int spider = 2;
    static constexpr int ladybug = 1;
    static constexpr int mosquito = 1;
    static constexpr int pillbug = 1;
};


namespace hive {
    static constexpr int X = 40;
    static constexpr int Y = 40;
    static constexpr int Z = 8;
    static constexpr int turns = 4;
};


static constexpr int possible_infinity = __INT_MAX__;
static constexpr int limit = 1000;

#endif
