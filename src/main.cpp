#include <Hive>
#include <HiveAI>
#include <stdio.h>


int main(int argc, char **argv) {
    auto bee = std::make_unique<hive::Bee>(Coords{1, 1}, WHITE);
    hive::Board board;
    board.add_piece(std::move(bee));
    auto i = board.get_piece_at<hive::Insect>({1, 1});
    if (bee == nullptr) {
        printf("Tak\n");
    }
    // board.remove_piece(i->get_location());
    return 0;
}
