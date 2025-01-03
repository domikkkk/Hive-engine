#include <Hive>
#include <iostream>
#include <decorators.hpp>



int main(int argc, char **argv) {
    Protocol protocol;
    Command c;
    std::cout << "id Moj silnik v0.1.0\nok\n"; 
    while(true) {
        std::cin >> c;
        c.execute(protocol);
    }
    // AlfaBeta a(game, heuristic1);
    // a.get_best_move();
    return 0;
}
