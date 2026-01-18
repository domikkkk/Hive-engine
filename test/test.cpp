#include <gtest/gtest.h>
#include <Hive.h>
#include <exceptions.hpp>


TEST(Piece, pieces) {
    hive::Piece piece(0, Insect::bee, Color::WHITE);

    ASSERT_EQ(piece.color, Color::WHITE);
    ASSERT_EQ(piece.type, Insect::bee);
    ASSERT_EQ(piece.id, 0);
    ASSERT_FALSE(piece.ismoving);
    ASSERT_EQ(piece, hive::Piece(0, Insect::bee, Color::WHITE));
    ASSERT_EQ(piece.to_str(), "wQ");

    piece.id = 1;
    piece.type = Insect::ant;

    ASSERT_EQ(piece.to_str(), "wA1");
}


TEST(Piece, ability) {
    hive::Ability a = hive::gen_ability(Insect::bee);

    ASSERT_FALSE(a.can_crawl);
    ASSERT_FALSE(a.can_hop);
    ASSERT_EQ(a.how_far, 1);

    a = hive::gen_ability(Insect::ant);

    ASSERT_FALSE(a.can_crawl);
    ASSERT_FALSE(a.can_hop);
    ASSERT_EQ(a.how_far, possible_infinity);

    a = hive::gen_ability(Insect::grasshopper);

    ASSERT_FALSE(a.can_crawl);
    ASSERT_TRUE(a.can_hop);
    ASSERT_EQ(a.how_far, 0);

    a = hive::gen_ability(Insect::beetle);

    ASSERT_TRUE(a.can_crawl);
    ASSERT_FALSE(a.can_hop);
    ASSERT_EQ(a.how_far, 1);
}


TEST(coords, surrounding_locations) {
    Coords c = {0, 0};
    std::vector<Coords> ans;
    ans.emplace_back(Coords{0, 1});
    ans.emplace_back(Coords{1, 1});
    ans.emplace_back(Coords{1, 0});
    ans.emplace_back(Coords{0, -1});
    ans.emplace_back(Coords{-1, -1});
    ans.emplace_back(Coords{-1, 0});

    int i = 0;
    for (auto res: c.get_surrounding_locations()) {
        ASSERT_EQ(res, ans[i++]);
    }
}


TEST(coords, direction) {
    Coords c = {0, 0};
    std::vector<Directions> dir;
    dir.emplace_back(Directions::N);
    dir.emplace_back(Directions::NE);
    dir.emplace_back(Directions::E);
    dir.emplace_back(Directions::S);
    dir.emplace_back(Directions::SW);
    dir.emplace_back(Directions::W);

    int i = 0;
    for (auto neighbor : c.get_surrounding_locations()) {
        ASSERT_EQ(c.get_direction(neighbor), dir[i++]);
    }
}


TEST(Board, pieces) {
    hive::Board b;

    b.add_piece(hive::Piece(0, Insect::bee, Color::WHITE), {0, 0});

    auto type = b[{0, 0}].type;
    ASSERT_EQ(type, Insect::bee);
    ASSERT_EQ(b.count_insects, 1);

    auto move = b.back();
    Coords to = Coords{0, 0};

    ASSERT_TRUE(move.added);
    ASSERT_EQ(move.to, to);
}


TEST(Board, moves) {
    hive::Board b;

    b.add_piece(hive::Piece(1, Insect::spider, Color::WHITE), {0, 0});

    auto &insect = b[{0, 0}];

    ASSERT_EQ(insect.type, Insect::spider);

    b.move({0, 0}, {1, 1});

    ASSERT_EQ(insect.type, Insect::notexists);
    
    auto insect1 = b[{1, 1}];
    auto insect2 = b[{0, 0}];

    ASSERT_EQ(insect1.type, Insect::spider);
    ASSERT_EQ(insect2.type, Insect::notexists);
}


TEST(Board, unmove) {
    hive::Board b;

    b.add_piece(hive::Piece(1, Insect::spider, Color::WHITE), {0, 0});
    b.add_piece(hive::Piece(1, Insect::spider, Color::BLACK), {1, 0});

    ASSERT_EQ(b.count_insects, 2);

    auto move = b.back();
    auto insect = b[move.to];
    ASSERT_EQ(insect.type, Insect::spider);

    b.unmove();
    insect = b[move.to];

    ASSERT_EQ(insect.type, Insect::notexists);
    ASSERT_EQ(b.count_insects, 1);
}


