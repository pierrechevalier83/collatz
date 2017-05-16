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
    // predicates:
    //  .  all smaller numbers coallesce to 1
    //  a) i is congruent to 3 mod 4
    //  b) i is congruent to 1, 3, 6, 7 or 9 modulo 9
    //  c) i is congruent to 7 modulo 8
    //  d) i is congruent to 7, 15 or 31 modulo 32
    //
    // a)
    //   i must be odd
    //   because if it was even,
    //   2n -> n < 2n, so already visited
    //
    //   i must also be 3 % 4
    //   because if it was 1 %4,
    //   4n + 1 -> 12n + 4 -> 6n + 2 -> 3n + 1 < 4n + 1, so already visited
    //
    // b)
    //   2 mod 9 has already been visited by smaller number:
    //     6n + 1 -> 18n + 4 -> 9n + 2
    //   4 mod 9 has already been visited by smaller number:
    //     8n + 3 -> 24n + 10 -> 12n + 5 -> 36n + 16 -> 18n + 8 -> 9n + 4
    //   5 mod 9 has already been visited by smaller number:
    //     6n + 3 -> 18n + 10 -> 9n + 5
    //   8 mod 9 has already been visited by smaller number:
    //     6n + 5 -> 18n + 16 -> 9n + 8
    //
    // c)
    //   given a, i can be 3 % 8 or 7 % 8
    //   it must be 7 % 8
    //   because if it was 3 % 8
    //   8n + 3 -> 24n + 10 -> 12n + 5 -> 36n + 16 -> 18n + 8 -> 9n + 4 // already visited (see proof in b)
    //
    // d)
    //   given c, i can be 7, 15, 23 or 31 modulo 32
    //   but i can't be 23 modulo 32 because
    //   32n + 23 -> 32n + 23 -> 96n + 70 -> 48n + 35 -> 144n + 106 -> 72n + 53 -> 216n + 160 -> 108n + 80 -> 54n + 40 -> 27n + 20 < 32n + 23, so already studied

    i += 8;

    if (i % 9 == 2) {
        // let's move on to next 7 % 8
        i += 8; // (we are now 1 % 9)
    }
    if (i % 9 == 4) {
        i += 8; // (we are now 3 % 9)
    }
    if (i % 9 == 5) {
        // i + 8 == 4 % 9, so uninteresting
        i += 16; // (we are now 3 % 9)
    }
    if (i % 9 == 8) {
        // let's move on to next 3 % 4
        // i + 4 == 2 % 9, so uninteresting
         i += 8; // (we are now 7 % 9)
    }

    if (i % 32 == 23) {
         i += 8; // (we are now 31 % 32)
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
    for (decltype(n) i = 7; i < n; collatz::increment(i)) {
        std::cout << 100 * (i - 1) / n + 1 << "%\r";
        std::flush(std::cout);
        collatz::sequence(i, seq);
    }
    std::cout << std::endl;
}
