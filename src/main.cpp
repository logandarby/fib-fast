#include "Timer.h"
#include "arguments.h"
#include "core.h"
#include "fib.h"
#include "sciNumber.h"

void run(const int argc, const char* argv[]) {
    const Arguments arguments = ArgumentParser::handleArguments(argc, argv);

    std::cout << "Calculating Fibonacci(" << arguments.index << ") on "
              << BUILD_TYPE << " build using algorithm "
              << ArgumentParser::getAlgorithmName(arguments.algorithm) << "..."
              << std::endl;

    Timer timer;
    timer.start();

    const auto algorithm = ArgumentParser::getAlgorithm(arguments.algorithm);
    const auto result = algorithm(arguments.index);

    timer.stop();

    const auto str = SciNumber::fromDigitVector(result);
    std::cout << "Elapsed time: " << timer.getElapsedSeconds() << " seconds"
              << std::endl;
    std::cout << "Fibonacci(" << arguments.index << ") = " << str << std::endl;
}

int main(const int argc, const char* argv[]) {
    try {
        run(argc, argv);
    } catch (const ArgumentError& e) {
        std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
        ArgumentParser::printUsage();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
