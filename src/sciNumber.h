#pragma once

#include <cmath>
#include <iostream>
#include <vector>

struct SciNumber {
    size_t base;
    size_t exponent;
    long double coefficient;

    void convertBase(const unsigned int newBase);

    void normalize();

    template <typename T>
    static SciNumber fromDigitVector(const std::vector<T> &digits) {
        // Search for first non-zero digit
        const size_t TYPE_BITS = sizeof(T) * CHAR_BIT;
        T nonZeroDigit = 0;
        size_t nonZeroDigitIndex = 0;
        for (size_t i = digits.size() - 1; i >= 0; i--) {
            if (digits.at(i) != 0) {
                nonZeroDigit = digits.at(i);
                nonZeroDigitIndex = i;
                break;
            }
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
