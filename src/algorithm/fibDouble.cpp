#include "fib.h"
#include "util.h"

template <Util::DigitType Factor>
using FibPairElement = std::span<Factor>;

template <Util::DigitType Factor>
using FibPair = std::array<FibPairElement<Factor> *, 4>;

template <typename Factor, typename Product>
    requires Util::ValidFactorProductPair<Factor, Product>
void calculateFibPair(
    size_t index, FibPair<Factor> &pair, size_t currentDigits
) {
    std::stack<size_t> stack;

    while (index > 0) [[likely]] {
        stack.push(index);
        index >>= 1;
        // TODO: Make currentDigits smaller every iteration
    }

    pair.at(0)->operator[](0) = 0;
    pair.at(1)->operator[](0) = 1;

    // TODO: For some reason this does not compute high numbers accurately.

    while (!stack.empty()) [[likely]] {
        index = stack.top();
        stack.pop();
        currentDigits = Util::getMaxDigits<Factor>(index);
        FibPairElement<Factor> *a = pair[0];
        FibPairElement<Factor> *b = pair[1];
        // c = a * (2 * b - a);
        FibPairElement<Factor> *c = pair[2];
        std::fill(c->begin(), c->end(), 0);
        FibPairElement<Factor> *d = pair[3];  // Temporarily use as buffer
        std::copy(b->begin(), b->end(), d->begin());
        Util::bitShiftLeft(*d, currentDigits, 1);
        const bool underflow = Util::subtractAccumulate(
            *d, *a, currentDigits
        );  // TODO: Remove calls to size for efficiency
        ASSERT(!underflow);
        Util::multiplyAccumulate<Factor, Product>(*c, *a, *d, currentDigits);
        // d = a * a + b * b;
        std::fill(d->begin(), d->end(), 0);
        Util::multiplyAccumulate<Factor, Product>(*d, *a, *a, currentDigits);
        Util::multiplyAccumulate<Factor, Product>(*d, *b, *b, currentDigits);

        // if index odd, return (d, c + d)
        // if index even, return (c, d)
        if (index & 1) {
            Util::accumulate(*c, *d, currentDigits - 1);
            std::swap(*pair[0], *pair[3]);
            std::swap(*pair[1], *pair[2]);
        } else {
            std::swap(*pair[0], *pair[2]);
            std::swap(*pair[1], *pair[3]);
        }
    }
}

std::vector<digit_t> fibonacciDouble(size_t index) {
    const size_t maxDigit = Util::getMaxDigits<factor_t>(index) + 1;
    factor_t *alloc = new factor_t[maxDigit * 4]();
    FibPairElement<factor_t> a(alloc, maxDigit);
    FibPairElement<factor_t> b(&alloc[maxDigit], maxDigit);
    FibPairElement<factor_t> c(&alloc[maxDigit * 2], maxDigit);
    FibPairElement<factor_t> d(&alloc[maxDigit * 3], maxDigit);
    FibPair<factor_t> pair{ &a, &b, &c, &d };
    calculateFibPair<factor_t, product_t>(index, pair, maxDigit);
    std::vector<digit_t> result(maxDigit);
    std::copy(pair[0]->begin(), pair[0]->end(), result.begin());
    delete[] alloc;
    return result;
}
