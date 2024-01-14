#include <iostream>
#include <vector>
#include <format>
#include <iomanip>
#include <algorithm>

std::string getString(std::string_view ask) {
    std::cout << ask;
    std::string input{};
    std::getline(std::cin, input);
    return input;
}

int main() {
    constexpr int maxRows{20};

    std::string_view stopKey{getString("Please enter stop key:\n")};

    std::vector<std::vector<double>> arrayOfArray{};
    int stopCount{};
    for (int row = 1; row < maxRows; ++row) {
        if (stopCount > 1) {
            break;
        }

        std::vector<double> array{};
        while (true) {
            std::string input{getString(std::format("Please add column {} for row {}:\n", array.size() + 1, row))};

            if (input == stopKey) {
                if (stopCount <= 0) {
                    arrayOfArray.push_back(array);
                }

                stopCount++;
                break;
            }

            double number{};
            try {
                number = std::stod(input);
            } catch (std::exception &exception) {
                std::cout << std::format("Can't parse to double: {}\n", input);
                continue;
            }

            if (stopCount > 0) {
                array = {};
            }

            array.push_back(number);

            stopCount = 0;
        }
    }

    std::size_t maxElements{std::max_element(arrayOfArray.begin(), arrayOfArray.end(),
                                             [](std::vector<double> first, std::vector<double> second) {
                                                 return first.size() < second.size();
                                             })->size()};

    std::vector<double> sumRow{};
    for (int i = 0; i < maxElements; ++i) {
        double sum{};
        for (int j = 0; j < arrayOfArray.size(); ++j) {
            if (j >= arrayOfArray.size() || i >= arrayOfArray.at(j).size()) {
                continue;
            }
            sum += arrayOfArray.at(j).at(i);
        }
        sumRow.push_back(sum);
    }
    arrayOfArray.push_back(sumRow);

    std::cout << std::fixed;
    for (std::vector<double> &array: arrayOfArray) {
        for (double &el: array) {
            std::cout << std::setprecision(2) << el << std::setw(6);
        }
        std::cout << '\n';
    }

    return 0;
}