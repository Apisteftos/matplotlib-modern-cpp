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
        x[i] = std::pow(10.0, 0.0 + i * (4.0 - 0.0) / (n - 1));
    }

    std::vector<double> y1(x.size()), y2(x.size()), y3(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        y1[i] = std::log(x[i]);    
        y2[i] = std::sqrt(x[i]);  
        y3[i] = x[i] * 0.01;       
    }

    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 2, .figsize = {12, 5}});
    
    axes[0].semilogx({.x = x, .y = y1, .fmt = "b", .label = "log(x)"});
    axes[0].semilogx({.x = x, .y = y2, .fmt = "r", .label = "√x"});
    axes[0].semilogx({.x = x, .y = y3, .fmt = "g", .label = "x * 0.01"});
    axes[0].set_title("semilogx");
    axes[0].set_xlabel({.xlabel = "x (log scale)"});
    axes[0].set_ylabel({.ylabel = "y (linear scale)"});
    axes[0].legend();
    axes[0].grid({.visible = true, .which = "both"});


    axes[1].plot({.x = x, .y = y1, .fmt = "b", .label = "log(x)"});
    axes[1].plot({.x = x, .y = y2, .fmt = "r", .label = "√x"});
    axes[1].plot({.x = x, .y = y3, .fmt = "g", .label = "x * 0.01"});
    axes[1].set_title("linear (same data)");
    axes[1].set_xlabel({.xlabel = "x"});
    axes[1].set_ylabel({.ylabel = "y"});
    axes[1].legend();
    axes[1].grid({.visible = true});

    fig.suptitle("semilogx vs linear");
    fig.save("../pics/semilogx_example.png");
    fig.tight_layout();
    plt.show();

    return 0;
}