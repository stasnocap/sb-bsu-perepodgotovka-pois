#include <iostream>
#include <array>
#include <numeric>

int main() {
    constexpr int arraySize{3};

    std::array<std::array<int, arraySize>, arraySize> arrayOfArray{{
                                                                           {2, 9, 4},
                                                                           {7, 5, 3},
                                                                           {6, 1, 8},
                                                                   }};

    const int sum{std::accumulate(arrayOfArray[0].begin(), arrayOfArray[0].end(), 0)};
    bool isMagicSquare{true};
    for (int i = 1; i < arraySize; ++i) {
        if (std::accumulate(arrayOfArray[i].begin(), arrayOfArray[i].end(), 0) != sum) {
            isMagicSquare = false;
            break;
        }
    }

    if (!isMagicSquare) {
        std::cout << "It is not magic square";
        return 0;
    }

    for (int i = 0; i < arraySize; ++i) {
        double columnSum{};
        for (int j = 0; j < arrayOfArray.size(); ++j) {
            if (j >= arrayOfArray.size() || i >= arrayOfArray.at(j).size()) {
                continue;
            }
            columnSum += arrayOfArray.at(j).at(i);
        }

        if (sum != columnSum) {
            isMagicSquare = false;
            break;
        }
    }

    if (!isMagicSquare) {
        std::cout << "It is not magic square";
        return 0;
    }

    int mainDiagonalSum{};
    int secondaryDiagonalSum{};
    for (int i = 0; i < arraySize; ++i) {
        mainDiagonalSum += arrayOfArray[i][i];
        secondaryDiagonalSum += arrayOfArray[i][arraySize - i - 1];
    }

    if (mainDiagonalSum != sum || secondaryDiagonalSum != sum) {
        std::cout << "It is not magic square";
        return 0;
    }

    std::cout << "It is magic square!";

    return 0;
}
