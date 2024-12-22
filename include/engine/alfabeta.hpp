#ifndef ALFABETA_HPP
#define ALFABETA_HPP
#pragma once

#include <hive/game.hpp>
#include <functional>


class AlfaBeta {
private:
    using EvaluationFunc = std::function<float(Controller&)>;

    EvaluationFunc evaluation;
    Controller game_c;

public:
    AlfaBeta() = default;
    AlfaBeta(Controller &controller, EvaluationFunc func)
        : evaluation(func), game_c(controller) {}

    std::pair<std::string, Coords> get_best_move() noexcept;
};


#endif
