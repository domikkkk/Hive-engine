#include <hive/zobrist.hpp>


void ZobristHash::switch_turn() noexcept {
    this->_hash ^= hashByColor;
}


void ZobristHash::togglePiece(const std::string &piece, const int &q, const int &c, const int &s) noexcept {
    this->_hash ^= this->hashByPosition[this->insect_index[piece]][hive::X/2 + q][hive::Y/2 + c];
    this->_hash ^= this->hashByStack[s];
}


uint64_t ZobristHash::rand64() noexcept {
    this->_next = this->_next * 1103515245 + 12345;
    return this->_next;
}


ZobristHash::ZobristHash() noexcept {
    this->_next = 1;
    this->hashByColor = this->rand64();
    for (int pn=0; pn<number; ++pn) {
        for (int r=0; r<hive::X; ++r) {
            for (int c=0; c<hive::Y; ++c) {
                this->hashByPosition[pn][r][c] = this->rand64();
            }
        }
    }
    for (int z=0; z<hive::Z; ++z) {
        this->hashByStack[z] = this->rand64();
    }
}
