#include <hive/game.hpp>


void Game::update() noexcept {
    this->state = this->moves.size()? State::INPROGRESS: State::NOTSTARTED;
    bool w = this->controller.count_queen_surrounded(Color::WHITE) == 6;
    bool b = this->controller.count_queen_surrounded(Color::BLACK) == 6;
    if (w && b) this->state = State::DRAW;
    else if (w) this->state = State::BLACKWINS;
    else if (b) this->state = State::WHITEWINS;
}


void Game::pass() noexcept {
    this->controller.pass();
    this->moves.push_back(Instrucions::pass);
}


void Game::set_valid_moves(std::unordered_map<std::string, std::vector<Coords>> &valid_moves) noexcept {
    std::unordered_map<char, char> hand;
    std::vector<std::string> pieces;
    std::vector<Coords> destinations;
    if (!this->controller.get_hands().empty()) this->controller.legal_piece_placement(destinations);
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
        for (auto info: hand) {
            std::string piece = colorToString[this->controller.get_current()];
            piece += info.first;
            if (info.first != Insect::bee) piece += info.second;
            valid_moves[piece] = destinations;
        }
    }
    if (!this->controller.validateQueen()) return;
    for (const auto &piece: this->controller.pieces_possible_to_move()) {
        hive::Ability ability = hive::gen_ability(piece[1]);
        if (ability.can_hop) {
            this->controller.hoppable_locations(piece, valid_moves[piece]);
        } else if (ability.can_crawl) {
            this->controller.beetle_locations(piece, valid_moves[piece]);
        } else {
            this->controller.movable_locations(piece, valid_moves[piece], ability.how_far);
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
    const auto &current = this->controller.get_current();
    const auto enemy = opposite[current];
    return this->controller.count_queen_surrounded(current) == 6 || this->controller.count_queen_surrounded(enemy) == 6; // sprawdzam po ruchu danego gracza/silnika czy ma pszczołe otoczoną
}
