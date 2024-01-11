#include <iostream>
#include <array>
#include<numeric>

#define GET_VARIABLE_NAME(Variable) (#Variable)

int main() {
    constexpr std::array A{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    constexpr std::array B{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    const int aSum{std::accumulate(std::begin(A), std::end(A), 0)};
    const int bSum{std::accumulate(std::begin(B), std::end(B), 0)};

    std::cout << ((aSum < bSum) ? GET_VARIABLE_NAME(A) : GET_VARIABLE_NAME(B));

    return EXIT_SUCCESS;
}
