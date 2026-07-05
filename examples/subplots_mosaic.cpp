#include "../include/Matplotlib.h"


#include <iostream>
#include <vector>
#include <random>


using matplotlibcpp::Vec;


int main() {

    matplotlibcpp::PyPlot plt;

    const int n = 100;    
    const int m = 50;
    Vec x(n), sinY(n), cosY(n), tanY(n);

    std::mt19937 rng(42); 

    std::normal_distribution<double> dist(0, 1);

    Vec x_dist(m), y_dist(m);
    for (int i = 0; i < m; ++i){
        x_dist[i] = dist(rng);
        y_dist[i] = dist(rng);
    }


    for (int i = 0; i < n; ++i) {
        x[i] = i * 2 * M_PI / (n - 1);
        sinY[i] = std::sin(x[i]);
        cosY[i] = std::cos(x[i]);
        tanY[i] = std::tan(x[i]);
    }    

    std::vector<std::vector<std::string>> mosaic = {
        {"A", "A", "B"},
        {"C", "D", "B"},
        {"C", "D", "E"},
    };

    Vec bar_x = {1, 2, 3};
    Vec bar_y = {4, 2, 5};


    auto [fig, axes] = plt.subplot_mosaic({.mosaic = mosaic, .figsize = {12, 8}});
    
    axes["A"].plot({.x = x, .y = sinY, .fmt = "b"});
    axes["A"].set_title("Sine — full width");
    axes["A"].grid({.visible = true});

    axes["B"].plot({.x = x, .y = cosY, .fmt = "r"});
    axes["B"].set_title("Cosine — tall");
    axes["B"].grid({.visible = true});

    axes["C"].plot({.x = x, .y = tanY, .fmt = "g"});
    axes["C"].set_title("Tangent");
    axes["C"].set_ylim({-5, 5});
    axes["C"].grid({.visible = true});

    axes["D"].scatter({.x = x_dist , .y = y_dist, .color = "purple"});
    axes["D"].set_title("Scatter");
    axes["D"].grid({.visible = true});

    axes["E"].bar({.x = bar_x, .height = bar_y, .color = "orange"});
    axes["E"].set_title("Bar");
    axes["E"].grid({.visible = true});

    fig.suptitle("subplot_mosaic example");
    fig.save("../pics/subplot_mosaic.png");
    fig.tight_layout();
    plt.show();


    return 0;
}