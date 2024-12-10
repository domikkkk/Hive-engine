#include <hive/game.hpp>


void Game::change_state(const State &state) noexcept {
    this->state = state;
}


void Game::update() noexcept {
    if (this->moves.size() > 0) this->state = State::INPROGRESS;
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
