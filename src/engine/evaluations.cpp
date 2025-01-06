#include <engine/evaluations.hpp>


float heuristic1(Controller &controller, const Color &maximazing) {
    auto maxx = controller.count_queen_surrounded(maximazing);
    auto minn = controller.count_queen_surrounded(opposite[maximazing]);
    if (maxx == 6 && minn == 6) return 0;
    if (maxx == 6) return -infinity;
    if (minn == 6) return infinity;
    return 1.5 * minn - maxx;
}


float heuristic2(Controller &controller, const Color &maximazing) {
    return 0.0;
}
