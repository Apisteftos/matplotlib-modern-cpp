#include "../include/Matplotlib.h"

#include <iostream>
#include <vector>
#include <random>


using matplotlibcpp::Vec;

int main() {

    matplotlibcpp::PyPlot plt;

    std::mt19937 rng(42);

    std::normal_distribution<double> normal(0.0, 1.0);
    Vec x(100), y(100);
    for (int i = 0; i < 100; ++i) {
        x[i] = normal(rng);
        y[i] = normal(rng);
    }

    
    std::uniform_int_distribution<int> randint(20, 299);

    std::vector<int> sizes(100);
    for (int i = 0; i < 100; ++i)
        sizes[i] = randint(rng);

    printf("sizes[0]=%d\n", sizes[0]);

    Vec sizes_d(100);
    for (int i = 0; i < 100; ++i)
        sizes_d[i] = static_cast<double>(sizes[i]);

    printf("sizes_d[0]=%f sizes_d[1]=%f\n", sizes_d[0], sizes_d[1]);


    std::uniform_real_distribution<double> rand(0.0, 1.0);
    Vec colors(100);
    for (int i = 0; i < 100; ++i)
        colors[i] = rand(rng);


    auto [fig, axes] = plt.subplots({.nrows = 2, .ncols = 2, .figsize = {12, 8}});

    axes[0, 0].scatter({.x = x, .y = y, .color = "blue"});
    axes[0, 0].set_title("Basic scatter");
    axes[0, 0].grid({.visible = true});

    axes[0, 1].scatter({.x = x, .y = y, .s = sizes_d, .color = "red", .alpha = 0.5});
    axes[0, 1].set_title("Variable size");
    axes[0, 1].grid({.visible = true});

    axes[1, 0].scatter({.x = x, .y = y, .c = colors, .cmap = "viridis", .alpha = 0.7});
    axes[1, 0].set_title("Colormap");
    axes[1, 0].grid({.visible = true});


    axes[1, 1].scatter({.x = x, .y = y, .s = sizes_d, .c = colors, .cmap = "plasma",
             .linewidths = 0.5, .edgecolors = "black", .alpha = 0.7});
    axes[1, 1].set_title("Size + color + colormap");
    axes[1, 1].grid({.visible = true});


    fig.suptitle("scatter examples");
    fig.save("../pics/scatter_example.png");
    fig.tight_layout(); 
    plt.show();


    return 0;
}; 