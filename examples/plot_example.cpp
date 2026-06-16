#include "../include/Matplotlib.h"

#include <iostream>
#include <vector>




int main() {

    matplotlibcpp::PyPlot plt;

    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {1, 4, 9, 16, 25};

    plt.plot({x, y});
    plt.show();

    return 0;
}