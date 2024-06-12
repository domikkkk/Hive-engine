#include <gtest/gtest.h>
#include <Hive>


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
    board.add_piece(std::make_unique<hive::Bee>(Coords{0, 0}, WHITE));
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
    auto bee = std::make_unique<hive::Bee>(Coords{0, 0}, WHITE);
    auto bee_raw = bee.get();
    auto ant = std::make_unique<hive::Ant>(Coords{1, 1}, BLACK);
    board.add_piece(std::move(bee));
    board.add_piece(std::move(ant));

    auto retreviedBee = board.get_piece_at<hive::Bee>({0, 0});
    auto retreviedAnt = board.get_piece_at<hive::Ant>({0, 1});
    ASSERT_EQ(retreviedBee, bee_raw);
    ASSERT_EQ(*retreviedBee, *bee_raw);
    ASSERT_EQ(retreviedAnt, nullptr);// still shoudn't be here
}


TEST(Board, operator) {
    hive::Board board;
    board.add_piece(std::make_unique<hive::Spider>(Coords{0, 0}, WHITE));
    board.add_piece(std::make_unique<hive::Bee>(Coords{0, 2}, BLACK));
    auto i = board[Coords{0, 0}];
    ASSERT_NE(i, nullptr);
    i = board[Coords{0, 3}];
    ASSERT_EQ(i, nullptr);
    board.move(Coords{0, 2}, Coords{0, 3});
    i = board[Coords{0, 3}];
    ASSERT_NE(i, nullptr);
}


TEST(Board, move) {
    hive::Board board;
    auto bee = std::make_unique<hive::Bee>(Coords{1, 1}, WHITE);
    Coords c = {1, 1};
    board.add_piece(std::move(bee));
    auto j = board.get_piece_at<hive::Insect>({1, 1});
    ASSERT_EQ(j->get_location(), c);
    // move piece to another place
    board.move({1, 1}, {2, 2});

    c = {2, 2};
    ASSERT_EQ(j->get_location(), c);
    auto i = board.get_piece_at<hive::Ant>(c);
    if (i != nullptr) {
        ASSERT_EQ(i->get_type(), InsectType::BEE);
    }
}


TEST(Board, unmove) {
    hive::Board board;
    board.add_piece(std::make_unique<hive::Spider>(Coords{-1, -1}, WHITE));
    auto i = board.get_piece_at<hive::Insect>(Coords{-1, -1});
    Coords c1 = {-2, 2}, c2 = {-1, -1};
    board.move(c2, c1);
    ASSERT_EQ(i->get_type(), InsectType::SPIDER);
    ASSERT_EQ(i->get_location(), c1);
    Move past_move = board.unmove();
    ASSERT_FALSE(past_move.added);
    ASSERT_EQ(past_move.to, c1); ASSERT_EQ(past_move.from, c2);
    ASSERT_FALSE(board.is_empty());
    past_move = board.unmove();
    ASSERT_TRUE(past_move.added);
    ASSERT_EQ(past_move.to, c2);
    ASSERT_TRUE(board.is_empty());
}


TEST(Board, validConnection) {
    hive::Board board;
    board.add_piece(std::make_unique<hive::Spider>(Coords{0, 0}, WHITE));
    board.add_piece(std::make_unique<hive::Bee>(Coords{0, 2}, BLACK));
    board.add_piece(std::make_unique<hive::Ant>(Coords{-1, -1}, WHITE));
    board.add_piece(std::make_unique<hive::Grasshopper>(Coords{1, 3}, BLACK));
    board.add_piece(std::make_unique<hive::Bee>(Coords{1, -1}, WHITE));
    ASSERT_TRUE(board.is_connected());
    board.add_piece(std::make_unique<hive::Grasshopper>(Coords{-2, 4}, BLACK));
    ASSERT_FALSE(board.is_connected());
    board.move({-2, 4}, {-1, 3});
    ASSERT_TRUE(board.is_connected());
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
