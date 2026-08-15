#include "../include/Matplotlib.h"

#include <iostream>
#include <vector>
#include <numeric>


using matplotlibcpp::Vec;
using matplotlibcpp::StrVec;

int main() {

    matplotlibcpp::PyPlot plt;

    Vec x(12); 
    std::iota(x.begin(), x.end(), 1.0); 

    Vec solar   = {2, 3, 5, 7, 9, 11, 12, 11, 8, 5, 3, 2};
    Vec wind    = {6, 7, 6, 5, 4,  3,  3,  4, 5, 6, 7, 7};
    Vec hydro   = {8, 7, 6, 5, 4,  3,  3,  4, 5, 6, 7, 8};
    Vec nuclear = {5, 5, 5, 5, 5,  5,  5,  5, 5, 5, 5, 5};

    std::vector<std::string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                       "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    
    auto [fig, axes] = plt.subplots({.nrows = 2, .ncols = 2, .figsize = {14, 10}});

    axes[0, 0].stackplot({
        .x = x, 
        .y = {solar, wind, hydro, nuclear},
                          .labels = StrVec{"Solar", "Wind", "Hydro", "Nuclear"},
                          .colors = StrVec{"gold", "steelblue", "mediumseagreen", "tomato"},
                          .alpha = 0.8});
    axes[0, 0].set_title("Energy Mix — baseline='zero'");
    axes[0, 0].set_xticks({.ticks = x});
    axes[0, 0].set_xticklabels({.labels = months, .rotation = 45.0});
    axes[0, 0].set_ylabel({.ylabel="GWh"});
    axes[0, 0].legend({.loc = "upper left"});
    axes[0, 0].grid({.visible = true, .alpha = 0.3});


    axes[0, 1].stackplot({
        .x = x, 
        .y = {solar, wind, hydro, nuclear},
                          .baseline = "sym",
                          .labels = StrVec{"Solar", "Wind", "Hydro", "Nuclear"},
                          .colors = StrVec{"gold", "steelblue", "mediumseagreen", "tomato"},
                          .alpha = 0.8});
    axes[0, 1].set_title("baseline='sym'");
    axes[0, 1].set_xticks({.ticks = x});
    axes[0, 1].set_xticklabels({.labels = months, .rotation = 45.0});
    axes[0, 1].set_ylabel({.ylabel="GWh"});
    axes[0, 1].legend({.loc = "upper left"});
    axes[0, 1].grid({.visible = true, .alpha = 0.3});

    axes[1, 0].stackplot({
        .x = x, 
        .y = {solar, wind, hydro, nuclear},
                          .baseline = "weighted_wiggle",
                          .labels = StrVec{"Solar", "Wind", "Hydro", "Nuclear"},
                          .colors = StrVec{"gold", "steelblue", "mediumseagreen", "tomato"},
                          .alpha = 0.8});
    axes[1, 0].set_title("baseline='weighted_wiggle' (streamgraph)");
    axes[1, 0].set_xticks({.ticks = x});
    axes[1, 0].set_xticklabels({.labels = months, .rotation = 45.0});
    axes[1, 0].legend({.loc = "upper left"});
    axes[1, 0].grid({.visible = true, .alpha = 0.3});

    axes[1, 1].stackplot({
        .x = x, 
        .y = {solar, wind, hydro, nuclear},
                          .baseline = "wiggle",
                          .labels = StrVec{"Solar", "Wind", "Hydro", "Nuclear"},
                          .colors = StrVec{"gold", "steelblue", "mediumseagreen", "tomato"},
                          .alpha = 0.8});
    axes[1, 1].set_title("baseline='wiggle'");
    axes[1, 1].set_xticks({.ticks = x});
    axes[1, 1].set_xticklabels({.labels = months, .rotation = 45.0});
    axes[1, 1].legend({.loc = "upper left"});
    axes[1, 1].grid({.visible = true, .alpha = 0.3});

    fig.suptitle({.t = "Stackplot — Energy Mix over 12 months", .fontsize = 14.0});
    fig.tight_layout();
    fig.savefig("../pics/stackplot_example.png");
    plt.show();

    return 0;
}