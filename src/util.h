#pragma once

#include "core.h"
#include <climits>

namespace Util {
    template <typename T>
    concept DigitType =
        std::unsigned_integral<T> || std::is_same_v<T, __uint128_t>;

    template <typename Factor, typename Product>
    concept ValidFactorProductPair = DigitType<Factor> && DigitType<Product> &&
                                     sizeof(Factor) * 2 <= sizeof(Product);

    template <typename T, typename D = decltype(T()[0])>
    concept IndexableToDigit = requires(T t, D d) {
        requires DigitType<std::remove_reference_t<D>>;
        { t.at(0) } -> std::convertible_to<D>;
        { t[0] } -> std::convertible_to<D>;
        { t.size() } -> std::same_as<size_t>;
    };

    /**
     * @brief Get the maximum number of digits that can be stored in the
     * index-th fibonacci number in the datatype T
     */
    template <DigitType D>
    inline size_t getMaxDigits(const size_t index) {
        if (index == 0) {
            return 1;
        }
        const size_t DIGIT_BITS = sizeof(D) * CHAR_BIT;
        const size_t sizeToAllocate = (index + DIGIT_BITS - 1) / DIGIT_BITS + 1;
        return std::max(sizeToAllocate, static_cast<size_t>(1));
    }

    /**
     * @brief From GCC: These built-in functions promote the first two operands
     * into infinite precision signed type and perform addition on those
     * promoted operands. The result is then cast to the type the third pointer
     * argument points to and stored there. If the result has carried, the
     * function returns true
     *
     * As the addition is performed in infinite signed precision, these built-in
     * functions have fully defined behavior for all argument values.
     *
     * @return true if the result has carried, false otherwise
     */
    template <typename T, typename R, typename S>
        requires std::is_convertible_v<T, S> && std::is_convertible_v<R, S>
    [[nodiscard]] inline bool addOverflow(T a, R b, S *result) {
        return __builtin_add_overflow(a, b, result);
    }
    /**
     * @brief Computes A += B with carry
     */
    template <typename T, typename R>
        requires std::is_convertible_v<R, T>
    [[nodiscard]] inline bool addOverflow(T &a, R b) {
        return __builtin_add_overflow(a, b, &a);
    }

    /**
     * @brief Computes a += b
     *
     * Requires that accumulate has enough for a carry bit
     */
    template <IndexableToDigit T>
    unsigned char accumulate(T &a, const T &b, const size_t size) {
        unsigned char carry = 0;
        for (size_t i = 0; i < size; i++) {
            carry = addOverflow(a.at(i), carry, &a.at(i));
            carry += static_cast<unsigned char>(
                addOverflow(a.at(i), b.at(i), &a.at(i))
            );
        }
        ASSERT(
            a.size() > size,
            "Argument \"a\" must have enough space for a carry bit"
        );
        return a.at(size) = carry;
    }

    /**
     * @brief Computes a -= b
     */
    template <
        typename T, DigitType D = std::remove_reference_t<decltype(T()[0])>>
        requires IndexableToDigit<T, D>
    bool subtractAccumulate(T &a, const T &b, const size_t size) {
        unsigned char underflow = 0;
        for (size_t i = 0; i < size; i++) {
            underflow = addOverflow(a.at(i), underflow, &a.at(i));
            D twosComplement = ~b.at(i);
            if (i == 0) {
                underflow +=
                    static_cast<unsigned char>(addOverflow(twosComplement, 1));
            }
            underflow += static_cast<unsigned char>(
                addOverflow(a.at(i), twosComplement, &a.at(i))
            );
        }
        return !underflow;
    }

    /**
     * @brief Multiply a by scalar and add the result to out
     *
     * Requires out has size * 2 items, and a has size items
     */
    template <
        typename Factor, typename Product, IndexableToDigit<Factor> I,
        IndexableToDigit<Factor> J>
        requires ValidFactorProductPair<Factor, Product>
    void scalarMultAccumulate(
        I &out, const J &a, const Factor &scalar, const size_t size,
        const size_t shiftFactor
    ) {
        for (size_t i = 0; i < size; i++) {
            Product product = a.at(i) * scalar;
            const bool carry = addOverflow(
                out.at(i + shiftFactor), static_cast<Factor>(product)
            );
            const Factor shifted = product >> (sizeof(Factor) * CHAR_BIT);
            const bool carry2 =
                addOverflow(out.at(i + shiftFactor + 1), shifted + carry);
            if (i < size - 1) {
                out.at(i + shiftFactor + 2) += carry2;
            }
        }
    }

    /**
     * @brief Multiply a by b and add the result in out
     *
     * Size refers to the size of a and b
     * Requires out has size * 2 elements
     */
    template <
        typename Factor, typename Product, IndexableToDigit<Factor> I,
        IndexableToDigit<Factor> J>
        requires ValidFactorProductPair<Factor, Product>
    void multiplyAccumulate(I &out, const J &a, const J &b, const size_t size) {
        ASSERT(&out != &a && &out != &b);
        const size_t halfSize = size / 2;
        for (size_t i = 0; i < halfSize; i++) {
            scalarMultAccumulate<Factor, Product>(out, a, b.at(i), halfSize, i);
        }
    }

    /**
     * @brief Shift a to the left by shift bits
     *
     * @returns The carry from the shift, if it's occured
     */
    template <IndexableToDigit T>
    auto bitShiftLeft(T &out, const size_t size, const size_t shift) {
        ASSERT(!(shift == 0 || size == 0))
        const size_t bitSize = sizeof(out.at(0)) * CHAR_BIT;
        const size_t shiftRemainder = bitSize - shift;
        const auto carry = out.at(size - 1) >> shiftRemainder;
        for (size_t i = size - 1; i >= 1; i--) {
            const auto test = 2;
            const auto currentShift = (out.at(i) << shift);
            const auto remainderShift = (out.at(i - 1) >> shiftRemainder);
            out.at(i) = currentShift | remainderShift;
        }
        out.at(0) <<= shift;
        return carry;
    }

    template <IndexableToDigit T>
    void bitShiftRight(T &out, const size_t size, const size_t shift) {
        ASSERT(!(shift == 0 || size == 0))
        const size_t bitSize = sizeof(out.at(0)) * CHAR_BIT;
        const size_t shiftRemainder = bitSize - shift;
        for (size_t i = 0; i < size - 1; i++) {
            const auto currentShift = (out.at(i) >> shift);
            const auto remainderShift = (out.at(i + 1) << shiftRemainder);
            out.at(i) = currentShift | remainderShift;
        }
        out.at(size - 1) >>= shift;
    }

}
