#include "../include/Matplotlib.h"

#include <iostream>
#include <vector>

using matplotlibcpp::Vec;

int main() {

    matplotlibcpp::PyPlot plt;

    const int n = 100;
    Vec x(n) , y(n);

    for (int i = 0; i < n; ++i) {
        x[i] = i * 2 * M_PI / (n - 1);
        y[i] = std::sin(x[i]);
    }

    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 3, .figsize = {15, 4}});

    axes[0].plot({.x = x, .y = y, .fmt = "b"});
    axes[0].set_title("box on (default)");
    axes[0].grid({.visible = true});

    axes[1].plot({.x = x, .y = y, .fmt = "r"});
    axes[1].set_frame_on({.b = false});
    axes[1].set_title("box off");
    axes[1].grid({.visible = true});

    plt.sca(axes[2]);
    axes[2].plot({.x = x, .y = y, .fmt = "g"});
    plt.box({.on = false});
    axes[2].set_title("plt.box(False)");
    axes[2].grid({.visible = true});

    fig.suptitle("box example");
    fig.tight_layout();
    plt.show();

    return 0;
}

