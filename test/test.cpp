#include <gtest/gtest.h>
#include <Hive>

#define DEBUG


TEST(insects, piece) {
    hive::Insect p({0, 0});
    EXPECT_EQ(p.get_location().x, 0);
    EXPECT_EQ(p.get_location().y, 0);
};


TEST(insects, Bee) {
    hive::Bee b({1, 0}, WHITE);
    EXPECT_EQ(b.get_location().x, 1);
    EXPECT_EQ(b.get_location().y, 0);
};


TEST(insects, Ant) {
    hive::Ant a({1, 1}, WHITE);
    EXPECT_EQ(a.get_location().x, 1);
    EXPECT_EQ(a.get_location().y, 1);
};


TEST(insects, Beetle) {
    hive::Beetle b({3, 0}, WHITE);
    EXPECT_EQ(b.get_location().x, 3);
    EXPECT_EQ(b.get_location().y, 0);
};


TEST(insects, Grasshopper) {
    hive::Grasshopper g({0, -3}, WHITE);
    EXPECT_EQ(g.get_location().x, 0);
    EXPECT_EQ(g.get_location().y, -3);
};


TEST(insects, Spider) {
    hive::Spider s({2, 4}, WHITE);
    EXPECT_EQ(s.get_location().x, 2);
    EXPECT_EQ(s.get_location().y, 4);
};


TEST(insects, operatorEqual) {
    hive::Ant ant({0, 0}, WHITE);
    hive::Ant ant1({0, 0}, BLACK);
    EXPECT_NE(ant, ant1);
    ant = hive::Ant({0, 1}, BLACK);
    EXPECT_NE(ant, ant1);
    ant = hive::Ant({0, 0}, WHITE);
    EXPECT_NE(ant, ant1);
    ant = hive::Ant({0, 0}, BLACK);
    EXPECT_EQ(ant, ant1);
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
    hive::Insect p({1, 1});
    std::vector<Coords> result = p.get_surrounding_locations();
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(expected[i], result[i]);
    }
}


TEST(Board, insects) {
    hive::Board board;
    hive::Bee *bee = new hive::Bee({0, 0}, WHITE);
    hive::Ant *ant = new hive::Ant({1, 1}, BLACK);
    board.add_piece(bee);
    board.add_piece(ant);
    auto *retreviedBee = board.get_piece_at<hive::Bee>({0, 0});
    auto *retreviedAnt = board.get_piece_at<hive::Ant>({0, 1});
    ASSERT_EQ(*retreviedBee, *bee);
    ASSERT_EQ(retreviedAnt, nullptr);
    ASSERT_EQ(retreviedBee, bee);
    retreviedAnt = board.get_piece_at<hive::Ant>({0, 1});
    ASSERT_EQ(retreviedAnt, nullptr);// still shoudn't be here
    retreviedAnt = nullptr;
    retreviedBee = nullptr;
}


TEST(Board, move) {
    hive::Board board;
    hive::Bee *bee = new hive::Bee({1, 1}, WHITE);
    Coords c = {1, 1};
    board.add_piece(bee);
    ASSERT_EQ(bee->get_location(), c);
    // move piece to another place
    board.move({1, 1}, {2, 2});

    c = {2, 2};
    ASSERT_EQ(bee->get_location(), c);
    hive::Ant *i = board.get_piece_at<hive::Ant>(c);
    ASSERT_EQ(i->get_type(), InsectType::BEE);
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
