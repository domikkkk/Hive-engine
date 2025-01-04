#include <engine/evaluations.hpp>


float heuristic1(Controller &controller, const Color &maximazing) {
    auto maxx = controller.count_queen_surrounded(maximazing);
    auto minn = controller.count_queen_surrounded(opposite[maximazing]);
    if (maxx == 6) return -infinity/2;
    if (minn == 6) return infinity/2;
    return 1.5 * minn - maxx;
}


float heuristic2(Controller &controller, const Color &maximazing) {
    return 0.0;
}
