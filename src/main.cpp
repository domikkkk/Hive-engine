#include <Hive>
#include <iostream>
#include <decorators.hpp>


int main(int argc, char **argv) {
    Controller ccc;
    ccc.prepare_pieces();
    hive::Board b;
    b.add_piece({0, Insect::bee, Color::WHITE}, {0, 0});
    b.add_piece({1, Insect::ant, Color::BLACK}, {0, 1});
    b.add_piece({1, Insect::ant, Color::WHITE}, {1, 2});
    auto result = b.is_connected({0, 0});
    std::cout << result << std::endl;
    b.move({1, 2}, {0, 1, 1});
    result = b.is_connected({0, 0}, {0, 1, 1});
    std::cout << result << std::endl;
    std::cout << b[{0, 0}].to_str() << '\n';
    // std::cout << b[{1, 2}].type << std::endl;
    return 0;
}
