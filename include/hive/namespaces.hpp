#ifndef NAMESPACES_HPP
#define NAMESPACES_HPP
#pragma once


#define PLAYERS 2


#ifdef ML
    #define MOSQUITO_E
    #define LADYBUG_E
#endif

#ifdef MP
    #define MOSQUITO_E
    #define PILLBUG_E
#endif

#ifdef LP
    #define LADYBUG_E
    #define PILLBUG_E
#endif


#ifdef MLP
    #define MOSQUITO_E
    #define LADYBUG_E
    #define PILLBUG_E
#endif

#include <string>


enum class Directions {
    N,
    NE,
    E,
    S,
    SW,
    W,
    UP,
    DOWN,
    DEFAULT,  // not existing -> error
};


enum Color {
    WHITE,
    BLACK,
    NONCOLOR,
};


constexpr Color opposite[] = {
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
    static const std::string pass = "pass";
};


namespace BestMove_Argument {
    static const std::string depth = "depth";
    static const std::string time = "time";
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
#ifdef LADYBUG_E
    static constexpr char ladybug = 'L';
#endif
#ifdef MOSQUITO_E
    static constexpr char mosquito = 'M';
#endif
#ifdef PILLBUG_E
    static constexpr char pillbug = 'P';
#endif
    static constexpr char notexists = '\0';
};


namespace Insects {
    static constexpr int bee = 1;
    static constexpr int ant = 3;
    static constexpr int beetle = 2;
    static constexpr int grasshopper = 3;
    static constexpr int spider = 2;
#ifdef LADYBUG_E
    static constexpr int ladybug = 1;
#else
    static constexpr int ladybug = 0;
#endif
#ifdef MOSQUITO_E
    static constexpr int mosquito = 1;
#else
    static constexpr int mosquito = 0;
#endif
#ifdef PILLBUG_E
    static constexpr int pillbug = 1;
#else
    static constexpr int pillbug = 0;
#endif
};


namespace hive {
    static constexpr int X = 64;
    static constexpr int Y = 64;
    static constexpr int Z = 8;
    static constexpr int turns = 4;
};


static constexpr int possible_infinity = __INT_MAX__;
static constexpr int limit = 1000;
static constexpr float infinity = __FLT_MAX__ / 2;


static constexpr int multiply[] = {2, -2};


enum EntryType {
    Exact = 0,
    LowerBound,
    UpperBound,
};

constexpr int number = 2 * (Insects::bee + Insects::ant + Insects::beetle + Insects::grasshopper +
    Insects::spider + Insects::mosquito + Insects::ladybug + Insects::pillbug);

#endif
