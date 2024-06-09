#include <hive/gamecontroller.hpp>


void Controller::switch_turn() {
    this->whos_turn = ++this->whos_turn % PLAYERS;
}


const int &Controller::get_player() const {
    return this->whos_turn;
}
