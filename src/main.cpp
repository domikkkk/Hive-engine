#include <Hive>
#include <HiveAI>
#include <iostream>


int main(int argc, char **argv) {
    Controller<hive::Board, Coords> controller;
    std::cout << controller.get_player() << '\n';
    controller.switch_turn();
    std::cout << controller.get_player() << '\n';
    controller.switch_turn();
    controller.add_piece("ws1", Coords{0, 0});
    return 0;
}
