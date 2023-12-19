#include <iostream>
#include <cmath>

// 7 вариант

constexpr double funcX(double x) {
    return 3 * x + 2;
}

double task(double xb, double fx, double y) {
    if (xb > 1 && xb < 10) {
        return exp(fx);
    } else if (xb > 12 && xb < 40) {
        return std::pow(abs(fx + 4 * y), 1/3.);
    } else {
        return y * fx * fx;
    }
}

int main() {
    constexpr double x{1};
    constexpr double y{2};
    constexpr double b{3};
    constexpr double xb{x * b};
    constexpr double fx{funcX(x)};
    
    std::cout << task(xb, fx, y);

    return 0;
}
