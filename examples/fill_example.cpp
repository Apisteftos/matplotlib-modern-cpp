#include "../include/Matplotlib.h"

#include <iostream>
#include <vector>

using matplotlibcpp::Vec;

int main() {

    matplotlibcpp::PyPlot plt;
    

    const int n = 100;
    Vec x(n), y1(n), y2(n);

    for (int i = 0; i < n; ++i) {
        x[i] = i * 2 * M_PI / (n - 1);
        y1[i] = std::sin(x[i]);
        y2[i] = std::cos(x[i]);

    }

    auto [fig, axes] = plt.subplots({.nrows = 2, .ncols = 2, .figsize = {12, 8}});


    axes[0, 0].plot({.x = x, .y = y1, .fmt = "b", .label = "sin(x)"});
    axes[0, 0].plot({.x = x, .y = y2, .fmt = "r", .label = "cos(x)"}); 
    axes[0, 0].fill_between({.x = x, .y1 = y1, .y2 = y2, .color = "purple", .alpha = 0.3});
    axes[0, 0].set_title("fill_between two curves");
    axes[0, 0].legend(); 
    axes[0, 0].grid({.visible = true});


    axes[0, 1].plot({.x = x, .y = y1, .fmt = "b"});
    axes[0, 1].fill_between({.x = x, .y1 = y1, .y2 = 0.0, .color = "blue", .alpha = 0.3});
    axes[0, 1].set_title("fill_between curve and zero");
    axes[0, 1].grid({.visible = true});

    axes[1, 0].plot({.x = x, .y = y1, .fmt = "b", .label = "sin(x)"});
    axes[1, 0].plot({.x = x, .y = y2, .fmt = "r", .label = "cos(x)"}); 
    axes[1, 0].fill_between({.x = x, .y1 = y1, .y2 = y2, .where = y1 > y2, .color = "green", .label = "sin > cos", .alpha = 0.3});
    axes[1, 0].fill_between({.x = x, .y1 = y1, .y2 = y2, .where = y1 < y2, .color = "red", .label = "cos < sin", .alpha = 0.3});
    axes[1, 0].set_title("fill_between with condition");
    axes[1, 0].legend();
    axes[1, 0].grid({.visible = true});

    axes[1, 1].fill({.x = x, .y = y1, .color = "orange", .alpha = 0.3});
    axes[1, 1].set_title("fill — closed polygon");
    axes[1, 1].grid({.visible = true});

    fig.suptitle("fill examples");
    fig.save("../pics/fill_example.png");
    fig.tight_layout();
    plt.show();


    return 0;
}