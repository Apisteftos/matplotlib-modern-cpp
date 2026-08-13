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
    // 1 — axes.Axes.set_ylabel 
    // ============================================================

    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 2, .figsize = {12, 4}});

    axes[0].plot({.x = x, .y = y, .fmt = "b"});
    axes[0].set_ylabel({
                        .ylabel = "Amplitude",
                        .labelpad = 10.0,
                        .loc = "center",
                        .color = "blue",
                        .fontsize = 14.0,
                        .fontweight = "bold"
                        });
    axes[0].set_title("axes.set_ylabel()");
    axes[0].grid({.visible = true});

    axes[1].plot({.x = x, .y = y, .fmt = "r"});
    axes[1].set_ylabel({
                        .ylabel = "Signal (mV)",
                        .loc = "top",
                        .color = "red",
                        .fontstyle = "italic"
                        });
    axes[1].set_title("axes.set_ylabel() — loc='top'");
    axes[1].grid({.visible = true});

    fig.suptitle("Axes.set_ylabel — OOP style");
    fig.tight_layout();



    // ============================================================
    // 2 - pyplot.ylabel 
    // ============================================================   
    
    auto [fig2, _] = plt.subplots({.nrows = 1, .ncols = 2, .figsize = {12, 4}});
    
    plt.subplot(1, 2, 1);
    plt.plot({.x = x, .y = y, .fmt = "g"});
    plt.ylabel({
                .ylabel = "Amplitude",
                .labelpad = 10.0,
                .loc = "center",
                .color = "green",
                .fontsize = 14.0,
                .fontweight = "bold"
                });
    plt.title("plt.ylabel()");
    plt.grid({.visible = true});

    plt.subplot(1, 2, 2);
    plt.plot({.x = x, .y = y, .fmt = "m"});
    plt.ylabel({
                .ylabel = "Signal (mV)",
                .labelpad = 10.0,
                .loc = "top",
                .color = "purple",
                .fontstyle = "italic"
                });
    plt.title("plt.ylabel() — loc='top'");
    plt.grid({.visible = true});

    plt.suptitle({.t="pyplot.ylabel — state-machine style"});
    plt.tight_layout();
    plt.show();

    return 0;
}