# Very fast implementation of the Fibonacci sequence algorithm using the fast doubling method. Used for benchmarking

import time

DEFAULT_INDEX = 20

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
    print(fastFib(DEFAULT_INDEX))
    end = time.time()
    print(f"Elapsed Time: {end - start:.4f} seconds")