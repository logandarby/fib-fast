#include "fib.h"
#include "sciNumber.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(FibLienar, Test2) {
    ASSERT_EQ(3, 3);
}

TEST(FibLinear, Test3) {
    const unsigned int fib = fibonacci(4).at(0);
    SciNumber s{ 2, 3, 4 };
    ASSERT_EQ(fib, 3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}