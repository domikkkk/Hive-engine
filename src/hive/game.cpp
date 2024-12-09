#include <hive/game.hpp>


void Game::change_state(const State &state) noexcept {
    this->state = state;
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
    gamestring += std::to_string(this->controller.get_turns()) + "]\n";
    return gamestring;
}


void Game::move(bool player) {
    
}
