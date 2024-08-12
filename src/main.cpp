#include <Hive>
#include <iostream>


int main(int argc, char **argv) {
    hive::Board b;
    b.add_piece(Insect::bee, {1, 2});
    b.add_piece(Insect::ant, {0, 1});
    b.add_piece(Insect::ant, {1, 3});
    std::cout << b(0, 1) << std::endl;
    std::cout << b.first_location.x << ' ' << b.first_location.y << std::endl;
    std::cout << b.is_connected() << std::endl;
    return 0;
}
