#include <engine/alfabeta.hpp>
#include <iostream>
#include <chrono>


void AlfaBeta::new_game(Game &game, EvaluationFunc func) noexcept {
    this->game = &game;
    this->evaluation = func;
}


float AlfaBeta::evaluate() noexcept {
    return this->evaluation(this->game->get_controller(), this->maximazing);
}


const std::string &AlfaBeta::_name() const noexcept {
    return this->name;
}


const std::string &AlfaBeta::_version() const noexcept {
    return this->version;
}


void AlfaBeta::order_moves(const std::unordered_map<std::string, std::vector<Coords>> &all_moves, std::vector<EMove> &sorted_moves) noexcept {
    for (const auto &piece: all_moves) {
        for (const auto &where: piece.second) {
            sorted_moves.emplace_back(piece.first, where);
        }
    }
    auto hash = this->game->get_controller().__key();
    auto entry = this->transpositiontable.find(hash);
    if (entry != this->transpositiontable.end()) {
        const auto &best_move = entry->second.BestMove;
        auto it = std::find_if(sorted_moves.begin(), sorted_moves.end(), [&](const EMove &m) {
            return m.piece == best_move.piece && m.where == best_move.where;
        });
        if (it != sorted_moves.end()) {
            std::iter_swap(it, sorted_moves.begin());
        }
    }

    // Posortuj pozostałe ruchy według heurystyki
    std::sort(sorted_moves.begin() + 1, sorted_moves.end(), [&](const EMove &a, const EMove &b) {
        this->game->get_controller().engine_move(a.piece, a.where);
        float eval_a = this->evaluate();
        this->game->get_controller().undo_move();

        this->game->get_controller().engine_move(b.piece, b.where);
        float eval_b = this->evaluate();
        this->game->get_controller().undo_move();

        return eval_a > eval_b;
    });
}


EMove AlfaBeta::get_best_move_with_time_limit(const int &time) noexcept {
    using Clock = std::chrono::steady_clock;
    auto time_limit = std::chrono::seconds(time);
    this->maximazing = this->game->get_controller().get_current();
    EMove best_move;
    auto start_time = Clock::now();
    for (int depth = 1; depth < this->max_depth; ++depth) {
        auto result = this->minimax(depth, true, -infinity, infinity);
        if (result.found) {
            best_move = result.bestmove;
        }
        auto now = Clock::now();
        if (now - start_time >= time_limit) {
            break;
        }
    }
    return best_move;
}


EMove AlfaBeta::get_best_move(const int &d) noexcept {
    auto depth = d? d: this->max_depth;
    this->maximazing = this->game->get_controller().get_current();
    auto good_move = this->minimax(1, true, -infinity, infinity);  // może mat w 1 i żeby znaleźć sobie potencjalny ruch
    if (!good_move.found) {good_move.bestmove.piece = "pass"; return good_move.bestmove;}
    if (good_move.value >= infinity - this->max_depth * 2) return good_move.bestmove;  // jeśli mat w 1 niech zagra
    auto better_move = this->minimax(depth, true, -infinity, infinity);
    return better_move.found? better_move.bestmove: good_move.bestmove; // jeśli pass to pewnie znalazł że zawsze przegrywa więc niech zagra jakikolwiek ruch
}


PossibleBestMove AlfaBeta::minimax(int depth, bool maximazing, float alfa, float beta) noexcept {
    if (depth == 0 || this->game->is_finished()) {
        return {this->evaluate() + depth * multiply[this->maximazing]};
    }

    auto hash = this->game->get_controller().__key();
    auto entry = this->transpositiontable.find(hash);

    if (entry != this->transpositiontable.end()) {
        const auto &tt_entry = entry->second;
        if (tt_entry.Depth >= depth) {
            if (tt_entry.Type == EntryType::Exact) return {tt_entry.Value};
            else if (tt_entry.Type == EntryType::LowerBound) alfa = std::max(alfa, tt_entry.Value);
            else if (tt_entry.Type == EntryType::UpperBound) beta = std::min(beta, tt_entry.Value);
            if (alfa >= beta) return {tt_entry.Value};
        }
    }

    PossibleBestMove possible_move = {maximazing? -infinity: infinity};
    std::unordered_map<std::string, std::vector<Coords>> valid_moves;
    this->game->set_valid_moves(valid_moves);
    std::vector<EMove> moves;
    this->order_moves(valid_moves, moves);
    for (const auto &move: moves) {
        this->game->get_controller().engine_move(move.piece, move.where);
        auto result = this->minimax(depth-1, !maximazing, alfa, beta);
        if (maximazing) {
            if (result.value > possible_move.value) {
                possible_move.value = result.value;
                possible_move.bestmove = {move.piece, move.where};
                possible_move.found = true;
            }
            alfa = std::max(alfa, possible_move.value);
        } else {
            if (result.value < possible_move.value) {
                possible_move.value = result.value;
                possible_move.bestmove = {move.piece, move.where};
                possible_move.found = true;
            }
            beta = std::min(beta, possible_move.value);
        }
        this->game->get_controller().undo_move();
        if (beta <= alfa) return possible_move;
    }
    if (possible_move.found) {
        EntryType entry_type = maximazing ? EntryType::UpperBound : EntryType::LowerBound;
        if (alfa < beta) entry_type = EntryType::Exact;
        this->transpositiontable[hash] = TranspositionTableEntry(possible_move.value, depth, possible_move.bestmove, entry_type);
    }
    return possible_move;
}
