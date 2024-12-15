#pragma once

#include "fib.h"
#include <climits>

namespace Util {
    template <typename T>
    concept DigitType =
        std::unsigned_integral<T> || std::is_same_v<T, __uint128_t>;

    template <typename Factor, typename Product>
    concept ValidFactorProduct = DigitType<Factor> && DigitType<Product> &&
                                 sizeof(Factor) * 2 <= sizeof(Product);

    /**
     * @brief Get the maximum number of digits that can be stored in the
     * index-th fibonacci number in the datatype T
     */
    template <DigitType D>
    inline size_t getMaxDigits(const size_t index) {
        static const size_t DIGIT_BITS = sizeof(D) * CHAR_BIT;
        return (index - 1) / DIGIT_BITS + 1;
    }

    /**
     * @brief These built-in functions promote the first two operands into
     * infinite precision signed type and perform addition on those promoted
     * operands. The result is then cast to the type the third pointer argument
     * points to and stored there. If the result has carried, the function
     * returns true
     *
     * As the addition is performed in infinite signed precision, these built-in
     * functions have fully defined behavior for all argument values.
     *
     * @return true if the result has carried, false otherwise
     */
    template <typename T, typename R, typename S>
        requires std::is_convertible_v<T, S> && std::is_convertible_v<R, S>
    inline bool addOverflow(T a, R b, S *result) {
        return __builtin_add_overflow(a, b, result);
    }

    /**
     * @brief Computes a += b
     */
    template <DigitType T>
    unsigned char accumulate(T *a, const T *b, const size_t size) {
        unsigned char carry = 0;
        for (size_t i = 0; i < size; i++) {
            carry = addOverflow(a[i], carry, &a[i]);
            carry += static_cast<unsigned char>(addOverflow(a[i], b[i], &a[i]));
        }
        return a[size] = carry;
    }

    /**
     * @brief Multiply a by scalar and add the result to out
     *
     * Requires out has size * 2 items, and a has size items
     */
    template <typename Factor, typename Product>
        requires ValidFactorProduct<Factor, Product>
    void scalarMultAccumulate(
        Factor *out, const Factor *a, const Factor scalar, const size_t size,
        const size_t shiftFactor
    ) {
        for (size_t i = 0; i < size; i++) {
            Product product = a[i] * scalar;
            out[i + shiftFactor] += product;
            const Factor shifted = product >> (sizeof(Factor) * CHAR_BIT);
            out[i + shiftFactor + 1] += shifted;
        }
    }

    /**
     * @brief Multiply a by b and store the result in out
     *
     * Size refers to the size of a and b
     * Requires out has size * 2 elements
     */
    template <typename Factor, typename Product>
        requires ValidFactorProduct<Factor, Product>
    void multiplyAccumulate(
        Factor out[], const Factor a[], const Factor b[], const size_t size
    ) {
        for (size_t i = 0; i < size; i++) {
            out[i] = 0;
        }
        for (size_t i = 0; i < size; i++) {
            scalarMultAccumulate<Factor, Product>(out, a, b[i], size, i);
        }
    }

}
