#include "../include/matplotlib.h"

#include <iostream>
#include <math.h>
#include <vector>



int main() {
    
    matplotlibcpp::PyPlot plt;

    const int n = 100;
    std::vector<double> x(n), sinY(n), expY(n);

    for (int i = 0; i < n; ++i) {
        x[i] = i * 10.0  / (n - 1);
        sinY[i] = std::sin(x[i]);
        expY[i] = std::exp(x[i]);

    }


    auto [fig, axes] = plt.subplots({.figsize = {10, 5}});
    auto& ax1 =   axes[0];
    

    ax1.plot({x, sinY, "b"});
    ax1.set_xlabel({.xlabel = "X"});
    ax1.set_ylabel({.ylabel = "Sine", .color = "b"});
    ax1.tick_params({.axis="y", .labelcolor = "b"});
  

    auto ax2 = ax1.twinx();
    ax2.plot({x, expY, "r"});
    ax2.set_ylabel({.ylabel = "Exponential", .color = "r"});
    ax2.tick_params({.axis="y", .labelcolor = "r"});  


    fig.suptitle("twinx example — two y-axes");
    fig.save("../pics/twinx_example.png");

    
    plt.tight_layout();
    plt.show();

    return 0;
}