TEST(Board, connected) {
    hive::Board b;

    b.add_piece(hive::Piece(1, Insect::spider, Color::WHITE), {0, 0});
    b.add_piece(hive::Piece(1, Insect::spider, Color::BLACK), {1, 0});
    b.add_piece(hive::Piece(0, Insect::bee, Color::WHITE), {0, 1});
    b.add_piece(hive::Piece(0, Insect::spider, Color::BLACK), {1, -1});

    ASSERT_TRUE(b.is_connected({1, -1}));
    ASSERT_TRUE(b.is_connected({0, 1}));

    ASSERT_FALSE(b.is_connected({0, 0}));
    ASSERT_FALSE(b.is_connected({1, 0}));
}


TEST(Board, connected2) {
    hive::Board b;

    b.add_piece(hive::Piece(1, Insect::spider, Color::WHITE), {0, 0});
    b.add_piece(hive::Piece(1, Insect::spider, Color::BLACK), {1, 0});
    b.add_piece(hive::Piece(0, Insect::bee, Color::WHITE), {0, 1});
    b.add_piece(hive::Piece(0, Insect::bee, Color::BLACK), {2, 1});
    b.add_piece(hive::Piece(1, Insect::ant, Color::WHITE), {-1, -1});
    b.add_piece(hive::Piece(1, Insect::ant, Color::BLACK), {2, 2});
    b.move({-1, -1}, {1, 2});

    ASSERT_TRUE(b.is_connected({0, 0}));
    ASSERT_TRUE(b.is_connected({1, 0}));
    ASSERT_TRUE(b.is_connected({0, 1}));
    ASSERT_TRUE(b.is_connected({1, 2}));
    ASSERT_TRUE(b.is_connected({2, 2}));
    ASSERT_TRUE(b.is_connected({2, 1}));
}


TEST(controller, move) {
    Controller c;

    c.move("wS1", {0, 0});
    c.move("bS1", {1, 0});

    ASSERT_THROW(c.move("wS4", {0, 0}), PieceNotExisting);
    ASSERT_THROW(c.move("wS1", {0, 0}), std::invalid_argument);
    ASSERT_THROW(c.move("bS1", {0, 0}), InvalidMove);
    ASSERT_THROW(c.move("wQ", {1, 1}), InvalidMove);

    c.move("wQ", {0, 1});
    c.move("bQ", {1, -1});

    ASSERT_THROW(c.move("wS1", {1, 2}), NotOneHive);
}


TEST(controller, unmove) {
    Controller c;

    c.move("wS1", {0, 0});
    c.move("bS1", {1, 0});
    c.move("wQ", {0, 1});
    c.move("bQ", {1, -1});

    Coords cc = {1, -1};

    auto piece = c.get_board()[cc];
    auto &pieces = c.get_pieces();
    auto &hands = c.get_hands();

    ASSERT_EQ(piece.type, Insect::bee);
    ASSERT_EQ(pieces.at("bQ"), cc);
    ASSERT_EQ(hands.size(), 18);

    c.undo_move();
    piece = c.get_board()[cc];

    ASSERT_EQ(piece.type, Insect::notexists);
    ASSERT_THROW(pieces.at("bQ"), std::out_of_range);
    ASSERT_EQ(hands.size(), 19);
}


TEST(controller, movable) {
    Controller c;

    c.move("wS1", {0, 0});
    c.move("bS1", {1, 0});
    c.move("wQ", {0, 1});
    c.move("bQ", {1, -1});
    c.move("wA1", {-1, -1});
    c.move("bA1", {2, 1});
    std::vector<Coords> result;
    c.movable_locations("wA1", result, hive::gen_ability(Insect::ant).how_far);

    std::vector<Coords> ans;
    ans.emplace_back(Coords{-1, 0});
    ans.emplace_back(Coords{-1, 1});
    ans.emplace_back(Coords{0, 2});
    ans.emplace_back(Coords{1, 2});
    ans.emplace_back(Coords{1, 1});
    ans.emplace_back(Coords{2, 2});
    ans.emplace_back(Coords{3, 2});
    ans.emplace_back(Coords{3, 1});
    ans.emplace_back(Coords{2, 0});
    ans.emplace_back(Coords{2, -1});
    ans.emplace_back(Coords{1, -2});
    ans.emplace_back(Coords{0, -2});
    ans.emplace_back(Coords{0, -1});

    ASSERT_EQ(ans.size(), result.size());

    for (std::size_t i=0; i<result.size(); ++i) {
        ASSERT_EQ(ans[i], result[i]);
    }
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
