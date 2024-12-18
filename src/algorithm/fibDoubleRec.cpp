#include "fib.h"
#include "util.h"

// Recursive version of the fibDouble algorithm, kept for reference

template <Util::DigitType Factor>
using FibPairElement = std::vector<Factor>;

template <Util::DigitType Factor>
using FibPair = std::array<FibPairElement<Factor> *, 4>;

template <typename Factor, typename Product>
    requires Util::ValidFactorProductPair<Factor, Product>
void calculateFibPair(
    size_t index, FibPair<Factor> &pair, size_t currentDigit
) {
    if (index <= 0) {
        pair[0]->at(0) = 0;
        pair[1]->at(0) = 1;
        return;
    }
    calculateFibPair<Factor, Product>((index >> 1), pair, currentDigit);
    FibPairElement<Factor> *a = pair[0];
    FibPairElement<Factor> *b = pair[1];
    // c = a * (2 * b - a);
    FibPairElement<Factor> *c = pair[2];
    std::fill(c->begin(), c->end(), 0);
    FibPairElement<Factor> *d = pair[3];  // Temporarily use as buffer
    std::copy(b->begin(), b->end(), d->begin());
    Util::bitShiftLeft(*d, d->size(), 1);
    const bool underflow = Util::subtractAccumulate(
        *d, *a, d->size()
    );  // TODO: Remove calls to size for efficiency
    ASSERT(!underflow);
    Util::multiplyAccumulate<Factor, Product>(*c, *a, *d, d->size());
    // d = a * a + b * b;
    std::fill(d->begin(), d->end(), 0);
    Util::multiplyAccumulate<Factor, Product>(*d, *a, *a, a->size());
    Util::multiplyAccumulate<Factor, Product>(*d, *b, *b, b->size());

    // if index odd, return (d, c + d)
    // if index even, return (c, d)
    if (index & 1) {
        Util::accumulate(*c, *d, c->size() - 1);
        std::swap(*pair[0], *pair[3]);
        std::swap(*pair[1], *pair[2]);
    } else {
        std::swap(*pair[0], *pair[2]);
        std::swap(*pair[1], *pair[3]);
    }
}