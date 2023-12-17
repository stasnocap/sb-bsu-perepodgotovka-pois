#include <math.h>;
#include <iostream>

int main() {
    const double x{0.1722};
    const double y{6.33};
    const double z{3.25e-4};

    std::cout << 5 * atan(x) - acos(x) / 4 * (x + 3 * fabs(x - y) + x * x) / (fabs(x - y) * z + x * x);

    return 0;
}