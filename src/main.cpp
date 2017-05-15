#include <iostream>
#include <unordered_map>
#include <vector>

namespace collatz {

template <typename T>
T next(T n) {
    if (n % 2 == 0) {
        return n / 2;
    }
    return 3 * n + 1;
}

template <typename T>
class Sequences {
public:
    bool add_chain(T n) {
        chains.push_back({});
        return add(n);
    }
    bool add(T n) {
        if (!contains(n)) {
            chains.back().push_back(n);
            which_chain[n] = chains.size() - 1;
            return n == 1;
        }
        return true;
    }
    void print_all() {
        for (const auto& chain: chains) {
            for (const auto& n: chain) {
                std::cout << n << " ";
            }
            std::cout << std::endl;
        }
    }
private:
    bool contains(T n) {
        return which_chain.find(n) != which_chain.end();
    }
    std::unordered_map<T, T> which_chain;
    std::vector<std::vector<T>> chains;
};

template <typename T>
void sequence(T n, Sequences<T>& seq) {
    bool done = seq.add_chain(n);
    while (!done) {
        n = next(n);
        done = seq.add(n);
    }
}

} // namespace collatz

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " N\n\twhere N is the number of points\n";
        return -1;
    }
    int n = atoi(argv[1]);
    collatz::Sequences<int> seq;
    for (int i = 1; i < n; ++i) {
      collatz::sequence(i, seq);
    }
    seq.print_all();
}
