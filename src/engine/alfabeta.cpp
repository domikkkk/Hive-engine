#include <engine/alfabeta.hpp>
#include <iostream>


void AlfaBeta::set_game(Game &game, EvaluationFunc func) noexcept {
    delete this->game;
    this->game = &game;
    this->evaluation = func;
}


float AlfaBeta::evaluate() noexcept {
    return this->evaluation(this->game->get_controller(), this->maximazing);
}


std::pair<std::string, Coords> AlfaBeta::get_best_move(const int &d) noexcept {
    auto depth = d? d: this->depth;
    this->maximazing = this->game->get_controller().get_current();
    this->minimazing = opposite[this->maximazing];
    std::cout << this->maximazing << " " << this->minimazing << ' ';
    auto best_move = this->minimax(depth, true, -possible_infinity, possible_infinity);
    std::cout << best_move.second << '\n';
    return best_move.first;
}


std::pair<std::pair<std::string, Coords>, float> AlfaBeta::minimax(int depth, bool maximazing, float alfa, float beta) noexcept {
    if (this->game->is_finished() || depth == 0) {
        auto color = maximazing? this->minimazing: this->maximazing;
        int multiply[] = {2, -2};
        float score = this->evaluation(this->game->get_controller(), color);
        return {{}, score};
    }
    std::pair<std::pair<std::string, Coords>, float> best_move = {{}, maximazing? -possible_infinity: possible_infinity};
    std::unordered_map<std::string, std::vector<Coords>> valid_moves;
    this->game->set_valid_moves(valid_moves);
    for (const auto &move: valid_moves) {
        for (const auto &where: move.second) {
            this->game->get_controller().engine_move(move.first, where);
            auto result = this->minimax(depth-1, !maximazing, alfa, beta);
            if (maximazing) {
                if (result.second > best_move.second) {
                    best_move.second = result.second;
                    best_move.first = {move.first, where};
                }
                alfa = std::max(alfa, best_move.second);
            } else {
                if (result.second < best_move.second) {
                    best_move.second = result.second;
                    best_move.first = {move.first, where};
                }
                beta = std::min(beta, best_move.second);
            }
            this->game->get_controller().undo_move();
            if (beta <= alfa) return best_move;
        }
    }
    return best_move;
}
