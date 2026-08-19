#include "../include/Matplotlib.h"
#include "RcConfigs.h"

#include <iostream>
#include <vector>
#include <cmath>

using matplotlibcpp::Vec;
using matplotlibcpp::GridRcConfig;
using matplotlibcpp::FigureRcConfig;
using matplotlibcpp::AxesRcConfig;
using matplotlibcpp::LinesRcConfig;
using matplotlibcpp::FontRcConfig;
using matplotlibcpp::TicksRcConfig;

int main() {

    matplotlibcpp::PyPlot plt;

    const int n = 100;
    Vec x(n), y1(n), y2(n), y3(n);
    for (int i = 0; i < n; ++i) {
        x[i] = i * 2 * M_PI / (n - 1);
        y1[i] = std::sin(x[i]);
        y2[i] = std::cos(x[i]);
        y3[i] = std::tan(x[i]);
    }; 

    plt.rc(GridRcConfig{.group = "grid",       
        .color = "#b0b0b0", 
        .linewidth = 0.8});
    plt.rc(GridRcConfig{.group = "grid.major", 
        .color = "blue",    
        .linewidth = 1.2});
    plt.rc(GridRcConfig{.group = "grid.minor", 
        .color = "red",     
        .linewidth = 0.6});

    plt.rc({.group = "legend", .kwargs = {
        {"loc", "best"},
        {"frameon", true},
        {"framealpha", 0.2},
        {"facecolor", "cyan"},
        {"edgecolor", "0.4"},
        {"fancybox", true}
    }});


    plt.rc(FigureRcConfig{.group = "figure", .figsize = {10.0, 5.0}});
    plt.rc(FigureRcConfig{.group = "figure", .titlesize = "medium"});
    plt.rc(FigureRcConfig{.group = "figure", .facecolor = "#f0f0f0"});
    plt.rc(FigureRcConfig{.group = "figure.subplot", .wspace = 0.5});
    plt.rc(FigureRcConfig{.group = "figure.subplot", .left = 0.125});
    plt.rc(FigureRcConfig{.group = "figure.subplot", .right = 0.9});
    plt.rc(FigureRcConfig{.group = "figure.subplot", .top = 0.88});
    plt.rc(FigureRcConfig{.group = "figure.subplot", .bottom = 0.11});


    plt.rc(AxesRcConfig{.group = "axes", .facecolor = "white"});
    plt.rc(AxesRcConfig{.group = "axes.spines", .right = false});
    plt.rc(AxesRcConfig{.group = "axes.spines", .top = false});
    plt.rc(AxesRcConfig{.group = "axes.spines", .left = false});
    plt.rc(AxesRcConfig{.group = "axes.spines", .bottom = false});
    plt.rc(AxesRcConfig{.group = "axes", .linewidth = 0.8});


    plt.rc(LinesRcConfig{.group = "lines", .linewidth = 2.0});
    plt.rc(LinesRcConfig{.group = "lines", .markersize = 8.0});
    plt.rc(LinesRcConfig{.group = "lines", .markeredgewidth = 1.0});
    plt.rc(LinesRcConfig{.group = "lines", .markerfacecolor = "black"});
    plt.rc(LinesRcConfig{.group = "lines", .markeredgecolor = "black"});


    plt.rc(FontRcConfig{.group = "font", .family = "serif"});
    plt.rc(FontRcConfig{.group = "font", .stretch = "normal"});
    plt.rc(FontRcConfig{.group = "font", .style = "normal"});
    plt.rc(FontRcConfig{.group = "font", .variant = "normal"});
    plt.rc(FontRcConfig{.group = "font", .weight = "bold"});


    plt.rc(TicksRcConfig{.group = "xtick", .labelsize = "medium"});
    plt.rc(TicksRcConfig{.group = "ytick", .labelsize = 10.0});
    plt.rc(TicksRcConfig{.group = "ytick", .direction = "in"});
    plt.rc(TicksRcConfig{.group = "ytick.minor", .ndivs = 5});

    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 2, .figsize = {10, 5}});
    axes[0].plot({.x = x, .y = y1, .fmt = "b", .label = "sin(x)"});
    axes[0].plot({.x = x, .y = y2, .fmt = "r", .label = "cos(x)"});
    axes[0].set_title("Sine and Cosine");
    axes[0].set_xlabel({.xlabel = "X"});
    axes[0].set_ylabel({.ylabel = "Y"});
    axes[0].legend();


    axes[1].plot({.x = x, .y = y3, .fmt = "g", .label = "tan(x)"});
    axes[1].set_ylim({.bottom =-5, .top = 5});
    axes[1].set_title("Tangent");
    axes[1].set_xlabel({.xlabel = "X"});
    axes[1].set_ylabel({.ylabel = "Y"});
    axes[1].legend();

    fig.tight_layout();
    fig.suptitle({.t = "plt.rc example — global styles"});
    fig.savefig("../pics/rc_example.png");
    plt.show();

    return 0;
}



