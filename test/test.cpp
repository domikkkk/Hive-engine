#include <hive/pieces.hpp>
#include <gtest/gtest.h>


TEST(pieces, piece) {
    Piece p(0, 0);
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
};


int main() {
    return RUN_ALL_TESTS();
}