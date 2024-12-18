#include "fib.h"
#include <gmp.h>

using FibPair = std::array<mpz_t *, 4>;

void calculateFibPair(size_t index, FibPair &pair, size_t currentDigits) {
    std::stack<size_t> stack;

    while (index > 0) [[likely]] {
        stack.push(index);
        index >>= 1;
    }

    mpz_t &a = *pair[0];
    mpz_t &b = *pair[1];
    mpz_set_ui(a, 0);
    mpz_set_ui(b, 1);

    while (!stack.empty()) [[likely]] {
        index = stack.top();
        stack.pop();
        const size_t maxBits = Util::getMaxBits(index);  // TODO: Use this later
        mpz_t &a = *pair[0];
        mpz_t &b = *pair[1];
        mpz_t &c = *pair[2];
        mpz_t &d = *pair[3];  // Temporarily use as buffer
        // c = a * (2 * b - a);
        mpz_set_ui(c, 2);
        mpz_mul(c, c, b);
        mpz_sub(c, c, a);
        mpz_mul(c, a, c);
        // d = a * a + b * b;
        mpz_set_ui(d, 0);
        mpz_addmul(d, a, a);
        mpz_addmul(d, b, b);
        // if index odd, return (d, c + d)
        // if index even, return (c, d)
        if (index & 1) {
            mpz_add(c, c, d);
            mpz_swap(a, d);
            mpz_swap(b, c);
        } else {
            mpz_swap(a, c);
            mpz_swap(b, d);
        }
    }
}

std::vector<digit_t> fibonacciDouble(size_t index) {
    const size_t maxDigit = Util::getMaxDigits<mp_limb_t>(index) + 1;
    mpz_t a, b, c, d;
    mpz_init2(a, maxDigit);
    mpz_init2(b, maxDigit);
    mpz_init2(c, maxDigit);
    mpz_init2(d, maxDigit);

    FibPair pair{ &a, &b, &c, &d };
    calculateFibPair(index, pair, maxDigit);

    std::vector<mp_limb_t> result(maxDigit);
    std::copy(a->_mp_d, &a->_mp_d[a->_mp_alloc - 1], result.begin());

    mpz_clears(a, b, c, d, nullptr);
    return result;
}
