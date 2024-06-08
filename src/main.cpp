#include <Hive>
#include <HiveAI>
#include <iostream>


int main(int argc, char **argv) {
    auto bee = std::make_unique<hive::Bee>(Coords{1, 1}, WHITE);
    hive::Board board;
    board.add_piece(std::move(bee));
    auto i = board.get_piece_at<hive::Insect>({1, 1});
    board.move({1, 1}, {2, 2});
    std::cout << i->get_location().x << '\n';
    board.move({2, 2}, {3, 3});
    std::cout << i->get_location().x << '\n';
    board.unmove();
    std::cout << i->get_location().x << '\n';
    board.remove_piece(i->get_location());
    i = board.get_piece_at<hive::Insect>({2, 2});
    if (!i) {
        std::cout << "removed\n";
    }
    return 0;
}
