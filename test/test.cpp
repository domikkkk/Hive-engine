#include <gtest/gtest.h>
#include <Hive>

#define DEBUG


TEST(insects, piece) {
    hive::Insect *p = new hive::Insect({0, 0});
    EXPECT_EQ(p->get_location().x, 0);
    EXPECT_EQ(p->get_location().y, 0);
    delete p;
};


TEST(insects, Bee) {
    hive::Bee *b = new hive::Bee({1, 0}, WHITE);
    EXPECT_EQ(b->get_location().x, 1);
    EXPECT_EQ(b->get_location().y, 0);
    delete b;
};


TEST(insects, Ant) {
    hive::Ant *a = new hive::Ant({1, 1}, WHITE);
    EXPECT_EQ(a->get_location().x, 1);
    EXPECT_EQ(a->get_location().y, 1);
    delete a;
};


TEST(insects, Beetle) {
    hive::Beetle *b = new hive::Beetle({3, 0}, WHITE);
    EXPECT_EQ(b->get_location().x, 3);
    EXPECT_EQ(b->get_location().y, 0);
    delete b;
};


TEST(insects, Grasshopper) {
    hive::Grasshopper *g = new hive::Grasshopper({0, -3}, WHITE);
    EXPECT_EQ(g->get_location().x, 0);
    EXPECT_EQ(g->get_location().y, -3);
    delete g;
};


TEST(insects, Spider) {
    hive::Spider *s = new hive::Spider({2, 4}, WHITE);
    EXPECT_EQ(s->get_location().x, 2);
    EXPECT_EQ(s->get_location().y, 4);
    delete s;
};


TEST(insects, operatorEqual) {
    hive::Ant *ant = new hive::Ant({0, 0}, WHITE);
    hive::Ant *ant1 = new hive::Ant({0, 0}, BLACK);
    EXPECT_NE(*ant, *ant1); delete ant;
    ant = new hive::Ant({0, 1}, BLACK);
    EXPECT_NE(*ant, *ant1); delete ant;
    ant = new hive::Ant({0, 0}, WHITE);
    EXPECT_NE(*ant, *ant1); delete ant;
    ant = new hive::Ant({0, 0}, BLACK);
    EXPECT_EQ(*ant, *ant1);
    delete ant;
    delete ant1;
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
    hive::Insect *p = new hive::Insect({1, 1});
    std::vector<Coords> result = p->get_surrounding_locations();
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(expected[i], result[i]);
    }
    delete p;
}


// TEST(Board, insects) {
//     hive::Board board;
//     hive::Bee *bee = new hive::Bee({0, 0}, WHITE);
//     hive::Ant *ant = new hive::Ant({1, 1}, BLACK);
//     board.add_piece(bee);
//     board.add_piece(ant);
//     hive::Bee *retreviedBee = static_cast<hive::Bee*>(board.get_piece_at({0, 0}));
//     hive::Ant *retreviedAnt = static_cast<hive::Ant*>(board.get_piece_at({0, 1}));
//     ASSERT_EQ(*retreviedBee, *bee);
//     ASSERT_NE(*retreviedAnt, *ant);
//     retreviedAnt = static_cast<hive::Ant*>(board.get_piece_at({0, 1}));
//     ASSERT_NE(*retreviedAnt, *ant);  // still shoudn't be here
// }


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
    hive::Insect *i = board.get_piece_at(c);
    ASSERT_EQ(i->get_type(), InsectType::BEE);
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
