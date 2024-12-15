#include "arguments.h"

Arguments ArgumentParser::handleArguments(const int argc, const char* argv[]) {
    size_t index = DEFAULT_ARGUMENTS.index;
    if (argc > 1) {
        const auto arg = argv[1];
        try {
            index = std::stoull(arg);
        } catch (const std::exception& e) {
            throw ArgumentError(
                "Index " + std::string(arg) + " is not a number"
            );
        }
    }
    AlgorithmType algorithm = DEFAULT_ARGUMENTS.algorithm;
    if (argc > 2) {
        const auto arg = std::string(argv[2]);
#define X(a) \
            if (arg == #a) { \
                return { index, AlgorithmType::a }; \
            }
        ALGORITHM_TABLE
#undef X
        throw ArgumentError("Algorithm " + std::string(arg) + " is not valid");
    }
    return {
        .index = index,
        .algorithm = algorithm,
    };
}

FibonacciFunction ArgumentParser::getAlgorithm(const AlgorithmType type) {
    try {
        return ALGORITHM_MAP.at(type);
    } catch (const std::out_of_range& e) {
        throw ArgumentError(
            "Algorithm type " + getAlgorithmName(type) +
            " exists, but no matching function was found in ALGORITHM_MAP"
        );
    }
}

void ArgumentParser::printUsage() {
    std::cout << "Usage: fib [index] [algorithm]" << std::endl;
    std::cout << "  index:     The index of the Fibonacci number to calculate"
              << std::endl;
    std::cout << "  algorithm: The algorithm to use for calculation"
              << std::endl;
    std::cout << "             Options: ";
#define X(a) \
    std::cout << #a << " ";
    ALGORITHM_TABLE
#undef X
    std::cout << std::endl;
}

std::string ArgumentParser::getAlgorithmName(const AlgorithmType type) {
    switch (type) {
#define X(a) \
        case AlgorithmType::a: \
            return #a;
        ALGORITHM_TABLE
    }
#undef X
    return "UNKNOWN";
}