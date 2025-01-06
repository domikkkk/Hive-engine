#ifndef ALFABETA_HPP
#define ALFABETA_HPP
#pragma once

#include <hive/game.hpp>
#include <engine/bestmove.hpp>
#include <functional>
#include <engine/transpositionTable.hpp>


typedef struct PossibleMove {
    EMove bestmove;
    float value;
    bool found = false;

    PossibleMove(const float &value) {this->value = value;};
    PossibleMove(const EMove &bestmove, const float &v): bestmove(bestmove) , value(v) {};
} PossibleMove;


class AlfaBeta {
private:
    using EvaluationFunc = std::function<float(Controller&, Color&)>;

    EvaluationFunc evaluation;
    Game *game = nullptr;

    Color maximazing = Color::WHITE;

    int depth = 5;

    std::string name = "Moja silnik";
    std::string version = "v0.1.0";

    TransposistionTable transpositiontable;

public:
    AlfaBeta() = default;

    void set_game(Game &game, EvaluationFunc func) noexcept;

    float evaluate() noexcept;

    EMove get_best_move(const int &depth=0) noexcept;
    PossibleMove minimax(int depth, bool maximazing, float alfa, float beta) noexcept;
};


#endif
