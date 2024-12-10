#include <hive/board.hpp>
#include <queue>
#include <hive/namespaces.hpp>
#ifdef DEBUG
#include <iostream>
#endif


bool hive::Piece::operator==(const Piece &p) const noexcept {
    return this->type == p.type && this->color == p.color;
}


const std::string hive::Piece::to_str() const noexcept {
    std::string Id = this->id == 0 ? "" : std::to_string(this->id);
    return colorToString[this->color] + this->type + Id;
}


void hive::Board::add_piece(const Piece &insect, const Coords &where) {
    (*this)[where] = insect;
    this->moves.push_back(Move{where});
    ++this->count_insects;
}


void hive::Board::remove_piece(const Coords &c) noexcept {
    (*this)[c] = {};
    --this->count_insects;
}


void hive::Board::swap(const Coords &from, const Coords &to) noexcept {
    (*this)[to] = (*this)[from];
    (*this)[from] = {};
}


bool hive::Board::move(const Coords &from, const Coords &to) noexcept {
    if (from == to) return false;
    if ((*this)[to].type != Insect::notexists) return false;
    if ((*this)[from].type == Insect::notexists) return false;
    this->swap(from, to);
    this->moves.push_back(Move{from, to});
    return true;
}


const Move hive::Board::unmove() noexcept {
    const Move m = this->moves.back();
    this->moves.pop_back();

    if (!m.added) {
        this->swap(m.to, m.from);
    } else {
        this->remove_piece(m.to);
    }
    return m;
}


bool hive::Board::is_connected(const Coords &from, const Coords &without) noexcept {
    if (!this->count_insects) return true;
    std::queue<Coords> q;
    bool visited[Z][X][Y] = {false};
    std::size_t count_visits = 1;
    if (without != Coords{-1, -1, -1} && without != from) {
        visited[without.z][without.x + X/2][without.y + Y/2] = true;
        ++count_visits;
    }
    visited[0][from.x + X/2][from.y + Y/2] = true;
    q.push(from);
#ifdef DEBUG
        std::cout << "\nNew check\n";
#endif
    do {
        Coords c = q.front(); q.pop();
#ifdef DEBUG
        std::cout << "Visited " << c.x << ' ' << c.y << ' ' << c.z << '\n';
#endif
        auto neighbors = c.get_surrounding_locations();
        auto z_neighbors = c.get_in_Z();
        neighbors.insert(neighbors.end(), z_neighbors.begin(), z_neighbors.end());
        for (Coords neighbor: neighbors) {
            if (!visited[neighbor.z][neighbor.x + X/2][neighbor.y + Y/2]) {
                visited[neighbor.z][neighbor.x + X/2][neighbor.y + Y/2] = true;
                if ((*this)[neighbor].type != Insect::notexists) {
#ifdef DEBUG
                    std::cout << "\tAdded " << neighbor.x << ' ' << neighbor.y << ' ' << neighbor.z << '\n';
#endif
                    q.push(neighbor);
                    ++count_visits;
                }
            }
        }
    } while (!q.empty());
    return count_visits == this->count_insects;
}


std::size_t hive::Board::get_turns() const noexcept {
    return this->moves.get_move_counts();
}


Coords hive::Board::get_upper(Coords c) noexcept {
    Coords cc = c.get_neighbor(Directions::UP);
    while ((*this)[cc].type != Insect::notexists) {
        ++c.z;
        ++cc.z;
    }
    return c;
}


hive::Piece &hive::Board::operator()(const std::size_t &x, const std::size_t &y) noexcept {
    return this->fields[x + X/2][y + Y/2];
}


hive::Piece &hive::Board::operator[](const Coords &c) noexcept {
    return c.z? this->z_fields[c] : this->fields[c.x + X/2][c.y + Y/2];
}


hive::Piece create_piece(const std::string &piece) noexcept {
    Color color = piece[0] == 'w' ? Color::WHITE : piece[0] == 'b' ? Color::BLACK : Color::NONCOLOR;
    char type = piece[1];
    int id = piece.length() > 2 ? piece[2]-'0' : 0;
    return hive::Piece(id, type, color);
}


const Coords hive::Board::first_location = {0, 0};
const Coords hive::Board::second_location = {1, 0};
