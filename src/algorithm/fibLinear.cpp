#include "fib.h"
#include "util.h"

std::vector<digit_t> fibonacci(size_t index) {
    const size_t maxDigits = Util::getMaxDigits<digit_t>(index);
    std::vector<digit_t> currentAllocation(maxDigits, 0);
    std::vector<digit_t> nextAllocation(maxDigits, 0);
    nextAllocation[0] = 1;
    size_t ndigits = 1;
    while (index--) {
        ndigits += Util::accumulate(nextAllocation, currentAllocation, ndigits);
        std::swap(currentAllocation, nextAllocation);
    }
    return currentAllocation;
}
