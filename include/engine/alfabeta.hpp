#ifndef ALFABETA_HPP
#define ALFABETA_HPP
#pragma once

#include <hive/game.hpp>
#include <functional>


typedef struct BestMove {
    std::string piece = "";
    Coords where;
    float value;

    BestMove(const float &value) {this->value = value;};
    BestMove(const std::string &piece, const Coords &c, const float &v): piece(piece), where(c), value(v) {};
} BestMove;


class AlfaBeta {
private:
    using EvaluationFunc = std::function<float(Controller&, Color&)>;

    EvaluationFunc evaluation;
    Game *game = nullptr;

    Color maximazing = Color::WHITE;

    int depth = 5;

public:
    AlfaBeta() = default;

    void set_game(Game &game, EvaluationFunc func) noexcept;

    float evaluate() noexcept;

    BestMove get_best_move(const int &depth=0) noexcept;
    BestMove minimax(int depth, bool maximazing, float alfa, float beta) noexcept;
};


#endif
