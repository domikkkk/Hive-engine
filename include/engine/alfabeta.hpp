#ifndef ALFABETA_HPP
#define ALFABETA_HPP
#pragma once

#include <hive/game.hpp>
#include <functional>


class AlfaBeta {
private:
    using EvaluationFunc = std::function<float(Controller&)>;

    EvaluationFunc evaluation;
    Game game;

    Color maximazing = Color::WHITE;
    Color minimazing = Color::BLACK;

public:
    AlfaBeta() = default;
    AlfaBeta(Game &game, EvaluationFunc func)
        : evaluation(func), game(game) {}

    std::pair<std::string, Coords> get_best_move() noexcept;
};


#endif
