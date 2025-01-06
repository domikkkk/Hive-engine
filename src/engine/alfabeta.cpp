#include <engine/alfabeta.hpp>
#include <iostream>


void AlfaBeta::set_game(Game &game, EvaluationFunc func) noexcept {
    this->game = &game;
    this->evaluation = func;
}


float AlfaBeta::evaluate() noexcept {
    return this->evaluation(this->game->get_controller(), this->maximazing);
}


EMove AlfaBeta::get_best_move(const int &d) noexcept {
    auto depth = d? d: this->depth;
    this->maximazing = this->game->get_controller().get_current();
    auto good_move = this->minimax(1, true, -infinity, infinity);
    if (!good_move.found) {good_move.bestmove.piece = "pass"; return good_move.bestmove;}
    if (good_move.value >= infinity - 20.0) return good_move.bestmove;  // jeśli mat w 1 niech zagra
    auto better_move = this->minimax(depth, true, -infinity, infinity);
    return better_move.found? better_move.bestmove: good_move.bestmove; // jeśli pass to pewnie znalazł że zawsze przegrywa więc niech zagra jakikolwiek ruch
}


PossibleMove AlfaBeta::minimax(int depth, bool maximazing, float alfa, float beta) noexcept {
    if (this->game->is_finished() || depth == 0) {
        return {this->evaluate() + depth * multiply[this->maximazing]};
    }

    auto hash = this->game->get_controller().__key();
    auto entry = this->transpositiontable.find(hash);

    if (entry != this->transpositiontable.end()) {
        const auto &tt_entry = entry->second;
        if (tt_entry.Depth >= depth) {
            if (tt_entry.Type == EntryType::Exact) {
                return {tt_entry.Value};
            } else if (tt_entry.Type == EntryType::LowerBound && maximazing) {
                alfa = std::max(alfa, tt_entry.Value);
            } else if (tt_entry.Type == EntryType::UpperBound && !maximazing) {
                beta = std::min(beta, tt_entry.Value);
            }
        }
    }

    PossibleMove possible_move = {maximazing? -infinity: infinity};
    std::unordered_map<std::string, std::vector<Coords>> valid_moves;
    this->game->set_valid_moves(valid_moves);
    for (const auto &move: valid_moves) {
        for (const auto &where: move.second) {
            this->game->get_controller().engine_move(move.first, where);
            auto result = this->minimax(depth-1, !maximazing, alfa, beta);
            if (maximazing) {
                if (result.value > possible_move.value) {
                    possible_move.value = result.value;
                    possible_move.bestmove = {move.first, where};
                    possible_move.found = true;
                }
                alfa = std::max(alfa, possible_move.value);
            } else {
                if (result.value < possible_move.value) {
                    possible_move.value = result.value;
                    possible_move.bestmove = {move.first, where};
                    possible_move.found = true;
                }
                beta = std::min(beta, possible_move.value);
            }
            this->game->get_controller().undo_move();
            if (beta <= alfa) return possible_move;
        }
    }
    EntryType entry_type = (maximazing ? EntryType::UpperBound : EntryType::LowerBound);
    this->transpositiontable[hash] = TranspositionTableEntry{possible_move.value, depth, possible_move.bestmove, entry_type};
    return possible_move;
}
