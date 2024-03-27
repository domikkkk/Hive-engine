#include <hive/pieces.hpp>
#include <gtest/gtest.h>


TEST(pieces, piece) {
    Piece p(0, 0);
    EXPECT_EQ(p._x, 0);
    EXPECT_EQ(p._y, 0);
};


int main() {
    return RUN_ALL_TESTS();
}