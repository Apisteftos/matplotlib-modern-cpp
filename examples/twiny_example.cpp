#include "../include/Matplotlib.h"

#include <iostream>
#include <math.h>
#include <vector>



int main() {
    
    matplotlibcpp::PyPlot plt;

    const int x = 100;
    std::vector<double> time_sec(x), time_min(x), y(x); 
    for (int i = 0; i < x; ++i) {
        time_sec[i] = i * 100.0  / (x - 1);
        time_min[i] = time_sec[i] / 60;
        y[i] = std::sin(time_sec[i] / 10) ;
    }

    auto [fig, axes] = plt.subplots({.figsize = {10, 5}});
    auto& ax1 =   axes[0];


    ax1.plot({.x =time_sec, .y = y, .fmt = "b"});
    ax1.set_xlabel({.xlabel = "Time (seconds)", .color = "b"});
    ax1.tick_params({.axis="x", .labelcolor = "b"});
  

    auto ax2 = ax1.twiny();
    auto [left, right] = ax1.get_xlim();
    ax2.set_xlim({.left = left / 60, .right = right / 60});
    ax2.set_xlabel({.xlabel = "Time (minutes)", .color = "r"});
    ax2.tick_params({.axis="x", .labelcolor = "r"});

    ax1.set_ylabel({.ylabel = "Signal"});
    fig.suptitle("twiny example — two x-axes");
    fig.tight_layout(); 
    fig.save("../pics/twiny_example.png");
    plt.show();



    return 0;
}