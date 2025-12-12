#ifndef ALFABETA_HPP
#define ALFABETA_HPP
#pragma once

#include <hive/game.hpp>
#include <engine/bestmove.hpp>
#include <functional>
#include <engine/transpositionTable.hpp>
#include <chrono>
#include <version.h>


struct CancellationToken {
    using Time = std::chrono::_V2::steady_clock::time_point;
    using Clock = std::chrono::steady_clock;
    using TimeLimit = std::chrono::seconds;

    CancellationToken() = default;
    CancellationToken(const TimeLimit &limit): timelimit(limit), defined(true), start(Clock::now()) {};

    inline bool is_end() const noexcept {
        return Clock::now() - this->start >= this->timelimit;
    }

    TimeLimit timelimit;
    bool defined = false;
    Time start;
};


class AlfaBeta {
private:
    using EvaluationFunc = std::function<float(Controller&)>;

    EvaluationFunc evaluation;
    EvaluationFunc to_order_moves;
    Game *game = nullptr;

    int max_depth = 20;

    const std::string name = "Mój silnik";
    const std::string version = VERSION;

    TransposistionTable transpositiontable;

public:
    AlfaBeta() = default;

    void new_game(Game &game, EvaluationFunc func, EvaluationFunc order) noexcept;

    inline float evaluate() noexcept {
        return this->evaluation(this->game->get_controller());
    }

    inline float evaluate_to_order() noexcept { // do pozbycia się kiedyś
        return this->to_order_moves(this->game->get_controller());
    }

    const std::string &_name() const noexcept;
    const std::string &_version() const noexcept;

    void order_moves(const std::unordered_map<std::string, std::vector<Coords>> &all_moves, std::vector<PossibleBestMove> &sorted_moves, bool maximazing) noexcept;
    float evaluate_move(const EMove &move) noexcept;  // kiedyś zamiast evaluate_to_order()

    EMove get_best_move(const int &depth=0) noexcept;
    EMove get_best_move_with_time_limit(const int &time=0) noexcept;
    PossibleBestMove minimax(int depth, bool maximazing, float alfa, float beta, const struct CancellationToken &token = {}) noexcept;
    PossibleBestMove negamax(int depth, float alfa, float beta, const struct CancellationToken &token = {}) noexcept;
};


#endif
