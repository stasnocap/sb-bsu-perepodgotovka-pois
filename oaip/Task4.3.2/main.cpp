#include <iostream>
#include <cmath>
#include <iomanip>
#include <array>

template<typename T>
bool approximatelyEqual(T dX, T dY);

void resetCharacterOutput();

namespace task {
    void whileApproach();

    void forApproach();
}

int main() {
    std::cout << "\tWhile approach:\n\n";
    task::whileApproach();

    resetCharacterOutput();

    std::cout << "\n\tFor approach:\n\n";
    task::forApproach();

    return EXIT_SUCCESS;
}

namespace task {
    void introduceMyselfAndPrintColumnTemplates(std::string_view whoAmI) {
        std::cout << std::fixed
                  << whoAmI << '\n'
                  << std::setw(6) << "j="
                  << std::setw(11) << "F(x)=\n\n";
    }

    double formula(double j) {
        return j < 2.5
               ? sin(j + -1.24)
               : sqrt(16) + j * j;
    }

    void calculateAndPrintRow(double j) {
        std::cout
                << std::setw(6) << std::setprecision(1) << j
                << std::setw(9) << std::setprecision(2) << task::formula(j) << '\n';
    }

    void whileApproach() {
        constexpr double maxJ{3.0};
        constexpr double stepJ{0.2};

        task::introduceMyselfAndPrintColumnTemplates("Kapitan Stas");

        double j{1};
        while (j < maxJ || approximatelyEqual(j, maxJ)) {
            calculateAndPrintRow(j);
            j += stepJ;
        }
    }

    void forApproach() {
        constexpr std::array<double, 3> array{1.3, 2.0, 2.6};

        task::introduceMyselfAndPrintColumnTemplates("Kapitan Stas");

        for (std::size_t index{0}; index < array.size(); ++index) {
            calculateAndPrintRow(array[index]);
        }
    }
}

void resetCharacterOutput() {
    std::cout.copyfmt(std::ios(nullptr));
}

template<typename T>
bool approximatelyEqual(const T dX, const T dY) {
    return std::abs(dX - dY) <= std::max(std::abs(dX), std::abs(dY))
                                * std::numeric_limits<T>::epsilon();
}