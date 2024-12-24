#include <Hive>
#include <iostream>
#include <decorators.hpp>
#include <HiveAI>



int main(int argc, char **argv) {
    Game game;
    Command c;
    while(true) {
        std::cin >> c;
        c.execute(game);
    }
    // AlfaBeta a(game, heuristic1);
    // a.get_best_move();
    return 0;
}
