#pragma once

#include "core.h"
#include "util.h"

#ifdef _DEBUG
typedef uint8_t digit_t;
#else
typedef uint8_t digit_t;
#endif

typedef uint8_t factor_t;
typedef uint16_t product_t;  // must be at least 2 * factor_t

static_assert(
    2 * sizeof(factor_t) <= sizeof(product_t),
    "2 * factor_t must be smaller than product_t"
);

using FibonacciFunction = std::function<std::vector<digit_t>(size_t)>;

/**
 * @brief Calculate the Fibonacci number at the given index.
 */
std::vector<digit_t> fibonacci(size_t index);
std::vector<digit_t> fibonacciMatrix(size_t index);
std::vector<digit_t> fibonacciDouble(size_t index);
