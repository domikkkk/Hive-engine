#include <engine/alfabeta.hpp>
#include <iostream>


void AlfaBeta::set_game(Game &game, EvaluationFunc func) noexcept {
    // delete this->game;
    this->game = &game;
    this->evaluation = func;
}


float AlfaBeta::evaluate() noexcept {
    return this->evaluation(this->game->get_controller(), this->maximazing);
}


BestMove AlfaBeta::get_best_move(const int &d) noexcept {
    auto depth = d? d: this->depth;
    this->maximazing = this->game->get_controller().get_current();
    auto best_move = this->minimax(1, true, -infinity/2, infinity/2);
    auto best_move1 = this->minimax(depth, true, -infinity/2, infinity/2);
    if (best_move1.piece == "") best_move = best_move1;
    std::cout << best_move.value << "\n";
    return best_move;
}


BestMove AlfaBeta::minimax(int depth, bool maximazing, float alfa, float beta) noexcept {
    if (this->game->is_finished() || depth == 0) {
        constexpr int multiply[] = {2, -2};
        float score = this->evaluation(this->game->get_controller(), this->maximazing) + depth * multiply[this->maximazing];
        return {score};
    }
    BestMove best_move = {maximazing? -infinity/2: infinity/2};
    std::unordered_map<std::string, std::vector<Coords>> valid_moves;
    this->game->set_valid_moves(valid_moves);
    for (const auto &move: valid_moves) {
        for (const auto &where: move.second) {
            this->game->get_controller().engine_move(move.first, where);
            auto result = this->minimax(depth-1, !maximazing, alfa, beta);
            if (maximazing) {
                if (result.value > best_move.value) {
                    best_move.value = result.value;
                    best_move.piece = move.first;
                    best_move.where = where;
                }
                alfa = std::max(alfa, best_move.value);
            } else {
                if (result.value < best_move.value) {
                    best_move.value = result.value;
                    best_move.piece = move.first;
                    best_move.where = where;
                }
                beta = std::min(beta, best_move.value);
            }
            this->game->get_controller().undo_move();
            if (beta <= alfa) return best_move;
        }
    }
    return best_move;
}
