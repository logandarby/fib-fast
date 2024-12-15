#include "fib.h"
#include "util.h"
#include <climits>
#include <concepts>
#include <cstdlib>
#include <span>

std::vector<digit_t> fibonacci(size_t index) {
    const size_t maxDigits = Util::getMaxDigits<digit_t>(index);
    digit_t *currentAllocation = new digit_t[maxDigits]();
    digit_t *nextAllocation = new digit_t[maxDigits]();
    nextAllocation[0] = 1;
    size_t ndigits = 1;
    while (index--) {
        ndigits += Util::accumulate(nextAllocation, currentAllocation, ndigits);
        std::swap(currentAllocation, nextAllocation);
    }

    delete[] nextAllocation;
    std::vector<digit_t> currentAllocationVector(
        currentAllocation, currentAllocation + ndigits
    );
    return currentAllocationVector;
}
