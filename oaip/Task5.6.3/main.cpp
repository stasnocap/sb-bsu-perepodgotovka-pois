#include <iostream>
#include <array>
#include <numeric>

int main() {
    std::array<std::array<double, 3>, 3> arrayOfArray{{
                                                              {1.11, 2.22, 3.33},
                                                              {4.44, 5.55, 6.66},
                                                              {1.11, 5.55, 6.66}
                                                      }};

    double maxSum{};
    int maxSumIndex{};
    for (int i = 0; i < arrayOfArray.size(); ++i) {
        const std::array<double, 3> &array = arrayOfArray.at(i);
        const double sum{std::accumulate(array.begin(), array.end(), 0.0)};
        if (sum > maxSum) {
            maxSum = sum;
            maxSumIndex = i;
        }
    }

    std::cout << "Max sum elements of row with number " << maxSumIndex + 1;

    return 0;
}
