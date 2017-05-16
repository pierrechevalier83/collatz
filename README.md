The collatz conjecture
----------------------

The 3x+1 problem is a conjecture in mathematics which can be summarized as follows. Take any positive integer n. If n is even, divide it by 2 to get n / 2. If n is odd, multiply it by 3 and add 1 to obtain 3n + 1. Repeat the process (which has been called "Half Or Triple Plus One", or HOTPO[1]) indefinitely. The conjecture is that no matter what number you start with, you will always eventually reach 1.

This repo is an exercise in code optimization: I want to see how fast I can test this conjecture with many numbers.

Build steps
-----------

`mkdir build`
`cd build`
`cmake -DCMAKE_BUILD_TYPE=release ..`
`make -j8`

Usage
-----

`time ./collatz 10000000 > ten_millions.txt`

Current performance
-------------------

Measuring the time to evaluate go throught the first ten million:
```
./collatz 10000000  7.32s user 0.16s system 99% cpu 7.475 total
```
