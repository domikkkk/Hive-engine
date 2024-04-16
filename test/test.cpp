#include <gtest/gtest.h>
#include <Hive>


TEST(pieces, piece) {
    Piece p(0, 0);
    EXPECT_EQ(p.get_x(), 0);
    EXPECT_EQ(p.get_y(), 0);
};


int main() {
    return RUN_ALL_TESTS();
}
