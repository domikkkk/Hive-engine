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


bool Controller::is_finished() noexcept {
    const Coords &queen = this->insects[colorToString[this->current]+"Q"];
    const std::vector<Coords> neighbors = queen.get_surrounding_locations();
    for (const Coords neighbor: neighbors) {
        if (this->board[neighbor].type == Insect::notexists) {
            return false;
        }
    }
    return true;
}


bool Controller::validateQueens() const noexcept {
    if (this->insects.at(colorToString[this->current] + "Q") == Coords{-1, -1, -1}) return false;
    return true;
}


bool Controller::can_move_on_board() const noexcept {
    return this->board.get_turns() > hive::turns ? true : this->validateQueens();
}


std::vector<Coords> Controller::legal_piece_placement() noexcept {
    if (this->board.get_turns() == 1 && this->current == Color::WHITE) return {this->board.first_location};
    if (this->board.get_turns() == 1 && this->current == Color::BLACK) return {this->board.second_location}; 
    std::vector<Coords> legal_places;
    bool visited[hive::X][hive::Y] = {false};
    for (auto piece: this->insects) {
        if (piece.second == Coords{-1, -1, -1}) continue;   // czy w ogole istnieje?
        if (color_from_string(piece.first[0]) != this->current) continue;   // jak jest przeciwna figura to nie ma co sprawdzać bo i tak wokół niej nic nie położymy
        if (piece.second.z > 0) continue;   // jak jest to chrząszcz to również nie ma co patrzeć
        const std::vector<Coords> possible_locations = piece.second.get_surrounding_locations();
        for (const Coords location: possible_locations) {
            if (this->board[location].type != Insect::notexists) continue;
            if (visited[location.x + hive::X/2][location.y + hive::Y/2]) continue;
            visited[location.x + hive::X/2][location.y + hive::Y/2] = true;
            bool hasEnemyNeighbor = false;
            for (const Coords neigbor_location: location.get_surrounding_locations()) {
                if (this->board[neigbor_location].type == Insect::notexists) continue;
                const Coords upper = this->board.get_upper(neigbor_location);
                if (this->board[upper].color != this->current){
                    hasEnemyNeighbor = true;
                    break;
                }
            }
            if (!hasEnemyNeighbor) {
                legal_places.push_back(location);
            }
        }
    }
    return legal_places;
}


void Controller::move(const std::string &piece, const Coords &to) {
    auto insect = this->insects.find(piece);
    if (insect == this->insects.end()) {
        throw PieceNotExisting();     // Nie ma takiej figury
    }
    if (color_from_string(piece[0]) != this->current) throw InvalidMove(); // czy na pewno ruch odpowiednią figurą (żeby nie pomylić kolorów)
    Coords &from = insect->second;
    if (from == Coords{-1, -1, -1}) { // nie istnieje jeszcze na planszy, więc trzeba dodać
        // if (this->legal_piece_placement(piece)) throw InvalidMove();
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
    const std::unordered_map<char, int> quantity = {
        {Insect::bee, Insects::bee},
        {Insect::ant, Insects::ant},
        {Insect::beetle, Insects::beetle},
        {Insect::grasshopper, Insects::grasshopper},
        {Insect::spider, Insects::spider}
    };
    for (const auto pair : quantity) {
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


std::unordered_map<std::string, Coords> &Controller::get_pieces() noexcept {
    return this->insects;
}


hive::Board &Controller::get_board() noexcept {
    return this->board;
}


Color color_from_string(const char &c) noexcept {
    switch (c) {
    case 'w':
        return Color::WHITE;
    case 'b':
        return Color::BLACK;
    default:
        return Color::NONCOLOR;
    }
}


#endif
