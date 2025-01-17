#include <engine/evaluations.hpp>


float heuristic1(Controller &controller, const Color &maximazing) {
    auto maxx = controller.count_queen_surrounded(maximazing);
    auto minn = controller.count_queen_surrounded(opposite[maximazing]);
    if (maxx == 6 && minn == 6) return 0;
    if (maxx == 6) return -infinity;
    if (minn == 6) return infinity;
    return minn - maxx;
}


float heuristic2(Controller &controller, const Color &maximazing) {
    auto maxx = controller.count_queen_surrounded(maximazing);
    auto minn = controller.count_queen_surrounded(opposite[maximazing]);
    if (maxx == 6 && minn == 6) return 0;
    if (maxx == 6) return -infinity;
    if (minn == 6) return infinity;
    if (controller.get_turns() <= 4) return minn - maxx;

    const auto &weights = controller._weights();
    const auto &pieces = controller.get_pieces(); // figury na planszy
    const auto &bee_max = pieces.find(colorToString[maximazing] + Insect::bee)->second;
    const auto &bee_min = pieces.find(colorToString[opposite[maximazing]] + Insect::bee)->second;
    float value = 3 * (minn - maxx);
    for (const auto &piece: pieces) {
        if (piece.first[1] == Insect::bee) continue;
        if (color_from_piece(piece.first[0]) == maximazing) {
            value += (weights.find(piece.first[1])->second * (1 - bee_min.distance(piece.second) / hive::X));
        } else {
            value -= (weights.find(piece.first[1])->second * (1 - bee_max.distance(piece.second) / hive::X));
        }
    }
    return value;
}
