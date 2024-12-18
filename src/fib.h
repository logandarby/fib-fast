#pragma once

#include "core.h"
#include "util.h"

#ifdef _DEBUG
using digit_t = uint8_t;
#else
using digit_t = uint8_t;
#endif

using factor_t = digit_t;
using product_t = uint16_t;  // must be at least 2 * factor_t

static_assert(
    2 * sizeof(factor_t) <= sizeof(product_t),
    "product_t must be able to fit 2 * factor_t bytes"
);

using FibonacciFunction = std::function<std::vector<digit_t>(size_t)>;

/**
 * @brief Calculate the Fibonacci number at the given index.
 */
std::vector<digit_t> fibonacci(size_t index);
std::vector<digit_t> fibonacciMatrix(size_t index);
std::vector<digit_t> fibonacciDouble(size_t index);
