#include <iostream>

// The aim of this code is to find famillies of collatz sequences that trivially converge to 1
// TODO:
// store proof,
// skip redundant checks such as 0 % 2 and 0 % 4,
// recognize cached sequences
template <typename T>
struct AmodB {
    AmodB(T a_, T b_): a(a_), b(b_) {
    }
    AmodB next_collatz() {
        if (is_even()) {
            return AmodB(a / 2, b / 2);
        } else {
            return AmodB(3 * a + 1, 3 * b);
        }
    }
    bool is_even() {
        return a % 2 == 0 && b % 2 == 0;
    }
    bool operator<(const AmodB& rhs) {
        return b < rhs.b;
    }
    void print() {
        std::cout << b << " * n + " << a;
    }
    T a;
    T b;
};

template <typename T>
bool is_trivial_sequence(AmodB<T> meta) {
    auto next = meta;
    auto depth = 10;
//    next.print() ;
//    std::cout << " -> ";
    for (auto i = 0; i < depth; ++i) {
        next = next.next_collatz();
//        std::cout << " ";
//        next.print();
//        std::cout << " -> ";
        if (next < meta) {
//            std::cout << "success!" << std::endl;
            return true;
        }
    }
//    std::cout << "nope..." << std::endl;
    return false;
}

template <typename T>
void find_trivial_sequences(AmodB<T> meta) {
    if (is_trivial_sequence(meta)) {
        meta.print();
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    auto how_many = 33;
    for (decltype(how_many) b = 2; b < how_many; ++b) {
        for (decltype(how_many) a = 1; a <= b; ++a) {
            find_trivial_sequences(AmodB<decltype(a)>(a, b));
        }
    }
}
