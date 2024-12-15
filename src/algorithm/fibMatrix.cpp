#include "fib.h"
#include "util.h"

// struct mat2 {
//     factor_t *a, b, c, d;
// };

void printOut(const factor_t *const out, size_t size) {
    size_t index = size;
    while (index--) {
        std::cout << "out[" << index << "] "
                  << static_cast<unsigned int>(out[index]) << " ";
    }
    std::cout << std::endl;
    uint64_t sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += out[i] * std::pow(256, i);
    }
    std::cout << "sum: " << sum << std::endl;
}

std::vector<digit_t> fibonacciMatrix(size_t index) {
    std::cout << "fibonacciMatrix(" << index << ")" << std::endl;
    factor_t a[2] = { 0, 255 };
    factor_t b[2] = { 0, 255 };
    factor_t out[4] = { 0, 0, 0, 0 };
    Util::multiplyAccumulate<factor_t, product_t>(out, a, b, 2);
    printOut(out, 4);

    /*
    M2x2 step = (0, 1, 1, 1);
    M2x2 fib(step)
    while (index > 0) {
        if (index & 1) != 0) {
            fib = fib * step;
        }
        step *= step
        index >>= 1;
    }
    return top left
    */
    return std::vector<digit_t>();
}