#include "../include/Matplotlib.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {

    matplotlibcpp::PyPlot plt;

    const int n = 100;
    std::vector<double> x(n); 

    for (int i = 0; i < n; ++i) {
         x[i] = i * 10.0 / (n - 1);
    }

    std::vector<double> y1(x.size()), y2(x.size()), y3(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        y1[i] = std::exp(x[i]);    
        y2[i] = std::exp(x[i] * 0.5);  
        y3[i] = std::exp(x[i] * 0.2);  
    }

    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 2, .figsize = {12, 5}});
    
    axes[0].semilogy({.x = x, .y = y1, .fmt = "b", .label = "e^x"});
    axes[0].semilogy({.x = x, .y = y2, .fmt = "r", .label = "e^0.5x"});
    axes[0].semilogy({.x = x, .y = y3, .fmt = "g", .label = "e^0.2x"});
    axes[0].set_title("semilogy");
    axes[0].set_xlabel({.xlabel = "x (linear scale)"});
    axes[0].set_ylabel({.ylabel = "y (log scale)"});
    axes[0].legend();
    axes[0].grid({.visible = true, .which = "both"});


    axes[1].plot({.x = x, .y = y1, .fmt = "b", .label = "e^x"});
    axes[1].plot({.x = x, .y = y2, .fmt = "r", .label = "e^0.5x"});
    axes[1].plot({.x = x, .y = y3, .fmt = "g", .label = "e^0.2x"});
    axes[1].set_title("linear (same data)");
    axes[1].set_xlabel({.xlabel = "x"});
    axes[1].set_ylabel({.ylabel = "y"});
    axes[1].legend();
    axes[1].grid({.visible = true});

    fig.suptitle("semilogy vs linear");
    fig.save("../pics/semilogy_example.png");
    fig.tight_layout();
    plt.show();

    return 0;
}