#pragma once

#include "core.h"
#include "util.h"
#include <gmp.h>

#ifdef _DEBUG
using digit_t = mp_limb_t;
#else
using digit_t = mp_limb_t;
#endif

using FibonacciFunction = std::function<std::vector<digit_t>(size_t)>;

/**
 * @brief Calculate the Fibonacci number at the given index.
 */
std::vector<digit_t> fibonacci(size_t index);
std::vector<digit_t> fibonacciMatrix(size_t index);
std::vector<digit_t> fibonacciDouble(size_t index);
