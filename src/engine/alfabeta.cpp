#include <engine/alfabeta.hpp>


std::pair<std::string, Coords> AlfaBeta::get_best_move() noexcept {
    this->maximazing = this->game.get_controller().get_current();
    this->minimazing = opposite[this->maximazing];
    return {};
}

