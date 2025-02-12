#include <engine/alfabeta.hpp>

constexpr bool use_minimax = false;

void AlfaBeta::new_game(Game &game, EvaluationFunc func, EvaluationFunc order) noexcept {
    this->game = &game;
    this->evaluation = func;
    this->to_order_moves = order;
}


const std::string &AlfaBeta::_name() const noexcept {
    return this->name;
}


const std::string &AlfaBeta::_version() const noexcept {
    return this->version;
}


void AlfaBeta::order_moves(const std::unordered_map<std::string, std::vector<Coords>> &all_moves, std::vector<PossibleBestMove> &sorted_moves, bool maximazing) noexcept {
    auto hash = this->game->get_controller().__key();
    auto entry = this->transpositiontable.find(hash);
    int was = 0;
    if (entry != this->transpositiontable.end()) {
        const auto &best_move = entry->second;
        sorted_moves.emplace_back(best_move.BestMove, best_move.Value);
        was = 1;
    }
    for (const auto &piece: all_moves) {
        for (const auto &where: piece.second) {
            if (was && where == sorted_moves[0].bestmove.where && piece.first == sorted_moves[0].bestmove.piece) {
                continue;
            }
            EMove move = {piece.first, where};
            // float eval = this->evaluate_move(move);  // to trzeba zastosować kiedyś i pozbyć się poniższego kodu
            this->game->get_controller().engine_move(piece.first, where);
            float eval = this->evaluate_to_order();
            this->game->get_controller().undo_move();
            sorted_moves.emplace_back(move, eval);
        }
    }
    if (sorted_moves.size() > 2) {
        std::sort(sorted_moves.begin() + was, sorted_moves.end(), [&](const PossibleBestMove &a, const PossibleBestMove &b) {
            return maximazing? a.value > b.value : a.value < b.value;
        });
    }
}


float AlfaBeta::evaluate_move(const EMove &move) noexcept {  // do dopisania
    auto &con = this->game->get_controller();
    auto &board = con.get_board();
    auto own_color = color_from_piece(move.piece[0]);
    con.engine_move(move.piece, move.where);
    float value = 0.0;
    int free_space = 0;
    for (const auto &c : move.where.get_surrounding_locations()) {
        if (board[c].type == Insect::bee) {
            value = opposite[own_color] == board[c].color? 6.0: board.is_connected(c)? -0.5: -6.0;
            con.undo_move();
            return value;
        } else if (board[c].type != Insect::notexists) {}
        //     if (opposite[own_color] == board[c].color){
        //         value = board.is_connected(c)? -1.0: 3.0;
        //     } else {
        //         value = board.is_connected(c)? 1.0: -3.0;
        //     }
        // } else {
        //     ++free_space;
        // } 
    }
    con.undo_move();
    return value + (float)free_space;
}


EMove AlfaBeta::get_best_move_with_time_limit(const int &time) noexcept {
    this->maximazing = this->game->get_controller().get_current();
    EMove best_move;
    struct CancellationToken token = CancellationToken(CancellationToken::TimeLimit(time));
#ifdef INFO
    setbuf(stdout, NULL);
#endif
    for (int depth = 1; depth <= this->max_depth; ++depth) {
        auto result = use_minimax ? this->minimax(depth, true, -infinity, infinity, token) : this->negamax(depth, -infinity, infinity, token);
        if (result.found) best_move = result.bestmove;
        if (result.value >= infinity) return best_move;
        if (token.is_end()) {
            break;
        }
#ifdef INFO
        printf("info depth: %d, value: %f\n", depth, result.value);
#endif
    }
    return best_move;
}


EMove AlfaBeta::get_best_move(const int &d) noexcept {
    auto depth = d? d: this->max_depth;
    this->maximazing = this->game->get_controller().get_current();
    auto good_move = use_minimax ? this->minimax(1, true, -infinity, infinity) : this->negamax(1, -infinity, infinity); // może mat w 1 i żeby znaleźć sobie potencjalny ruch
    if (!good_move.found) {good_move.bestmove.piece = "pass"; return good_move.bestmove;}
    if (good_move.value >= infinity - this->max_depth * 2) return good_move.bestmove;  // jeśli mat w 1 niech zagra
    auto better_move = use_minimax ? this->minimax(depth, true, -infinity, infinity) : this->negamax(depth, -infinity, infinity); // może mat w 1 i żeby znaleźć sobie potencjalny ruch
    return better_move.found? better_move.bestmove: good_move.bestmove; // jeśli pass to pewnie znalazł że zawsze przegrywa więc niech zagra jakikolwiek ruch
}


