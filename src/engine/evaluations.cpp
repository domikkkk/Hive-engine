#include <engine/evaluations.hpp>


float heuristic1(Controller &controller) {
    auto white = controller.count_queen_surrounded(Color::WHITE);
    auto black = controller.count_queen_surrounded(Color::BLACK);
    return white - black;
}