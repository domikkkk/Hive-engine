#ifndef ALFABETA_HPP
#define ALFABETA_HPP
#pragma once

#include <hive/game.hpp>
#include <functional>


class AlfaBeta {
private:
    using EvaluationFunc = std::function<float(Controller&, Color&)>;

    EvaluationFunc evaluation;
    Game *game = nullptr;

    Color maximazing = Color::WHITE;
    Color minimazing = Color::BLACK;

    int depth = 5;

public:
    AlfaBeta() = default;
    // AlfaBeta(Game &game, EvaluationFunc func)
    //     : evaluation(func), game(game) {}

    void set_game(Game &game, EvaluationFunc func) noexcept;

    float evaluate() noexcept;

    std::pair<std::string, Coords> get_best_move(const int &depth=0) noexcept;
    std::pair<std::pair<std::string, Coords>, float> minimax(int depth, bool maximazing, float alfa, float beta) noexcept;
};


#endif
