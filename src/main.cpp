#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

namespace collatz {

template <typename T>
T next(T n) {
    if (n % 2 == 0) {
        return n / 2;
    }
    // 3 * n + 1 is even, so divide it by 2 directly
    return (3 * n + 1) / 2;
}

template <typename T>
class Sequences {
   public:
    Sequences(T n) { seen_before.reserve(n); }
    bool add(T n) {
        if (!contains(n)) {
            seen_before.insert(n);
            return n == 1;
        }
        return true;
    }

   private:
    bool contains(T n) { return seen_before.find(n) != seen_before.end(); }
    std::unordered_set<T> seen_before;
};

template <typename T>
void sequence(T n, Sequences<T> &seq) {
    const T start = n;
    bool done = seq.add(n);
    while (!done) {
        n = next(n);
        // If n < start, no need to look in the hash_table, I know it converges
        // to 1 as I went through it before
        done = n < start || seq.add(n);
    }
}

template <typename T>
void increment(T &i) {
    // predicate: i is odd (even numbers are uninteresting)
    i += 2;
    // i is odd
    // we want to skip 2, 4, 5 and 8 modulo 9 as they are uninteresting
    if (i % 9 == 2) {
        // i is uniniteresting;
        // i + 1 is even, so uninteresting
        // i + 2 is congruent to 4 mod 9, so uninteresting
        // i + 3 is congruent to 5 mod 9 and even, so extremely uninteresting
        i += 4;
    }
    if (i % 9 == 8) {
        // i is uniniteresting;
        // i + 1 is even, so uninteresting
        i += 2;
    }
    if (i % 8 == 5) {
        // i is uniniteresting;
        // i + 1 is even, so uninteresting
        i += 2;
    }
}

}  // namespace collatz

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0]
                  << " N\n\twhere N is the number of points\n";
        return -1;
    }
    auto n = std::stoll(argv[1]);
    collatz::Sequences<decltype(n)> seq(2 * n);
    for (decltype(n) i = 1; i < n; collatz::increment(i)) {
        if (i % (n / 100) == 1) {
            std::cout << 100 * (i - 1) / n + 1 << "%\r";
            std::flush(std::cout);
        }
        collatz::sequence(i, seq);
    }
    std::cout << std::endl;
}
