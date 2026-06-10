#include "../include/matplotlib.h"

#include <iostream>
#include <math.h>
#include <vector>

namespace plt = matplotlibcpp;


int main() {
    

    const int n = 100;
    std::vector<double> x(n), sinY(n), cosY(n), tanY(n), acosY(n);

    for (int i = 0; i < n; ++i) {
        x[i] = i * 2 * M_PI / (n - 1);
        sinY[i] = std::sin(x[i]);
        cosY[i] = std::cos(x[i]);
        tanY[i] = std::tan(x[i]);
        acosY[i] = std::acos(x[i]);

    }

    std::vector<long> figsize = {10, 10};
    auto [fig, axes] = plt::subplots(2, 2, figsize);   
    
    
    axes[0].plot(x, sinY, "b");
    axes[0].set_title("Sine");
    axes[0].grid(true);
    

    axes[1].plot(x, cosY, "r");
    axes[1].set_title("Cosine");
    axes[1].grid(true);


    axes[2].plot(x, tanY, "g");
    axes[2].set_title("Tangent");
    axes[2].grid(true);

    axes[3].plot(x, acosY, "m");
    axes[3].set_title("Arccosine");
    axes[3].grid(true);


    fig.suptitle("Math Functions");
    fig.save("../pics/math_functions.png");
    // fig.tight_layout();
    
    plt::tight_layout();
    plt::show();

    return 0;
}