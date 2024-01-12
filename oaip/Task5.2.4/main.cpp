#include <array>
#include <algorithm>
#include <iostream>
#include <numeric>

int main() {
    constexpr int zero{0};
    constexpr std::array array{1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};

    const int *foundFirst{std::find(array.begin(), array.end(), zero)};

    if (foundFirst == array.end()) {
        std::cout << "Does not contain zero";
        return EXIT_SUCCESS;
    }

    const long long foundFirstIndex{foundFirst - array.begin()};

    if (foundFirstIndex == 0) {
        std::cout << "Zero can't be first value";
        return EXIT_SUCCESS;
    }

    const int *foundSecond{std::find(foundFirst + 1, array.end(), zero)};

    if (foundSecond == array.end()) {
        std::cout << "Does not contain two zeros";
        return EXIT_SUCCESS;
    }

    const long long foundSecondIndex{foundSecond - array.begin()};

    if (foundSecondIndex == std::ssize(array)) {
        std::cout << "Zero can't be last value";
        return EXIT_SUCCESS;
    }

    const int *foundThird{std::find(foundSecond + 1, array.end(), zero)};

    if (foundThird != array.end()) {
        std::cout << "Only two zero's possible";
        return EXIT_SUCCESS;
    }

    std::cout << 
        std::accumulate(array.begin(), array.begin() + foundFirstIndex, 0)
        +
        std::accumulate(array.begin() + foundSecondIndex, array.end(), 0);

    return EXIT_SUCCESS;
}