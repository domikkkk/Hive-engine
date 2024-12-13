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
    if (this->board.get_turns() <= 2) {
        Coords to_ret = this->current == Color::WHITE? this->board.first_location : this->board.second_location;
        return {to_ret};
    }
    std::vector<Coords> legal_places;
    bool visited[hive::X][hive::Y] = {false};
    for (auto piece: this->insects) {
        if (piece.second.z > 0) continue;   // jak jest to chrząszcz to również nie ma co patrzeć
        const Coords up = this->board.get_upper(piece.second);
        if (this->board[up].color != this->current) continue;   // jak wierzchnia jest koloru przeciwnika to nie ma co sprawdzać bo i tak wokół tego nic nie położymy
        const std::vector<Coords> possible_locations = piece.second.get_surrounding_locations();
        for (const Coords location: possible_locations) {
            if (this->board[location].type != Insect::notexists) continue;  // jeśli jest figura to nie położymy więc pomijamy dalsze
            if (visited[location.x + hive::X/2][location.y + hive::Y/2]) continue;  // jeśli juz sprawdzaliśmy dane pole to nie ma co ponownie
            visited[location.x + hive::X/2][location.y + hive::Y/2] = true;  // zapisujemy że sprawdzaliśmy
            if (!this->check_destination(location)) {
                legal_places.push_back(location);
            }
        }
    }
    return legal_places;
}


void Controller::move(const std::string &piece, const Coords &to) {
    auto pair = this->insects_off.find(piece);
    if (pair == this->insects_off.end()) throw PieceNotExisting(piece);
    if (color_from_piece(piece[0]) != this->current) throw InvalidMove("Can't move using opponent piece"); // czy na pewno ruch odpowiednią figurą (żeby nie pomylić kolorów)
    if (pair->second) { // nie istnieje jeszcze na planszy, więc trzeba dodać
        if (this->board.get_turns() > 2 && this->check_destination(to)) throw InvalidMove("Can't put new piece on the board next to the opponent"); // jeśli jest zły sąsiad to trzeba odrzucić
        hive::Piece p = create_piece(piece);
        p.inPlay = true;
        pair->second = false;
        this->board.add_piece(p, to);
    } else {
        auto from = this->insects[piece];
        if (from == to) throw std::invalid_argument("Can't be the same destination file");
        if (this->board[from].type == Insect::notexists) throw std::invalid_argument("Unexpected error");
        if (this->board[to].type != Insect::notexists) throw InvalidMove("Destination file is occupied");  // invalid move
        this->board.move(from, to);
    }
    this->insects[piece] = to;
    this->switch_turn();
}


void Controller::engine_move(const std::string &piece, const Coords &to) { // zakładamy, że robi to zawsze poprawnie
    auto pair = this->insects_off.find(piece);
    if (pair->second) {
        pair->second = false;
        hive::Piece p = create_piece(piece);
        this->board.add_piece(p, to);
    } else {
        auto from = this->insects[piece];
        this->board.move(from, to);
    }
    this->insects[piece] = to;
    this->switch_turn();
}


void Controller::undo_move() noexcept {
    const struct Move m = this->board.back();
    const std::string piece = this->board[m.to].to_str();
    if (m.added) {
        this->insects_off[piece] = true;
        this->insects.erase(piece);
    } else {
        this->insects[piece] = m.from;
    }
    this->switch_turn();
}


void Controller::prepare_pieces() {
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
            this->insects_off["w"+piece] = true;
            this->insects_off["b"+piece] = true;
            continue;
        }
        for (int i = 0; i < pair.second; ++i) {
            this->insects_off["w"+piece+std::to_string(i+1)] = true;
            this->insects_off["b"+piece+std::to_string(i+1)] = true;
        }
    }
}


Coords Controller::find_destination(const std::string &piece, Directions direction) const {
    if (this->board.get_turns() == 0) return this->board.first_location;
    auto a = this->insects_off.find(piece);
    if (a == this->insects_off.end()) throw PieceNotExisting(piece);
    if (a->second) throw PieceNotOnTheBoard(piece);
    return this->insects.find(piece)->second.get_neighbor(direction);
}


bool Controller::check_destination(const Coords &destination) {
    for (const Coords neigbor_location: destination.get_surrounding_locations()) {
        if (this->board[neigbor_location].type == Insect::notexists) continue; // jeśli koło potencjalnego pola jest inne puste to nie ma co
        const Coords upper = this->board.get_upper(neigbor_location); // bierzemy wierzchnią figure by sprawdzić kolor
        if (this->board[upper].color != this->current) {     // jeśli kolor jest przeciwnika to wykluczamy location jako potencjalne pole na dołożenie nowej figury
            return true;
        }
    }
    return false;
}


std::unordered_map<std::string, Coords> &Controller::get_pieces() noexcept {
    return this->insects;
}


hive::Board &Controller::get_board() noexcept {
    return this->board;
}


std::size_t Controller::get_turns() const noexcept {
    return this->board.get_turns() / 2 + 1;
}


const Color &Controller::get_current() const noexcept {
    return this->current;
}


Color color_from_piece(const char &c) noexcept {
    switch (c) {
    case 'w':
        return Color::WHITE;
    case 'b':
        return Color::BLACK;
    default:
        return Color::NONCOLOR;
    }
}


int get_id_from_piece(const std::string &piece) noexcept {
    return piece.length() > 2 ? piece[2]-'0' : 0;
}
