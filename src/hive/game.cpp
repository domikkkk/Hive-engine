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
    if (!this->controller.validateQueen() && this->controller.get_turns() == 4) {
        std::vector<Coords> destinations;
        this->controller.legal_piece_placement(destinations);
        std::string piece = colorToString[this->controller.get_current()] + Insect::bee;
        valid_moves[piece] = destinations;
        return;
    }
    for (const auto &piece_in_hands: this->controller.get_hands()) {
        if (color_from_piece(piece_in_hands[0]) != this->controller.get_current()) continue;
        switch (piece_in_hands[1])
        {
        case Insect::bee:
            hand[piece_in_hands[1]] = 0;
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


Controller &Game::get_controller() noexcept {
    return this->controller;
}


const std::string Game::get_valid_moves() noexcept {
    std::string to_display = "";
    std::unordered_map<std::string, std::vector<Coords>> valid_moves;
    this->set_valid_moves(valid_moves);
    for (auto move: valid_moves) {
        for (auto where: move.second) {
            to_display += move.first + " ";
            auto adjacent = this->controller.find_adjacent(where);
            switch (adjacent.second)
            {
            case Directions::NE:
                to_display += adjacent.first + "/";
                break;
            case Directions::E:
                to_display += adjacent.first + "-";
                break;
            case Directions::S:
                to_display += adjacent.first + "\\";
                break;
            case Directions::SW:
                to_display += "/" + adjacent.first;
                break;
            case Directions::W:
                to_display += "-" + adjacent.first;
                break;
            case Directions::N:
                to_display += "\\" + adjacent.first;
                break;
            case Directions::UP:
                to_display += adjacent.first;
                break;
            case Directions::DEFAULT:
                to_display.erase(to_display.size()-1);
            default:
                break;
            }
            to_display += ";";
        }
    }
    return to_display;
}


const std::string Game::get_gamestring() const noexcept {
    std::string gamestring = this->gameType + ";";
    switch (this->state)
    {
    case State::NOTSTARTED:
        gamestring += GameState::notstarted;
        break;
    case State::INPROGRESS:
        gamestring += GameState::inprogress;
        break;
    case State::DRAW:
        gamestring += GameState::draw;
        break;
    case State::WHITEWINS:
        gamestring += GameState::whitewins;
        break;
    case State::BLACKWINS:
        gamestring += GameState::blackwins;
        break;
    default:
        break;
    }
    gamestring += ";";
    switch (this->controller.get_current())
    {
    case Color::WHITE:
        gamestring += "White[";
        break;
    case Color::BLACK:
        gamestring += "Black[";
    default:
        break;
    }
    gamestring += std::to_string(this->controller.get_turns()) + "]";
    for (auto str: this->moves) {
        gamestring += ';' + str;
    }
    return gamestring;
}


void Game::player_move(const struct Move_parameters &move) {
    Coords c = this->controller.find_destination(move.next_to_piece, move.direction);
    this->controller.move(move.what_piece, c);
    this->moves.push_back(move.str);
}


void Game::undo(const int &n) noexcept {
    for (int i = 0; i < n; ++i) {
        this->controller.undo_move();
        this->moves.pop_back();
    }
}
