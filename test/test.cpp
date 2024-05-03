#include <gtest/gtest.h>
#include <Hive>


TEST(pieces, piece) {
    hive::Piece p({0, 0}, WHITE);
    EXPECT_EQ(p.get_x(), 0);
    EXPECT_EQ(p.get_y(), 0);
};


TEST(pieces, Bee) {
    hive::Bee b({1, 0}, WHITE);
    EXPECT_EQ(b.get_x(), 1);
    EXPECT_EQ(b.get_y(), 0);
};


TEST(pieces, Ant) {
    hive::Ant a({1, 1}, WHITE);
    EXPECT_EQ(a.get_x(), 1);
    EXPECT_EQ(a.get_y(), 1);
};


TEST(pieces, Beetle) {
    hive::Beetle b({3, 0}, WHITE);
    EXPECT_EQ(b.get_x(), 3);
    EXPECT_EQ(b.get_y(), 0);
};


TEST(pieces, Grasshopper) {
    hive::Grasshopper g({0, -3}, WHITE);
    EXPECT_EQ(g.get_x(), 0);
    EXPECT_EQ(g.get_y(), -3);
};


TEST(pieces, Spider) {
    hive::Spider s({2, 4}, WHITE);
    EXPECT_EQ(s.get_x(), 2);
    EXPECT_EQ(s.get_y(), 4);
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


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
