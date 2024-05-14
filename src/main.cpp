#include <Hive>
#include <HiveAI>
#include <stdio.h>


int main(int argc, char **argv) {
    hive::Bee bee({1, 1}, WHITE);
    hive::Board board;
    board.add_piece(bee);
    hive::Insect *i = &board.get_piece({1, 1});
    printf("%d\n", i->can_move());
    i->set_move(true);
    const void *j = &board.get_piece({1, 1});
    printf("%d\n", static_cast<const hive::Insect*>(j)->can_move());
    i = nullptr;
    const void* x = j;
    printf("%d\n", static_cast<const int>(static_cast<const hive::Insect*>(x)->get_type()));
    return 0;
}
