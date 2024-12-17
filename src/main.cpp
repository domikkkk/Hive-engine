#include <Hive>
#include <iostream>
#include <decorators.hpp>


int main(int argc, char **argv) {
    Game game;
    Command c;
    while(true) {
        std::cin >> c;
        c.execute(game);
    }
    return 0;
}
