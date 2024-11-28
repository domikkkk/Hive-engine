#ifndef GAMECONTROLLER_CPP
#define GAMECONTROLLER_CPP

#include <hive/gamecontroller.hpp>


void Controller::switch_turn() noexcept {
    switch (this->current)
    {
    case WHITE:
        this->current = BLACK;
        break;
    case BLACK:
        this->current = WHITE;
        break;
    default:
        this->current = WHITE;
        break;
    }
}


const Color &Controller::get_player() const noexcept {
    return this->current;
}


void Controller::add_piece(const std::string &piece, const Coords &where) noexcept {
    this->insects[piece] = where;
}


bool Controller::is_finished(const Color &c) noexcept {
    const Coords &queen = this->insects[colorToString[c] + "Q"];
    std::vector<Coords> neighbors = queen.get_surrounding_locations();
    for (Coords neighbor: neighbors) {
        if (this->board[neighbor].type == Insect::notexists) {
            return false;
        }
    }
    return true;
}


void Controller::move(const std::string &piece, const Coords &to) noexcept {
    auto insect = this->insects.find(piece);
    if (insect == this->insects.end()) {
        return;     // can't find piece
    }
    Coords &from = insect->second;
    if (!this->board.move(from, to)) {
        return;  // invalid move
    }
    this->insects[piece] = to;
}


#endif
