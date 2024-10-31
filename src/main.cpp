#include <Hive>
#include <iostream>
#include <decorators.hpp>

int nwd(const int &a, const int &b) {
    return b? nwd(b, a%b) : a;
}


int main(int argc, char **argv) {
    hive::Board b;
    b.add_piece({1, Insect::bee}, {1, 2});
    b.add_piece({1, Insect::ant}, {0, 1});
    b.add_piece({2, Insect::ant}, {0, 3});
    auto result = time_function(&hive::Board::is_connected, &b);
    std::cout << result << std::endl;
    b.move({0, 3}, {0, 1, 1});
    result = time_function(&hive::Board::is_connected, &b);
    std::cout << result << std::endl;
    auto res = time_function(&hive::gen_possibility, 'q');
    std::cout << res.can_hop << std::endl;
    return 0;
}
