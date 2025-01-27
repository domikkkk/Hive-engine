#include <hive/zobrist.hpp>


void ZobristHash::switch_turn() noexcept {
    this->_hash ^= hashByColor;
}


void ZobristHash::Xor(const std::string &piece, const int &q, const int &c, const int &s) noexcept {
    this->_hash ^= this->hashByPosition[this->insect_index[piece]][hive::X/2 + q][hive::Y/2 + c][s];
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
                for (int s=0; s<hive::Z; ++s) {
                    this->hashByPosition[pn][r][c][s] = this->rand64();
                }
            }
        }
    }
}
