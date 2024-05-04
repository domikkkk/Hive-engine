#include <gtest/gtest.h>
#include <Hive>


TEST(pieces, piece) {
    hive::Piece p({0, 0}, WHITE);
    EXPECT_EQ(p.get_location().x, 0);
    EXPECT_EQ(p.get_location().y, 0);
};


TEST(pieces, Bee) {
    hive::Bee b({1, 0}, WHITE);
    EXPECT_EQ(b.get_location().x, 1);
    EXPECT_EQ(b.get_location().y, 0);
};


TEST(pieces, Ant) {
    hive::Ant a({1, 1}, WHITE);
    EXPECT_EQ(a.get_location().x, 1);
    EXPECT_EQ(a.get_location().y, 1);
};


TEST(pieces, Beetle) {
    hive::Beetle b({3, 0}, WHITE);
    EXPECT_EQ(b.get_location().x, 3);
    EXPECT_EQ(b.get_location().y, 0);
};


TEST(pieces, Grasshopper) {
    hive::Grasshopper g({0, -3}, WHITE);
    EXPECT_EQ(g.get_location().x, 0);
    EXPECT_EQ(g.get_location().y, -3);
};


TEST(pieces, Spider) {
    hive::Spider s({2, 4}, WHITE);
    EXPECT_EQ(s.get_location().x, 2);
    EXPECT_EQ(s.get_location().y, 4);
};


TEST(Board, empty) {
    hive::Board board;
    EXPECT_TRUE(board.is_empty());
};


TEST(Board, not_empty) {
    hive::Board board;
    board.add_piece(new hive::Bee({0, 0}, WHITE));
    EXPECT_FALSE(board.is_empty());
};


TEST(Board, locations) {
    std::vector<Coords> expected{{1, 3}, {2, 2}, {2, 0}, {1, -1}, {0, 0}, {0, 2}};
    std::vector<Coords> result = get_surrounding_locations({1, 1});
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(expected[i], result[i]);
    }
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
