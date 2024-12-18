# Very fast implementation of the Fibonacci sequence algorithm using the fast doubling method. Used for benchmarking

import time
import sys

DEFAULT_INDEX = 24

def fastFib(n: int) -> int:
    def fib_pair(k: int) -> tuple[int, int]:
        if k <= 0:
            return (k, 1)
        a, b = fib_pair(k >> 1)
        c = a * ((b << 1) - a)
        d = a * a + b * b
        if k & 1:
            return (d, c + d)
        return (c, d)
    return fib_pair(n)[0]

if __name__ == '__main__':
    start = time.time();
    arg = int(sys.argv[1])
    print(arg)
    inputVal = arg if arg else DEFAULT_INDEX
    big = fastFib(inputVal)
    end = time.time()
    print(f"Elapsed Time: {end - start:.4f} seconds")
    # print(big)