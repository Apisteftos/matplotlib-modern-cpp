#include "../include/Matplotlib.h"


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


int main() {

    matplotlibcpp::PyPlot plt;

    const int n = 100;
    std::vector<double> y1(n);

    std::vector<double> x(n);
    for (int i = 0; i < n; ++i) {
        x[i] = std::pow(10.0, 0.0 + i * (4.0 - 0.0) / (n - 1));
    }

    std::transform(x.begin(), x.end(), y1.begin(),
        [](double v) { return std::pow(v, 2.0); });

    std::vector<double> y2(n);
    std::transform(x.begin(), x.end(), y2.begin(),
        [](double v) { return std::sqrt(v); });

    std::vector<double> y3 = x;

    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 2, .figsize = {12, 5}});


    axes[0].loglog({.x = x, .y = y1, .fmt = "b", .label = "x²"});
    axes[0].loglog({.x = x, .y = y2, .fmt = "r", .label = "√x"});
    axes[0].loglog({.x = x, .y = y3, .fmt = "g", .label = "x"});
    axes[0].set_title("loglog");
    axes[0].set_xlabel({.xlabel = "x (log scale)"});
    axes[0].set_ylabel({.ylabel = "y (log scale)"});
    axes[0].legend();
    axes[0].grid({.visible = true, .which = "both"});

    axes[1].plot({.x = x, .y = y1, .fmt = "b", .label = "x²"});
    axes[1].plot({.x = x, .y = y2, .fmt = "r", .label = "√x"});
    axes[1].plot({.x = x, .y = y3, .fmt = "g", .label = "x"});
    axes[1].set_title("linear (same data)");
    axes[1].set_xlabel({.xlabel = "x"});
    axes[1].set_ylabel({.ylabel = "y"});
    axes[1].legend();
    axes[1].grid({.visible = true});


    fig.suptitle("loglog vs linear");
    fig.save("../pics/loglog_example.png");
    fig.tight_layout();
    plt.show();



    return 0;
}


