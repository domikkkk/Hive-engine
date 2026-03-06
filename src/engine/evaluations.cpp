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
    float value = black - white;
    for (const auto &piece : controller.pieces_possible_to_move()) {
        const float &w = weights.find(piece[1])->second;
        value += color_from_piece(piece[0]) == Color::WHITE? w: -w;
    }
    return value;
}



int get_index_for_input(const std::pair<std::string, Coords> &piece) {
    int insect_type = 0;
    switch(piece.first[1]) {
        case 'Q': insect_type = 0; break;
        case 'S': insect_type = 1; break;
        case 'B': insect_type = 2; break;
        case 'G': insect_type = 3; break;
        case 'A': insect_type = 4; break;
    }
    const int color_offset = piece.first[0] == 'w' ? 0 : 1;
    const int layer = (color_offset * 5) + insect_type;
    return (layer * hive::X * hive::Y) + ((piece.second.y + hive::Y/2) * hive::X) + piece.second.x + hive::X/2;
}


template <class T>
void set_input(nd2array<T> *input, const std::unordered_map<std::string, Coords> *insects) {
    for (const auto &p : *insects) {
        const int &idx = get_index_for_input(p);
        (*input)(0, idx) = static_cast<T>(1);
    }
}


float learn_nnue(Controller &controller) {
    float value = heuristic3(controller);

    return value;
}
