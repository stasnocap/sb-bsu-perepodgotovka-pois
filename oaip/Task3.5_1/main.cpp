#include <math.h>;
#include <iostream>

int main() {
    const double percent{10};
    const double loanAmount{123};
    const int paymentsPerYear{2};
    const int countOfYears{1};

    std::cout << (percent * loanAmount / paymentsPerYear) /
                 pow(1 - ((percent / paymentsPerYear) + 1), -paymentsPerYear * countOfYears);

    return 0;
}