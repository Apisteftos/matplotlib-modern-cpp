#include "../include/Matplotlib.h"
#include "Configs.h"


#include <iostream>
#include <vector>
#include <numeric>

using matplotlibcpp::Vec;

int main() {

    matplotlibcpp::PyPlot plt;

    
    std::vector<std::string> categories = {"Jan", "Feb", "Mar", "Apr", "May", "Jun"};
    Vec val1        = {4, 7, 3, 8, 5, 9};
    Vec val2        = {3, 5, 6, 4, 7, 6};
    Vec val3        = {2, 4, 5, 3, 6, 4};


    const double width = 0.25;
  
    
    Vec x(categories.size());
    std::iota(x.begin(), x.end(), 0);

    auto [fig, axes] = plt.subplots({.nrows = 2, .ncols = 2, .figsize = {12, 8}});

    axes[0, 0].bar({.x = x, .height = val1, .color = "blue", .alpha = 0.7});
    axes[0, 0].set_title("Basic bar");
    axes[0, 0].set_xticks({.ticks = x});
    axes[0, 0].set_xticklabels({.labels = categories});
    axes[0, 0].grid({.visible = true, .axis = "y"});


    axes[0, 1].bar({.x = x - width, .height = val1, .width = width, .color = "blue", .label = "2022", .alpha = 0.7,});
    axes[0, 1].bar({.x = x, .height = val2, .width = width, .color = "red", .label = "2023", .alpha = 0.7});
    axes[0, 1].bar({.x = x + width, .height = val3, .width = width, .color = "green", .label = "2024", .alpha = 0.7});
    axes[0, 1].set_title("Grouped bar");
    axes[0, 1].set_xticks({.ticks = x});
    axes[0, 1].set_xticklabels({.labels = categories});
    axes[0, 1].legend();
    axes[0, 1].grid({.visible = true, .axis = "y"});


    axes[1, 0].bar({.x = x, .height = val1, .color = "blue", .label = "2022", .alpha = 0.7});
    axes[1, 0].bar({.x = x, .height = val2, .bottom = val1, .color = "red", .label = "2023", .alpha = 0.7});
    axes[1, 0].bar({.x = x, .height = val3, .bottom = val1 + val2, .color = "green", .label = "2024", .alpha = 0.7, });
    axes[1, 0].set_title("Stacked bar");
    axes[1, 0].set_xticks({.ticks = x});
    axes[1, 0].set_xticklabels({.labels = categories});
    axes[1, 0].legend();
    axes[1, 0].grid({.visible = true, .axis = "y"});


    axes[1, 1].barh({.y = x, .width = val1, .color = "purple", .alpha = 0.7});
    axes[1, 1].set_title("Horizontal bar");
    axes[1, 1].set_yticks({.ticks = x});
    axes[1, 1].set_yticklabels({.labels = categories});
    axes[1, 1].grid({.visible = true, .axis = "x"});



    fig.suptitle("bar examples");
    fig.save("../pics/bar_example.png");
    fig.tight_layout();
    plt.show();

    return 0;
}
  