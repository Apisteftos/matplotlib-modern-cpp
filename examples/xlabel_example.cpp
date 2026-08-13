#include "../include/Matplotlib.h"

#include <iostream>
#include <vector>

int main() {

    matplotlibcpp::PyPlot plt;

    const int n = 100;
    std::vector<double> x(n), y(n);

    for (int i = 0; i < n; ++i) {
        x[i] = i * 2 * M_PI / (n - 1);
        y[i] = std::sin(x[i]);
    }

    // ============================================================
    // 1 — axes.Axes.set_xlabel 
    // ============================================================

    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 2, .figsize = {12, 4}});

    axes[0].plot({.x = x, .y = y, .fmt = "b"});
    axes[0].set_xlabel({
                                .xlabel = "Time (seconds)",
                                .labelpad = 10.0,
                                .loc = "center",
                                .color = "blue",
                                .fontsize = 14.0,
                                .fontweight = "bold"
                            });
    axes[0].set_title("axes.set_xlabel()");
    axes[0].grid({.visible = true});

    axes[1].plot({.x = x, .y = y, .fmt = "r"});
    axes[1].set_xlabel({
                        .xlabel = "Amplitude",
                        .loc = "right",
                        .color = "red",
                        .fontstyle = "italic"
                        });
    axes[1].set_title("axes.set_xlabel() — loc='right'");
    axes[1].grid({.visible = true});

    fig.suptitle("Axes.set_xlabel — OOP style");
    fig.tight_layout();
  


    // ============================================================
    // 2 - pyplot.xlabel 
    // ============================================================   
    
    auto [fig2, _] = plt.subplots({.nrows = 1, .ncols = 2, .figsize = {12, 4}});
    
    plt.subplot(1, 2, 1);
    plt.plot({.x = x, .y = y, .fmt = "g"});
    plt.xlabel({
                .xlabel = "Time (seconds)",
                .labelpad = 10.0,
                .loc = "center",
                .color = "green",
                .fontsize = 14.0,
                .fontweight = "bold"
                });
    plt.title("plt.xlabel()");
    plt.grid({.visible = true});

    plt.subplot(1, 2, 2);
    plt.plot({.x = x, .y = y, .fmt = "m"});
    plt.xlabel({
                .xlabel = "Amplitude",
                .labelpad = 10.0,
                .loc = "right",
                .color = "purple",
                .fontstyle = "italic"
                });
    plt.title("plt.xlabel() — loc='right'");
    plt.grid({.visible = true});

    plt.suptitle({.t="pyplot.xlabel — state-machine style"});
    plt.tight_layout();
    plt.show();

    return 0;
}