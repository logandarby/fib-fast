#include "util.h"
#include <gtest/gtest.h>

using ::testing::FloatLE;

TEST(BitShift, shiftLow) {
    std::array<uint8_t, 2> array{ 0b11111111, 0b10000001 };
    const auto carry = Util::bitShiftLeft(array, 2, 1);
    ASSERT_EQ(array.at(0), 0b11111110);
    ASSERT_EQ(array.at(1), 0b00000011);
    ASSERT_EQ(carry, 0b00000001);
}

TEST(BitShift, shiftHigh) {
    std::array<uint8_t, 4> array{ 0b11111111, 0b11111111, 0b11111111,
                                  0b11111111 };
    const auto carry = Util::bitShiftLeft(array, 4, 2);
    ASSERT_EQ(array.at(0), 0b11111100);
    ASSERT_EQ(array.at(1), 0b11111111);
    ASSERT_EQ(array.at(1), 0b11111111);
    ASSERT_EQ(array.at(1), 0b11111111);
    ASSERT_EQ(carry, 0b00000011);
}

TEST(Multiply, multoverflow) {
    uint8_t a[2] = { 255, 0 };
    uint8_t b[2] = { 255, 0 };
    uint8_t out[4] = { 0, 0, 0, 0 };
    Util::multiplyAccumulate<factor_t, product_t>(out, a, b, 2);
    ASSERT_EQ(out[0], 0b00000001);
    ASSERT_EQ(out[1], 0b11111110);
    ASSERT_EQ(out[2], 0);
    ASSERT_EQ(out[3], 0);
}

TEST(Multiply, multhigh) {
    uint8_t a[2] = { 1, 1 };
    uint8_t b[2] = { 1, 1 };
    uint8_t out[4] = { 0, 0, 0, 0 };
    Util::multiplyAccumulate<factor_t, product_t>(out, a, b, 2);
    ASSERT_EQ(out[0], 1);
    ASSERT_EQ(out[1], 0b10);
    ASSERT_EQ(out[2], 1);
    ASSERT_EQ(out[3], 0);
}

TEST(Multiply, zero) {
    uint8_t a[2] = { 0, 0 };
    uint8_t b[2] = { 0, 0 };
    uint8_t out[4] = { 0, 0, 0, 0 };
    Util::multiplyAccumulate<factor_t, product_t>(out, a, b, 2);
    ASSERT_EQ(out[0], 0);
    ASSERT_EQ(out[1], 0);
    ASSERT_EQ(out[2], 0);
    ASSERT_EQ(out[3], 0);
}

TEST(Multiply, highestMult) {
    uint8_t a[2] = { 255, 255 };
    uint8_t b[2] = { 255, 255 };
    uint8_t out[4] = { 0, 0, 0, 0 };
    Util::multiplyAccumulate<factor_t, product_t>(out, a, b, 2);
    ASSERT_EQ(out[0], 1);
    ASSERT_EQ(out[1], 0);
    ASSERT_EQ(out[2], 0b11111110);
    ASSERT_EQ(out[3], 0b11111111);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}