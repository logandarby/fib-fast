#include "util.h"
#include <gtest/gtest.h>

using ::testing::FloatLE;

TEST(Util, shift1) {
    std::array<uint8_t, 2> array{ 0b11111111, 0b10000001 };
    const auto carry = Util::bitShiftLeft(array, 2, 1);
    ASSERT_EQ(array.at(0), 0b11111110);
    ASSERT_EQ(array.at(1), 0b00000011);
    ASSERT_EQ(carry, 0b00000001);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}