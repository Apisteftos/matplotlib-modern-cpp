#include "../include/Matplotlib.h"

#include <iostream>
#include <numeric>
#include <vector>



int main() {

    matplotlibcpp::PyPlot plt;

    std::vector<double> x(7);
    std::iota(x.begin(), x.end(), 1);
    std::vector<double> y = {2.3, 3.1, 4.5, 3.8, 5.2, 4.9, 6.1};
    std::vector<double> y_err = {0.3, 0.5, 0.4, 0.6, 0.3, 0.5, 0.4};
    std::vector<std::vector<double>> y_err_asym = {
        {0.2, 0.4, 0.3, 0.5, 0.2, 0.4, 0.3}, 
        {0.4, 0.6, 0.5, 0.7, 0.4, 0.6, 0.5}
    };

    std::vector<double> x_err = {0.1, 0.2, 0.1, 0.3, 0.1, 0.2, 0.1};

    auto [fig, axes] = plt.subplots({.nrows = 2, .ncols = 2, .figsize = {12, 8}});

    axes[0, 0].errorbar({.x = x, .y = y, .yerr = y_err, .fmt = "bo-", .capsize = 5, .color = "b"});
    axes[0, 0].set_title("Basic errorbar");
    axes[0, 0].grid({.visible = true});

    axes[0, 1].errorbar({.x = x, .y = y, .yerr = y_err_asym, .fmt = "rs-", .capsize = 5, .color = "r"});
    axes[0, 1].set_title("Asymmetric errors");
    axes[0, 1].grid({.visible = true});


    axes[1, 0].errorbar({.x = x, .y = y, .yerr = y_err,.xerr = x_err, .fmt = "g^-", .ecolor = "red", .elinewidth = 2, 
                         .capsize = 5, .capthick = 2});
    axes[1, 0].set_title("X and Y errors");
    axes[1, 0].grid({.visible = true});


    axes[1, 1].errorbar({.x = x, .y = y, .yerr = y_err, .fmt = "none",
                         .ecolor = "purple", .elinewidth = 2, .capsize = 8, .capthick = 2});                   
    axes[1, 1].plot({.x = x, .y = y, .fmt = "o", .color = "purple"});
    axes[1, 1].set_title("Error bars only");
    axes[1, 1].grid({.visible = true});

    fig.suptitle("Error Bar Plot");
    fig.save("../pics/errorbar_example.png");
    fig.tight_layout();
    plt.show();

    return 0;
}
