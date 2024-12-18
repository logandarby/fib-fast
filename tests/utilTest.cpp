#include "util.h"
#include <gtest/gtest.h>

using ::testing::FloatLE;

TEST(BitShiftLeft, shiftLow) {
    std::array<uint8_t, 2> array{ 0b11111111, 0b10000001 };
    const auto carry = Util::bitShiftLeft(array, 2, 1);
    ASSERT_EQ(array.at(0), 0b11111110);
    ASSERT_EQ(array.at(1), 0b00000011);
    ASSERT_EQ(carry, 0b00000001);
}

TEST(BitShiftLeft, shiftHigh) {
    std::array<uint8_t, 4> array{ 0b11111111, 0b11111111, 0b11111111,
                                  0b11111111 };
    const auto carry = Util::bitShiftLeft(array, 4, 2);
    ASSERT_EQ(array.at(0), 0b11111100);
    ASSERT_EQ(array.at(1), 0b11111111);
    ASSERT_EQ(array.at(2), 0b11111111);
    ASSERT_EQ(array.at(3), 0b11111111);
    ASSERT_EQ(carry, 0b00000011);
}

TEST(BitShiftLeft, shiftOne) {
    std::array<uint8_t, 2> array{ 0b11111111 };
    const auto carry = Util::bitShiftLeft(array, 1, 4);
    ASSERT_EQ(array.at(0), 0b11110000);
    ASSERT_EQ(carry, 0b00001111);
}

TEST(BitShiftRight, shiftHigh) {
    std::array<uint8_t, 4> array{ 0b11111111, 0b11111111, 0b11111111,
                                  0b11111111 };
    Util::bitShiftRight(array, 4, 2);
    ASSERT_EQ(array.at(0), 0b11111111);
    ASSERT_EQ(array.at(1), 0b11111111);
    ASSERT_EQ(array.at(2), 0b11111111);
    ASSERT_EQ(array.at(3), 0b00111111);
}

TEST(BitShiftRight, shiftLow) {
    std::array<uint8_t, 2> array{ 0b11111111, 0b10000001 };
    Util::bitShiftRight(array, 2, 1);
    ASSERT_EQ(array.at(0), 0b11111111);
    ASSERT_EQ(array.at(1), 0b01000000);
}

TEST(BitShiftRight, shiftOne) {
    std::array<uint8_t, 2> array{ 0b11111111 };
    Util::bitShiftRight(array, 1, 1);
    ASSERT_EQ(array.at(0), 0b01111111);
}

// TEST(Multiply, multoverflow) {
//     std::array<uint8_t, 2> a{ 255, 0 };
//     std::array<uint8_t, 2> b{ 255, 0 };
//     std::array<uint8_t, 4> out{ 0, 0, 0, 0 };
//     Util::multiplyAccumulate<uint8_t, uint16_t>(out, a, b, 4);
//     ASSERT_EQ(out[0], 0b00000001);
//     ASSERT_EQ(out[1], 0b11111110);
//     ASSERT_EQ(out[2], 0);
//     ASSERT_EQ(out[3], 0);
// }

// TEST(Multiply, multhigh) {
//     std::array<uint8_t, 2> a{ 1, 1 };
//     std::array<uint8_t, 2> b{ 1, 1 };
//     std::array<uint8_t, 4> out{ 0, 0, 0, 0 };
//     Util::multiplyAccumulate<uint8_t, uint16_t>(out, a, b, 4);
//     ASSERT_EQ(out[0], 1);
//     ASSERT_EQ(out[1], 0b10);
//     ASSERT_EQ(out[2], 1);
//     ASSERT_EQ(out[3], 0);
// }

// TEST(Multiply, zero) {
//     std::array<uint8_t, 2> a{ 0, 0 };
//     std::array<uint8_t, 2> b{ 0, 0 };
//     std::array<uint8_t, 4> out{ 0, 0, 0, 0 };
//     Util::multiplyAccumulate<uint8_t, uint16_t>(out, a, b, 4);
//     ASSERT_EQ(out[0], 0);
//     ASSERT_EQ(out[1], 0);
//     ASSERT_EQ(out[2], 0);
//     ASSERT_EQ(out[3], 0);
// }

// TEST(Multiply, highestMult) {
//     std::array<uint8_t, 2> a{ 255, 255 };
//     std::array<uint8_t, 2> b{ 255, 255 };
//     std::array<uint8_t, 4> out{ 0, 0, 0, 0 };
//     Util::multiplyAccumulate<uint8_t, uint16_t>(out, a, b, 4);
//     ASSERT_EQ(out[0], 1);
//     ASSERT_EQ(out[1], 0);
//     ASSERT_EQ(out[2], 0b11111110);
//     ASSERT_EQ(out[3], 0b11111111);
// }

TEST(Add, accumulateOverflow) {
    std::array<uint8_t, 3> a{ 255, 255, 0 };
    std::array<uint8_t, 3> b{ 1, 0, 0 };
    Util::accumulate(a, b, 2);
    ASSERT_EQ(a[0], 0);
    ASSERT_EQ(a[1], 0);
    ASSERT_EQ(a[2], 1);
}

TEST(Add, addZero) {
    std::array<uint8_t, 4> a{ 0, 0, 0, 0 };
    std::array<uint8_t, 4> b{ 0, 0, 0, 0 };
    Util::accumulate(a, b, 3);
    ASSERT_EQ(a[0], 0);
    ASSERT_EQ(a[1], 0);
    ASSERT_EQ(a[2], 0);
}

TEST(Subtract, subtractOverflow) {
    std::array<uint8_t, 3> a{ 0, 0, 1 };
    std::array<uint8_t, 3> b{ 1, 0, 0 };
    const bool underflow = Util::subtractAccumulate(a, b, 3);
    ASSERT_EQ(a[0], 255);
    ASSERT_EQ(a[1], 255);
    ASSERT_EQ(a[2], 0);
    ASSERT_EQ(underflow, 0);
}

TEST(Subtract, subtractUnderflow) {
    std::array<uint8_t, 3> a{ 1, 0, 0 };
    std::array<uint8_t, 3> b{ 1, 1, 0 };
    const bool underflow = Util::subtractAccumulate(a, b, 3);
    ASSERT_EQ(underflow, 1);
}

TEST(Subtract, subZero) {
    std::array<uint8_t, 3> a{ 1, 1, 0 };
    std::array<uint8_t, 3> b{ 0, 0, 0 };
    const bool underflow = Util::subtractAccumulate(a, b, 3);
    ASSERT_EQ(a[0], 1);
    ASSERT_EQ(a[1], 1);
    ASSERT_EQ(a[2], 0);
    ASSERT_EQ(underflow, 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}