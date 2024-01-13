#include <iostream>
#include <array>

template<typename T, std::size_t Row, std::size_t Col>
void printArray(std::array<std::array<T, Col>, Row> &array) {
    for (std::array<T, Col> &row: array) {
        for (T &col: row) {
            std::cout << col << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    constexpr int arraySize{5};

    std::array<std::array<int, arraySize>, arraySize> array{};

    for (int i = 0; i < array.size(); ++i) {
        array[i][i] = 1;
    }

    printArray(array);

    return 0;
}