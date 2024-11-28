#include <Hive>
#include <iostream>
#include <decorators.hpp>


int main(int argc, char **argv) {
    hive::Board b;
    b.add_piece({1, Insect::bee}, {0, 0});
    b.add_piece({1, Insect::ant}, {0, 1});
    b.add_piece({2, Insect::ant}, {1, 2});
    auto result = time_function(&hive::Board::is_connected, &b);
    std::cout << result << std::endl;
    b.move({1, 2}, {0, 1, 1});
    result = time_function(&hive::Board::is_connected, &b);
    std::cout << result << std::endl;
    // std::cout << b[{1, 2}].type << std::endl;
    return 0;
}
