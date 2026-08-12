#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../include/Matplotlib.h"


TEST_CASE("box: on") {
    matplotlibcpp::PyPlot plt;

    CHECK_NOTHROW(plt.box({.on = true}));
}


TEST_CASE("box: off") {
    matplotlibcpp::PyPlot plt;

    CHECK_NOTHROW(plt.box({.on = false}));
}

TEST_CASE("box: default") {
    matplotlibcpp::PyPlot plt;
    
    CHECK_NOTHROW(plt.box({}));
}