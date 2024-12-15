# Very fast implementation of the Fibonacci sequence algorithm using the matrix exponentiation method. Used for benchmarking

import time

DEFAULT_INDEX = 400_000

def fastFib(n: int) -> int:
    def fib_pair(k: int) -> tuple[int, int]:
        if k <= 0:
            return (k, 1)
        fh, fh1 = fib_pair(k >> 1)
        fk = fh * ((fh1 << 1) - fh)
        fk1 = fh * fh + fh1 * fh1
        if k & 1:
            return (fk1, fk + fk1)
        return (fk, fk1)
    return fib_pair(n)[0]

if __name__ == '__main__':
    start = time.time();
    fastFib(DEFAULT_INDEX)
    end = time.time()
    print(f"Elapsed Time: {end - start:.4f} seconds")