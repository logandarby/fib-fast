#pragma once

#include "core.h"

struct SciNumber {
    size_t base;
    size_t exponent;
    long double coefficient;

    void convertBase(const unsigned int newBase);

    void normalize();

    static const SciNumber ZERO;

    template <typename T>
    static SciNumber fromDigitVector(const std::vector<T> &digits) {
        // Search for first non-zero digit
        const size_t TYPE_BITS = sizeof(T) * CHAR_BIT;
        T nonZeroDigit = 0;
        size_t nonZeroDigitIndex = 0;
        if (digits.empty()) {
            return SciNumber::ZERO;
        }
        for (size_t i = digits.size() - 1; i-- > 0;) {
            if (digits.at(i) != 0) {
                nonZeroDigit = digits.at(i);
                nonZeroDigitIndex = i;
                break;
            }
        };
        if (nonZeroDigit == 0) {
            return SciNumber::ZERO;
        }
        long double a = nonZeroDigit;
        if (nonZeroDigitIndex > 0) {
            a += static_cast<long double>(digits.at(nonZeroDigitIndex - 1)) /
                 pow(2, TYPE_BITS);
        }
        const size_t b = (nonZeroDigitIndex)*TYPE_BITS;
        SciNumber sciNumber{
            .base = 2,
            .exponent = b,
            .coefficient = a,
        };
        sciNumber.convertBase(10);
        sciNumber.normalize();
        return sciNumber;
    }
};

std::ostream &operator<<(std::ostream &os, const SciNumber &sciNumber);
