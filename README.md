# Fib Fast!

Fun project aimed at calculating incredibly large Fibonacci numbers incredibly fast.

## Dependencies

This project requires GNU MP (gmplib) to run. On windows, I've installed it from MSYS2 using MinGW terminal: `pacman -S mingw-w64-x86_64-gmp`. You can install this on other operating systems using your desired package manager.

I've included a pre-built binary for x64 Windows, which has the latest debug build under `release`.

## Building

The project is built using cmake.

If you have Ninja installed, you can simply build the project using the default setting
```bash
cd build 
cmake .
ninja
./FibFast.exe
```

If you don't have Ninja installed, you can use the default makefile generator by running
```bash
cmake -G "Unix Makefiles" .
make
./FibFast.exe
```

## Usage

Right now, there are a couple algorithms implemented. You can run the program with the `--help` or `-h` flag to see the most up-to-date usage.

Current usage:
```bash
Usage: fib [index] [algorithm]
  index:     The index of the Fibonacci number to calculate
  algorithm: The algorithm to use for calculation
             Options: LINEAR MATRIX FAST_DOUBLE 
```

Currently, the fastest algorithm is `FAST_DOUBLE`, which can calculate ~100,000,000-th Fibonacci number in under 1 second.
