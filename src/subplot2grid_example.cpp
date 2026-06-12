#include "../include/matplotlib.h"


#include <iostream>
#include <vector>
#include <cmath>


using matplotlibcpp::Figure;

int main() {

    matplotlibcpp::PyPlot plt;

    const int n = 100;    
    std::vector<double> x(n), sinY(n), cosY(n), tanY(n);

    for (int i = 0; i < n; ++i) {
        x[i] = i * 2 * M_PI / (n - 1);
        sinY[i] = std::sin(x[i]);
        cosY[i] = std::cos(x[i]);
        tanY[i] = std::tan(x[i]);
    }   

    std::vector<double> sinCos(n);
    for (int i = 0; i < n; ++i){
        sinCos[i] = sinY[i] * cosY[i];
    }

    std::vector<double> sinY2(n);
    for (int i = 0; i < n; ++i) {
        sinY2[i] = std::sin(x[i]) * std::sin(x[i]);
    }
        

    Figure fig = plt.figure({.figsize = {10, 8}});
    auto ax1 = plt.subplot2grid({.shape = {3, 3}, .loc = {0, 0}, .colspan = 3});
    ax1.plot(x, sinY, "b");
    ax1.set_title("Sine - full width");

  
    auto ax2 = plt.subplot2grid({.shape = {3, 3}, .loc = {1, 0}, .colspan = 2});
    ax2.plot(x, cosY, "r");
    ax2.set_title("Cosine - 2 cols");


    auto ax3 = plt.subplot2grid({.shape = {3, 3}, .loc = {1, 2}, .rowspan = 2});
    ax3.plot(x, tanY, "g");
    ax3.set_title("Tan - 2 rows");
    ax3.set_ylim(-5, 5);

    
    auto ax4 = plt.subplot2grid({.shape = {3, 3}, .loc = {2, 0}});
    ax4.plot(x, sinCos, "m");
    ax4.set_title("sin*cos");


    auto ax5 = plt.subplot2grid({.shape = {3, 3}, .loc = {2, 1}});
    ax5.plot(x, sinY2, "orange");
    ax5.set_title("sin²");

    fig.suptitle("subplot2grid example");
    fig.save("../pics/subplot2grid_example.png");
    fig.tight_layout();

    plt.show();




    return 0;
}


