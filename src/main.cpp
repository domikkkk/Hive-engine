#include <Hive>
#include <HiveAI>
#include <stdio.h>


int main(int argc, char **argv) {
    auto bee = std::make_shared<hive::Bee>(Coords{1, 1}, WHITE);
    hive::Board board;
    board.add_piece(bee);
    auto i = board.get_piece_at<hive::Insect>({1, 1});
    board.remove_piece(bee);
    return 0;
}
