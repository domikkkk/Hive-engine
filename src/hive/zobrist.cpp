#include <hive/zobrist.hpp>


void ZobristHash::switch_turn() noexcept {
    this->_hash ^= hashByColor;
}


void ZobristHash::Xor(const std::string &piece, const int &q, const int &c, const int &s) noexcept {
    if (piece[1] == 'B') {
        int bettle;
        switch (piece[0]) {
        case 'w':
            bettle = 0;
            break;
        case 'b':
            bettle = 1;
            break;
        default:
            bettle = 0;
        }
        this->_hash ^= this->hashByBettle[hive::bettles[bettle][piece[2] - 49]][s];   // -49 bo '1' = 49
    }
    this->_hash ^= this->hashByPosition[this->insect_index[piece]][hive::X/2 + q][hive::Y/2 + c];
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
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < hive::Z; ++j) {
            this->hashByBettle[i][j] = this->rand64();
        }
    }
}
