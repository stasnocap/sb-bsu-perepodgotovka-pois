#include <cstdlib>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

int main() {
    std::vector<int> array = {8, 4, 5, 9};

    std::sort(array.begin(), array.end(), std::less{});

    array.erase(array.begin());
    array.erase(array.end());

    std::cout <<
              (double) std::accumulate(array.begin(), array.end(), 0)
              /
              (double) std::ssize(array);

    return EXIT_SUCCESS;
}