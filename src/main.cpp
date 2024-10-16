#include <Hive>
#include <iostream>


int main(int argc, char **argv) {
    hive::Board b;
    b.add_piece(Insect::white_bee, {1, 2});
    b.add_piece(Insect::white_ant, {0, 1});
    b.add_piece(Insect::white_ant, {0, 3});
    std::cout << b.is_connected() << std::endl;
    b.move({0, 3}, {0, 1, 1});
    std::cout << b.is_connected() << std::endl;
    return 0;
}
