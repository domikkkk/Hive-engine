#include <engine/transpositionTable.hpp>


void TransposistionTable::_delete() noexcept {
    if (this->table_.empty()) return;
    auto iter = this->table_.begin(); // usuwanie pierwszego wpisu
    this->table_.erase(iter);
}
