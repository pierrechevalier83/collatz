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
    Sequences(T n) {
        seen_before.reserve(n);
    }
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
        // If n < start, no need to look in the hash_table, I know it converges to 1 as I went through it before
        done = n < start || seq.add(n);
    }
}

}  // namespace collatz

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0]
                  << " N\n\twhere N is the number of points\n";
        return -1;
    }
    int n = atoi(argv[1]);
    collatz::Sequences<int> seq(2*n);
    // I can easily prove that all even numbers will converge to 1.
    // Avoid wasting effort!
    for (int i = 1; i < n; i += 2) {
        if (i % (n/100) == 1) { std::cout << 100 * (i - 1) / n + 1 << "%\r"; std::flush(std::cout); }
        collatz::sequence(i, seq);
    }
    std::cout << std::endl;
}
