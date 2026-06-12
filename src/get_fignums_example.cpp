#include "../include/matplotlib.h"  
#include "PyPlot.h"


#include <iostream>                 
#include <vector>
#include <print>

using matplotlibcpp::Figure;

int main() {

    matplotlibcpp::PyPlot plt;

    Figure fig1 = plt.figure({.num = 1, .label = "sine_plot"});
    plt.plot({1, 2, 3}, {1, 4, 9});

    Figure fig2 = plt.figure({.num = 2, .label = "cosine_plot"});
    plt.plot({1, 2, 3}, {1, 2, 3});

    auto fig3 = plt.figure({.num = 3, .label = "bar_plot"});
    plt.plot({1, 2, 3}, {5, 3, 7});


    std::vector<int> nums = plt.get_fignums();
    std::vector<std::string> labels = plt.get_figlabels();

    for (int i = 0; i < nums.size(); ++i) {
        std::println("Num: {}, Label: {}", nums[i], labels[i]);
    }

    return 0;
}