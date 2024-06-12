#include <hive/board.hpp>
#include <queue>
#ifdef DEBUG
#include <iostream>
#endif


hive::Board::~Board() {
    this->insects.clear();
}


void hive::Board::add_piece(const hive::Insect &i) {
    const auto& location = i.get_location();
    auto it = this->insects.find(location);
    if (it != this->insects.end()) return;  // Can't add. TODO make expection
    auto j = std::make_unique<hive::Insect>(i);
    this->insects[location] = std::move(j);
    this->moves.all.push_back(Move{location});
}


void hive::Board::remove_piece(const Coords &c) noexcept {
    auto it = this->insects.find(c);
    if (it != this->insects.end()) {
        // it->second.reset();  // because unique_ptr
        this->insects.erase(it);
    }
}


void hive::Board::remove_piece(hive::Insect *i) noexcept {
    this->remove_piece(i->get_location());
}


bool hive::Board::is_empty() const noexcept {
    return insects.empty();
}


void hive::Board::swap(const Coords &from, const Coords &to) noexcept {
    auto insect_from = this->insects.find(from);
    insect_from->second->move(to);
    this->insects[to] = std::move(insect_from->second);
    this->insects.erase(insect_from);
}


void hive::Board::move(const Coords &from, const Coords &to) {
    if (from == to) return;

    auto insect_from = this->insects.find(from);
    if (insect_from == this->insects.end()) return; // zrobić wyjątek

    auto insect_to = this->insects.find(to);
    if (insect_to != this->insects.end()) return; // zrobić wyjątek

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


bool hive::Board::is_connected() const noexcept {
    std::queue<Coords> q;
    std::unordered_map<Coords, bool, HashFn> visited(false);
    auto i = this->insects.begin()->second.get();
    if (!i) return true;
    Coords c = i->get_location();
    visited[c] = true;
    q.push(c);
    std::size_t count_visits = 1;
#ifdef DEBUG
        std::cout << "\nNew check\n";
#endif
    do {
        c = q.front(); q.pop();
#ifdef DEBUG
        std::cout << "visited " << c.x << ' ' << c.y << '\n';
#endif
        auto neighbors = c.get_surrounding_locations();
        for (Coords neighbor: neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                if (this->get_piece_at<hive::Insect>(neighbor) != nullptr) {
#ifdef DEBUG
                    std::cout << "\tAdded " << neighbor.x << ' ' << neighbor.y << '\n';
#endif
                    q.push(neighbor);
                    ++count_visits;
                }
            }
        }
    } while (!q.empty());
    return count_visits == this->insects.size();
}


hive::Insect *hive::Board::operator[](const Coords &c) const noexcept {
    return this->get_piece_at<hive::Insect>(c);
}
