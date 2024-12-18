#pragma once

#include "core.h"
#include "fib.h"

/**
 * @brief A list of all possible algorithms, which must be matched in
 * ALGORITHM_MAP
 */
#define ALGORITHM_TABLE \
    X(LINEAR)           \
    X(MATRIX)           \
    X(FAST_DOUBLE)

#define X(a) a,
enum class AlgorithmType { ALGORITHM_TABLE };
#undef X

struct Arguments {
    size_t index;
    AlgorithmType algorithm;
};

class ArgumentError : public std::invalid_argument {
public:
    explicit ArgumentError(const std::string& message) :
        std::invalid_argument(message) {}
};

static const Arguments DEFAULT_ARGUMENTS{
    .index = 100'000,
    .algorithm = AlgorithmType::FAST_DOUBLE,
};

static const auto ALGORITHM_MAP =
    std::unordered_map<AlgorithmType, FibonacciFunction>{
        { AlgorithmType::LINEAR, fibonacci },
        { AlgorithmType::MATRIX, fibonacciMatrix },
        { AlgorithmType::FAST_DOUBLE, fibonacciDouble },
    };

class ArgumentParser {
public:
    static Arguments handleArguments(const int argc, const char* argv[]);
    static FibonacciFunction getAlgorithm(const AlgorithmType type);
    static void printUsage();
    static std::string getAlgorithmName(const AlgorithmType type);
};
