#include <engine/evaluations.hpp>
#include <cmath>


float heuristic1(Controller &controller) {
    auto white = controller.count_surrounded_fields_of_queen(Color::WHITE);
    auto black = controller.count_surrounded_fields_of_queen(Color::BLACK);
    if (white == 6 && black == 6) return 0;
    if (white == 6) return -infinity;
    if (black == 6) return infinity;
    return black - white;
}


float heuristic2(Controller &controller) {
    auto white = controller.count_surrounded_fields_of_queen(Color::WHITE);
    auto black = controller.count_surrounded_fields_of_queen(Color::BLACK);
    if (white == 6 && black == 6) return 0;
    if (white == 6) return -infinity;
    if (black == 6) return infinity;
    if (controller.get_turns() <= 4) return black - white;

    const auto &weights = controller._weights();
    const auto &pieces = controller.get_pieces(); // figury na planszy
    const auto bee_white = colorToString[Color::WHITE] + Insect::bee;
    const auto &bee_white_coords = pieces.find(bee_white)->second;
    const auto bee_black = colorToString[Color::BLACK] + Insect::bee;
    const auto &bee_black_coords = pieces.find(bee_black)->second;
    float value = 3.5 * (black - white);
    float d;
    for (const auto &piece: pieces) {
        if (piece.first[1] == Insect::bee) continue;
        if (color_from_piece(piece.first[0]) == Color::WHITE) {
            d = 1 - pow(2.0, bee_black_coords.distance(piece.second)) / hive::X;
            value += (weights.find(piece.first[1])->second * d);
        } else {
            d = 1 - pow(2.0, bee_white_coords.distance(piece.second)) / hive::X;
            value -= (weights.find(piece.first[1])->second * d);
        }
    }
    return value;
}


float heuristic3(Controller &controller) {
    auto white = controller.count_surrounded_fields_of_queen(Color::WHITE);
    auto black = controller.count_surrounded_fields_of_queen(Color::BLACK);
    if (white == 6 && black == 6) return 0;
    if (white == 6) return -infinity;
    if (black == 6) return infinity;
    if (controller.get_turns() <= 4) return black - white;

    const auto &weights = controller._weights();
    float value = 3.5 * black - white;
    for (const auto &piece : controller.pieces_possible_to_move()) {
        const float &w = weights.find(piece[1])->second;
        value += color_from_piece(piece[0]) == Color::WHITE? 0.2*w: -w;
    }
    return value;
}
