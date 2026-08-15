#include "../include/Matplotlib.h"

#include <iostream>
#include <vector>

using matplotlibcpp::Vec;

int main() {

    matplotlibcpp::PyPlot plt;

    const int n = 20;
    Vec x(n), y1(n), y2(n);

    for (int i = 0; i < n; ++i) {
        x[i] = i * 2 * M_PI / (n - 1);
        y1[i] = std::sin(x[i]);
        y2[i] = std::cos(x[i]);
    }

    auto [fig, axes] = plt.subplots({.nrows = 2, .ncols = 2, .figsize = {12, 8}});

    axes[0, 0].stem({.locs = x, .heads = y1});
    axes[0, 0].set_title("Basic stem");
    axes[0, 0].grid({.visible = true});

    axes[0, 1].stem({.locs = x, .heads = y1,
                     .linefmt = "b-",
                     .markerfmt = "ro",
                     .basefmt = "k-"});
    axes[0, 1].set_title("Custom colors");
    axes[0, 1].grid({.visible = true});

    axes[1, 0].stem({.locs = x, .heads = y2,
                     .linefmt = "g-",
                     .markerfmt = "g^",
                     .basefmt = "k-",
                     .bottom = -0.5});
    axes[1, 0].set_title("Cosine with custom baseline");
    axes[1, 0].grid({.visible = true});

    axes[1, 1].stem({.locs = y1, .heads = x,
                     .linefmt = "m-",
                     .markerfmt = "ms", 
                     .basefmt = "k-",
                     .orientation = "horizontal"});
    axes[1, 1].set_title("Horizontal stem");
    axes[1, 1].grid({.visible = true});
    
    fig.suptitle({.t = "Stem examples"});
    fig.savefig("../pics/stem_example.png");
    fig.tight_layout();
    plt.show();

    return 0;
}