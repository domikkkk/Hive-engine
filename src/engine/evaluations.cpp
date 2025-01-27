#include <engine/evaluations.hpp>
#include <cmath>


float heuristic1(Controller &controller, const Color &maximazing) {
    auto maxx = controller.count_surrounded_fields_of_queen(maximazing);
    auto minn = controller.count_surrounded_fields_of_queen(opposite[maximazing]);
    if (maxx == 6 && minn == 6) return 0;
    if (maxx == 6) return -infinity;
    if (minn == 6) return infinity;
    return minn - maxx;
}


float heuristic2(Controller &controller, const Color &maximazing) {
    auto maxx = controller.count_surrounded_fields_of_queen(maximazing);
    auto minn = controller.count_surrounded_fields_of_queen(opposite[maximazing]);
    if (maxx == 6 && minn == 6) return 0;
    if (maxx == 6) return -infinity;
    if (minn == 6) return infinity;
    if (controller.get_turns() <= 4) return minn - maxx;

    const auto &weights = controller._weights();
    const auto &pieces = controller.get_pieces(); // figury na planszy
    const auto bee_max = colorToString[maximazing] + Insect::bee;
    const auto &bee_max_coords = pieces.find(bee_max)->second;
    const auto bee_min = colorToString[opposite[maximazing]] + Insect::bee;
    const auto &bee_min_coords = pieces.find(bee_min)->second;
    float value = 3.5 * (minn - maxx);
    float d;
    for (const auto &piece: pieces) {
        if (piece.first[1] == Insect::bee) continue;
        if (color_from_piece(piece.first[0]) == maximazing) {
            d = 1 - pow(2.0, bee_min_coords.distance(piece.second)) / hive::X;
            value += (weights.find(piece.first[1])->second * d);
        } else {
            d = 1 - pow(2.0, bee_max_coords.distance(piece.second)) / hive::X;
            value -= (weights.find(piece.first[1])->second * d);
        }
    }
    return value;
}


float heuristic3(Controller &controller, const Color &maximazing) {
    auto maxx = controller.count_surrounded_fields_of_queen(maximazing);
    auto minn = controller.count_surrounded_fields_of_queen(opposite[maximazing]);
    if (maxx == 6 && minn == 6) return 0;
    if (maxx == 6) return -infinity;
    if (minn == 6) return infinity;
    if (controller.get_turns() <= 4) return minn - maxx;

    const auto &weights = controller._weights();
    float value = 3.5 * minn - maxx;
    for (const auto &piece : controller.pieces_possible_to_move()) {
        const float &w = weights.find(piece[1])->second;
        value += color_from_piece(piece[0]) == maximazing? 0.2*w: -w;
    }
    return value;
}
