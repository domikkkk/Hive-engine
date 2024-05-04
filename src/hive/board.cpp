#include <hive/board.hpp>


void hive::Board::add_piece(hive::Piece *p) {
    this->pieces.push_back(std::make_unique<hive::Piece>(*p));
    p->set_board(this);
}


bool hive::Board::is_empty() const {
    return pieces.empty();
}


std::vector<Coords> get_surrounding_locations(const Coords &c) {
    std::vector<Coords> neighbors;
    neighbors.reserve(6);
    for (int i = 0; i < 6; ++i) {
        neighbors.push_back(c + movements(i));
    }
    return neighbors;
}


Coords movements(int i) {
    switch (i)
    {
    case 0:  // N
        return {0, 2};
    case 1:  // NE
        return {1, 1};
    case 2:  // SE
        return {1, -1};
    case 3:  // S
        return {0, -2};
    case 4:  // SW
        return {-1, -1};
    case 5:  // NW
        return {-1, 1};
    default:
        return {200, 200};  // unexpected error
    }
}
