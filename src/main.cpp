#include <Hive>
#include <HiveAI>
#include <stdio.h>


int main(int argc, char **argv) {
    hive::Bee *bee = new hive::Bee({1, 1}, WHITE);
    hive::Board board;
    board.add_piece(bee);
    Coords c = bee->get_location();
    hive::Insect *i = board.get_piece_at({1, 1});
    printf("%d %d %d\n", c.x, c.y, i->is_exist());
    board.move({1, 1}, {2, 2});
    c = bee->get_location();
    i = board.get_piece_at({1, 1});
    if (i == nullptr) printf("XD\n");
    printf("%d %d\n", c.x, c.y);
    return 0;
}
