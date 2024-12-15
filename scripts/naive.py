# Naive implementation of the Fibonacci sequence algorithm

import time

DEFAULT_INDEX = 400_000

def fibonacci(index: int) -> int:
    a = 0
    b = 1
    for _ in range(index):
        a, b = b, a + b
    return a

if __name__ == '__main__':
    start = time.time();
    fibonacci(DEFAULT_INDEX)
    end = time.time()
    print(f"Elapsed Time: {end - start:.4f} seconds")