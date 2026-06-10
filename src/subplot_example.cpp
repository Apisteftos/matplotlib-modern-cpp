#include "../include/matplotlib.h"

#include <iostream>
#include <vector>
#include <cmath>


namespace plt = matplotlibcpp;

int main() {

    const int n = 100;
    std::vector<double> x(n), sinY(n), cosY(n);

    for (int i = 0; i < n; ++i) {
        x[i] = i * 2 * M_PI / (n - 1);
        sinY[i] = std::sin(x[i]);
        cosY[i] = std::cos(x[i]);
    }

    
    plt::subplot(1, 2, 1);
    plt::plot(x, sinY, "b");
    plt::title("Sine");
    plt::grid(true);

    plt::subplot(1, 2, 2);
    plt::plot(x, cosY, "r");
    plt::title("Cosine");
    plt::grid(true);

    plt::tight_layout();
    plt::show();

    return 0;
}



