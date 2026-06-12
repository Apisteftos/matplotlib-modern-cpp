#include "../include/matplotlib.h"

#include <iostream>



int main() {


    matplotlibcpp::PyPlot plt;

    std::vector<long> figsize = {10, 10};

    auto [fig, axes] = plt.subplots(1, 2, figsize);

    plt.sca(axes[0]);
    axes[0].plot({1, 2, 3, 4, 5}, {1, 4, 9, 16, 25});
    axes[0].set_title("Line");
    axes[0].grid(true);


    plt.sca(axes[1]);
    axes[1].plot({1, 2, 3, 4, 5}, {1, 4, 9, 16, 25});
    axes[1].set_title("Bar");
    axes[1].grid(true);


    fig.suptitle("SCA Example");
    fig.save("../pics/sca_example.png");
    fig.tight_layout();
    
  
    plt.show();

    return 0;
}