PossibleBestMove AlfaBeta::minimax(int depth, bool maximazing, float alfa, float beta, const struct CancellationToken &token) noexcept {
    if (depth == 0 || this->game->is_finished()) {
        return {this->evaluate()};
    }

    auto hash = this->game->get_controller().__key();
    auto entry = this->transpositiontable.find(hash);

    if (entry != this->transpositiontable.end()) {
        const auto &tt_entry = entry->second;
        if (tt_entry.Depth >= depth) {
            if (tt_entry.Type == EntryType::Exact) return {tt_entry.BestMove, tt_entry.Value};
            else if (tt_entry.Type == EntryType::LowerBound) alfa = std::max(alfa, tt_entry.Value);
            else if (tt_entry.Type == EntryType::UpperBound) beta = std::min(beta, tt_entry.Value);
            if (alfa >= beta) return {tt_entry.BestMove, tt_entry.Value};
        }
    }

    PossibleBestMove possible_move = {maximazing? -infinity: infinity};
    std::unordered_map<std::string, std::vector<Coords>> valid_moves;
    this->game->set_valid_moves(valid_moves);
    std::vector<PossibleBestMove> moves;
    this->order_moves(valid_moves, moves, maximazing);
    if (moves.size() != 0){
        possible_move.bestmove = moves[0].bestmove;
        possible_move.found = true;
    }
    for (const auto &move: moves) {
        if (token.defined && token.is_end()) break;
        this->game->get_controller().engine_move(move.bestmove.piece, move.bestmove.where);
        auto result = this->minimax(depth-1, !maximazing, alfa, beta, token);
        if (maximazing) {
            if (result.value > possible_move.value) {
                possible_move.value = result.value;
                possible_move.bestmove = move.bestmove;
                possible_move.found = true;
            }
            alfa = std::max(alfa, possible_move.value);
        } else {
            if (result.value < possible_move.value) {
                possible_move.value = result.value;
                possible_move.bestmove = move.bestmove;
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

PossibleBestMove AlfaBeta::negamax(int depth, float alfa, float beta, const struct CancellationToken &token) noexcept {
    Color color = this->game->get_controller().get_player();
    if (depth == 0 || this->game->is_finished()) {
        auto eval = this->evaluate();
        if (color == Color::WHITE)
            return eval;
        else
            return -eval;
    }

    auto hash = this->game->get_controller().__key();
    auto entry = this->transpositiontable.find(hash);

    if (entry != this->transpositiontable.end()) {
        const TranspositionTableEntry &tt_entry = entry->second;
        // TODO: this should not be done in PV nodes
        // TODO: this should only be done if tt_entry.BestMove is legal
        if (depth <= tt_entry.Depth &&
            ((tt_entry.Type == EntryType::Exact) ||
             (tt_entry.Type == EntryType::LowerBound && tt_entry.Value <= alfa) ||
             (tt_entry.Type == EntryType::UpperBound && tt_entry.Value >= beta))) {
            return {tt_entry.BestMove, tt_entry.Value};
        }
    }

    PossibleBestMove possible_move = -infinity;
    std::unordered_map<std::string, std::vector<Coords>> valid_moves;
    this->game->set_valid_moves(valid_moves);
    std::vector<PossibleBestMove> moves;
    this->order_moves(valid_moves, moves, Color::WHITE);

    for (const auto &move: moves) {
        if (token.defined && token.is_end()) break;
        possible_move.found = true;
        this->game->get_controller().engine_move(move.bestmove.piece, move.bestmove.where);
        auto result = this->negamax(depth - 1, -beta, -alfa, token);
        this->game->get_controller().undo_move();

        if (result.value <= possible_move.value)
            continue;

        possible_move.value = result.value;
        possible_move.bestmove = move.bestmove;

        if (possible_move.value >= beta)
            break;

        if (possible_move.value > alfa) {
            alfa = possible_move.value;
        }
    }

    if (!possible_move.found) {
        // TODO: return checkmate
        return possible_move;
    }

    this->transpositiontable[hash] = TranspositionTableEntry(
        possible_move.value, depth, possible_move.bestmove,
        possible_move.value <= alfa   ? EntryType::LowerBound
        : possible_move.value >= beta ? EntryType::UpperBound
                                      : EntryType::Exact);

    return possible_move;
}
