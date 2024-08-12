#include <hive/board.hpp>
#include <queue>
#include <hive/namespaces.hpp>
#ifdef DEBUG
#include <iostream>
#endif


void hive::Board::add_piece(const char &insect, const Coords &where) {
    this->fields[where.x + hive::X/2][where.y + hive::Y/2] = insect;
    this->moves.all.push_back(Move{where});
    ++this->insects;
}


void hive::Board::remove_piece(const Coords &c) noexcept {
    (*this)(c.x, c.y) = Insect::empty;
    --this->insects;
}


void hive::Board::swap(const Coords &from, const Coords &to) noexcept {
    (*this)(to.x, to.y) = (*this)(from.x, from.y);
    (*this)(from.x, from.y) = Insect::empty;
}


void hive::Board::move(const Coords &from, const Coords &to) noexcept {
    if (from == to) return;
    if ((*this)(to.x, to.y) == Insect::empty) return;
    if ((*this)(from.x, from.y) != Insect::empty) return;
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
    bool visited[X][Y] = {false};
    // auto i = 0;
    // if (!i) return true;
    Coords c = {0, 1};
    visited[c.x + X/2][c.y + Y/2] = true;
    q.push(c);
    std::size_t count_visits = 1;
#ifdef DEBUG
        std::cout << "\nNew check\n";
#endif
    do {
        c = q.front(); q.pop();
#ifdef DEBUG
        std::cout << "Visited " << c.x << ' ' << c.y << '\n';
#endif
        auto neighbors = c.get_surrounding_locations();
        for (Coords neighbor: neighbors) {
            if (!visited[neighbor.x + X/2][neighbor.y + Y/2]) {
                visited[neighbor.x + X/2][neighbor.y + Y/2] = true;
                if ((*this)[neighbor] != Insect::notexists) {
#ifdef DEBUG
                    std::cout << "\tAdded " << neighbor.x << ' ' << neighbor.y << '\n';
#endif
                    q.push(neighbor);
                    ++count_visits;
                }
            }
        }
    } while (!q.empty());
    return count_visits == this->insects;
}


char &hive::Board::operator()(const std::size_t &x, const std::size_t &y) noexcept {
    return this->fields[x + X/2][y + Y/2];
}


char &hive::Board::operator[](const Coords &c) noexcept {
    return (*this)(c.x, c.y);
}


const Coords hive::Board::first_location = {0, 1};
const Coords hive::Board::second_location = {0, -1};
