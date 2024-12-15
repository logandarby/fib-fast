#include "sciNumber.h"

namespace Util {
    long double logbase(const long double a, const unsigned int base) {
        return log(a) / log(base);
    }
}

const SciNumber SciNumber::ZERO{ .base = 10, .exponent = 0, .coefficient = 0 };

void SciNumber::convertBase(const unsigned int newBase) {
    if (newBase == base) {
        return;
    }
    const long double d =
        log10(coefficient) + exponent * Util::logbase(base, newBase);
    const long double c = pow(newBase, d - floor(d));
    base = newBase;
    exponent = floor(d);
    coefficient = c;
}

void SciNumber::normalize() {
    using namespace std;
    const long double digits = floor(Util::logbase(coefficient, base));
    coefficient /= pow(base, digits);
    exponent += digits;
}

std::ostream &operator<<(std::ostream &os, const SciNumber &sciNumber) {
    if (sciNumber.coefficient == 0) {
        os << "0";
        return os;
    }
    os << sciNumber.coefficient << " * " << sciNumber.base << "^"
       << sciNumber.exponent;
    return os;
}