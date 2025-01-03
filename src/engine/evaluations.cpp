#include <engine/evaluations.hpp>


float heuristic1(Controller &controller, const Color &maximazing) {
    auto maxx = controller.count_queen_surrounded(maximazing);
    auto minn = controller.count_queen_surrounded(opposite[maximazing]);
    if (maxx == 6) return -possible_infinity;
    if (minn == 6) return possible_infinity;
    return 2* minn - maxx;
}