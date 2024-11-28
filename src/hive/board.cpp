#include <hive/board.hpp>
#include <queue>
#include <hive/namespaces.hpp>
#ifdef DEBUG
#include <iostream>
#endif


bool hive::Piece::operator==(const Piece &p) noexcept {
    return this->type == p.type && this->color == p.color;
}


void hive::Board::add_piece(const Piece &insect, const Coords &where) {
    (*this)[where] = insect;
    this->moves.all.push_back(Move{where});
    ++this->count_insects;
}


void hive::Board::remove_piece(const Coords &c) noexcept {
    (*this)[c] = {0, Insect::notexists};
    --this->count_insects;
}


void hive::Board::swap(const Coords &from, const Coords &to) noexcept {
    (*this)[to] = (*this)[from];
    (*this)[from] = {0, Insect::notexists};
}


void hive::Board::move(const Coords &from, const Coords &to) noexcept {
    if (from == to) return;
    if ((*this)[to].type != Insect::notexists) return;
    if ((*this)[from].type == Insect::notexists) return;
    this->swap(from, to);
    this->moves.all.push_back(Move{from, to});
}


const Move hive::Board::unmove() noexcept {
    const Move m = this->moves.all.back();
    this->moves.all.pop_back();
    
    if (!m.added) {
        this->swap(m.to, m.from);
    } else {
        this->remove_piece(m.to);
    }
    return m;
}


bool hive::Board::is_connected() noexcept {
    std::queue<Coords> q;
    bool visited[Z][X][Y] = {false};
    if (!this->count_insects) return true;
    Coords c = {0, 0};
    visited[0][c.x + X/2][c.y + Y/2] = true;
    q.push(c);
    std::size_t count_visits = 1;
#ifdef DEBUG
        std::cout << "\nNew check\n";
#endif
    do {
        c = q.front(); q.pop();
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


hive::Piece &hive::Board::operator()(const std::size_t &x, const std::size_t &y) noexcept {
    return this->fields[x + X/2][y + Y/2];
}


hive::Piece &hive::Board::operator[](const Coords &c) noexcept {
    if (c.z > 0) {
        return this->z_fields[c];
    }
    return this->fields[c.x + X/2][c.y + Y/2];
}


const Coords hive::Board::first_location = {0, 0};
const Coords hive::Board::second_location = {0, 1};
