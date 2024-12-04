#include <Hive>
#include <iostream>
#include <decorators.hpp>


int main(int argc, char **argv) {
    Controller controller;
    controller.prepare_pieces();
    controller.move("wS1", {0, 0});
    controller.move("bS1", {0, 1});
    printf("1:\n");
    std::vector<Coords> places = controller.legal_piece_placement();
    for (const auto place: places) {
        printf("%d %d\n", place.x, place.y);
    }

    printf("\n2:\n");
    controller.move("wQ", {-1, -1});
    places = controller.legal_piece_placement();
    for (const auto place: places) {
        printf("%d %d\n", place.x, place.y);
    }
    printf("\n3:\n");
    controller.move("bQ", {0, 2});
    places = controller.legal_piece_placement();
    for (const auto place: places) {
        printf("%d %d\n", place.x, place.y);
    }
    return 0;
}
