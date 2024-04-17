#include <gtest/gtest.h>
#include <Hive>
#include <string>


TEST(pieces, piece) {
    hive::Piece p(0, 0);
    EXPECT_EQ(p.get_x(), 0);
    EXPECT_EQ(p.get_y(), 0);
};


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
