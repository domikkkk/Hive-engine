#ifndef GAMECONTROLLER_CPP
#define GAMECONTROLLER_CPP

#include <hive/gamecontroller.hpp>


void Controller::switch_turn() noexcept {
    switch (this->current)
    {
    case Color::WHITE:
        this->current = Color::BLACK;
        break;
    case Color::BLACK:
        this->current = Color::WHITE;
        break;
    default:
        this->current = Color::WHITE;
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


void Controller::move(const std::string &piece, const Coords &to) {
    auto insect = this->insects.find(piece);
    if (insect == this->insects.end()) {
        throw PieceNotExisting();     // Nie ma takiej figury
    }
    Coords &from = insect->second;
    if (from == Coords{-1, -1, -1}) { // nie istnieje jeszcze na planszy, więc trzeba dodać
        hive::Piece p = create_piece(piece);
        p.inPlay = true;
        this->board.add_piece(p, to);
    } else if (!this->board.move(from, to)) {
        throw InvalidMove();  // invalid move
    }
    this->insects[piece] = to;
    this->switch_turn();
}


void Controller::prepare_pieces() noexcept {
    std::unordered_map<char, int> quantity = {
        {Insect::bee, Insects::bee},
        {Insect::ant, Insects::ant},
        {Insect::beetle, Insects::beetle},
        {Insect::grasshopper, Insects::grasshopper},
        {Insect::spider, Insects::spider}
    };
    for (auto pair : quantity) {
        std::string piece(1, pair.first);
        if (pair.second == 1) {
            this->add_piece("w"+piece, {});
            this->add_piece("b"+piece, {});
            continue;
        }
        for (int i = 0; i < pair.second; ++i) {
            this->add_piece("w"+piece+std::to_string(i+1), {});
            this->add_piece("b"+piece+std::to_string(i+1), {});
        }
    }
}


std::unordered_map<std::string, Coords> &Controller::get_map() {
    return this->insects;
}


#endif
