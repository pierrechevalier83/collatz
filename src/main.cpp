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
        chains.reserve(n);
        seen_before.reserve(n);
    }
    bool add_chain(T n) {
        chains.push_back({});
        return add(n);
    }
    bool add(T n) {
        chains.back().push_back(n);
        if (!contains(n)) {
            seen_before.insert(n);
            return n == 1;
        }
        return true;
    }
    void print_all() {
        for (const auto &chain : chains) {
            bool first = true;
            for (const auto &n : chain) {
                if (!first) {
                    std::cout << ' ';
                }
                first = false;
                std::cout << n;
            }
            std::cout << std::endl;
        }
    }

   private:
    bool contains(T n) { return seen_before.find(n) != seen_before.end(); }
    std::unordered_set<T> seen_before;
    std::vector<std::vector<T>> chains;
};

template <typename T>
void sequence(T n, Sequences<T> &seq) {
    const T start = n;
    bool done = seq.add_chain(n);
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
    collatz::Sequences<int> seq(n);
    // I can easily prove that all even numbers will converge to 1.
    // Avoid wasting effort!
    for (int i = 1; i < n; i += 2) {
        collatz::sequence(i, seq);
    }
    seq.print_all();
}
