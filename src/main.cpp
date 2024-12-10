#include <Hive>
#include <iostream>
#include <decorators.hpp>


int main(int argc, char **argv) {
    // Controller controller;
    // std::vector<Coords> places = controller.legal_piece_placement();
    // for (const auto place: places) {
    //     printf("%d %d\n", place.x, place.y);
    // }
    // controller.move("wS1", {0, 0});
    // places = controller.legal_piece_placement();
    // for (const auto place: places) {
    //     printf("%d %d\n", place.x, place.y);
    // }
    // controller.move("bS1", {0, 1});
    // printf("1:\n");
    // places = controller.legal_piece_placement();
    // for (const auto place: places) {
    //     printf("%d %d\n", place.x, place.y);
    // }

    // printf("\n2:\n");
    // controller.move("wQ", {-1, -1});
    // places = controller.legal_piece_placement();
    // for (const auto place: places) {
    //     printf("%d %d\n", place.x, place.y);
    // }
    // printf("\n3:\n");
    // controller.move("bQ", {0, 2});
    // places = controller.legal_piece_placement();
    // for (const auto place: places) {
    //     printf("%d %d\n", place.x, place.y);
    // }
    Game game;
    Command c;
    while(true) {
        std::cin >> c;
        c.execute(game);
    }
    return 0;
}
