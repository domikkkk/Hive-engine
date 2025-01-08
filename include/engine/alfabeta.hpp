#ifndef ALFABETA_HPP
#define ALFABETA_HPP
#pragma once

#include <hive/game.hpp>
#include <engine/bestmove.hpp>
#include <functional>
#include <engine/transpositionTable.hpp>


class AlfaBeta {
private:
    using EvaluationFunc = std::function<float(Controller&, Color&)>;

    EvaluationFunc evaluation;
    Game *game = nullptr;

    Color maximazing = Color::WHITE;

    int max_depth = 10;

    const std::string name = "Moja silnik";
    const std::string version = "v0.1.0";

    TransposistionTable transpositiontable;

public:
    AlfaBeta() = default;

    void new_game(Game &game, EvaluationFunc func) noexcept;

    float evaluate() noexcept;

    const std::string &_name() const noexcept;
    const std::string &_version() const noexcept;

    void order_moves(const std::unordered_map<std::string, std::vector<Coords>> &all_moves, std::vector<EMove> &sorted_moves) noexcept;

    EMove get_best_move(const int &depth=0) noexcept;
    EMove get_best_move_with_time_limit(const int &time=0) noexcept;
    PossibleBestMove minimax(int depth, bool maximazing, float alfa, float beta) noexcept;
};


#endif
