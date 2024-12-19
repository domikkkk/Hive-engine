#include <hive/game.hpp>


void Game::change_state(const State &state) noexcept {
    this->state = state;
}


void Game::update() noexcept {
    if (this->moves.size() > 0) this->state = State::INPROGRESS;
}


void Game::set_valid_moves() noexcept {
    this->valid_moves.clear();
    std::unordered_map<char, char> hand;
    std::vector<std::string> pieces;
    for (auto piece_in_hands: this->controller.get_hands()) {
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
            std::string piece = this->controller.get_current() == Color::WHITE? "w" : "b";
            piece += info.first;
            if (info.first != 'w') piece += info.second;
            for (auto c: destinations) {
                this->valid_moves[piece].emplace_back(c);
            }
        }
    }
//     for (auto piece: this->controller.get_pieces()) {

//     }
}


const std::string Game::get_valid_moves() const noexcept {
    std::string to_display = "";
    for (auto move: this->valid_moves) {
        to_display += move.first + " ";
        for (auto where: move.second) {
            to_display += std::to_string(where.x) + " " + std::to_string(where.y) + "; ";
        }
        to_display += "\n";
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
