#include <iostream>

namespace collatz {

template <typename T>
T next(T n) {
    if (n % 2 == 0) {
        return n / 2;
    }
    return 3 * n + 1;
}

template <typename T>
void sequence(T n) {
    std::cout << n;
    while (n != 1) {
        n = next(n);
        std::cout << " " << n;
    }
    std::cout << std::endl;
}

} // namespace collatz

int main() {
    for (int i = 1; i < 10; ++i) {
      collatz::sequence(i);
    }
}
