#include <hive/game.hpp>


void Game::change_state(const State &state) noexcept {
    this->state = state;
}


void Game::update() noexcept {
    if (this->moves.size() > 0) this->state = State::INPROGRESS;
}


void Game::set_valid_moves(std::unordered_map<std::string, std::vector<Coords>> &valid_moves) noexcept {
    std::unordered_map<char, char> hand;
    std::vector<std::string> pieces;
    std::vector<Coords> destinations;
    this->controller.legal_piece_placement(destinations);
    if (this->controller.get_turns() == 4 && !this->controller.validateQueen()) {
        std::string piece = colorToString[this->controller.get_current()] + Insect::bee;
        valid_moves[piece] = destinations;
        return;
    }
    for (const auto &piece_in_hands: this->controller.get_hands()) {
        if (color_from_piece(piece_in_hands[0]) != this->controller.get_current()) continue;
        switch (piece_in_hands[1])
        {
        case Insect::bee:
            if (this->controller.get_turns() != 1) hand[piece_in_hands[1]] = 0;
            continue;
        default:
            if (hand.find(piece_in_hands[1]) == hand.end()) hand[piece_in_hands[1]] = piece_in_hands[2];
            else if (hand[piece_in_hands[1]] > piece_in_hands[2]) hand[piece_in_hands[1]] = piece_in_hands[2];
        }
    }
    if (hand.size() != 0) {
        std::vector<Coords> destinations;
        this->controller.legal_piece_placement(destinations);
        for (auto info: hand) {
            std::string piece = colorToString[this->controller.get_current()];
            piece += info.first;
            if (info.first != Insect::bee) piece += info.second;
            valid_moves[piece] = destinations;
        }
    }
    if (!this->controller.validateQueen()) return;
    for (const auto &piece: this->controller.get_pieces()) {
        if (color_from_piece(piece.first[0]) != this->controller.get_current()) continue;
        if (!this->controller.can_move_on_board(piece.first)) continue;
        hive::Ability ability = hive::gen_ability(piece.first[1]);
        if (ability.can_hop) {
            this->controller.hoppable_locations(piece.first, valid_moves[piece.first]);
            continue;
        } else if (ability.can_crawl) {
            this->controller.beetle_locations(piece.first, valid_moves[piece.first]);
        } else {
            this->controller.movable_locations(piece.first, valid_moves[piece.first], ability.how_far);
        }
    }
}


void Game::player_move(const struct Move_parameters &move) {
    Coords c = this->controller.find_destination(move.next_to_piece, move.direction);
    this->controller.move(move.what_piece, c);
    this->moves.push_back(move.str);
}


void Game::undo(const int &n) noexcept {
    for (int i = 0; i < std::min(n, (int)this->moves.size()); ++i) {
        this->controller.undo_move();
        this->moves.pop_back();
    }
}


bool Game::is_finished() noexcept {
    const auto &pieces = this->controller.get_pieces();
    const auto &current = this->controller.get_current();
    if (pieces.find(colorToString[current]+Insect::bee) == pieces.end()) return false;
    return this->controller.count_queen_surrounded(current) == 6; // sprawdzam po ruchu danego gracza/silnika czy ma pszczołe otoczoną
}
