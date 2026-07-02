#include "../include/Matplotlib.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <numeric>

int main() {

    matplotlibcpp::PyPlot plt;

    std::vector<double> x(10);
    std::iota(x.begin(), x.end(), 0.0);
    std::vector<double> y = {2, 3, 5, 4, 6, 5, 7, 8, 6, 9};

    auto [fig, axes] = plt.subplots({.nrows = 2, .ncols = 2, .figsize = {10, 8}});


    axes[0, 0].step({.x = x, .y = y, .where = "pre", .color = "b"});
    axes[0, 0].plot({.x = x, .y = y, .fmt = "o", .color = "gray", .alpha = 0.3});
    axes[0, 0].set_title("where='pre' (default)");
    axes[0, 0].grid({.visible = true});

    axes[0, 1].step({.x = x, .y = y, .where = "post", .color = "r"});
    axes[0, 1].plot({.x = x, .y = y, .fmt = "o", .color = "gray", .alpha = 0.3});
    axes[0, 1].set_title("where='post'");
    axes[0, 1].grid({.visible = true});


    axes[1, 0].step({.x = x, .y = y, .where = "mid", .color = "g"});
    axes[1, 0].plot({.x = x, .y = y, .fmt = "o", .color = "gray", .alpha = 0.3});
    axes[1, 0].set_title("where='mid'");
    axes[1, 0].grid({.visible = true});


    axes[1, 1].step({.x = x, .y = y, .where = "pre", .color = "purple", .linewidth = 2,
                     .linestyle = "--", .marker = "o",  .markersize = 6 });
    axes[1, 1].set_title("Styled step plot");
    axes[1, 1].grid({.visible = true});

    fig.suptitle("step() examples");
    fig.save("../pics/step_example.png");
    fig.tight_layout();
    plt.show();

    return 0;
   
}

