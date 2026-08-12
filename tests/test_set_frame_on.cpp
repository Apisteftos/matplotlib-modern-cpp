#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../include/Matplotlib.h"


TEST_CASE("set_frame_on: on") {
    matplotlibcpp::PyPlot plt;

    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    
    CHECK_NOTHROW(axes[0].set_frame_on({.b = true}));
}

TEST_CASE("set_frame_on: off") {
    matplotlibcpp::PyPlot plt;

    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    
    CHECK_NOTHROW(axes[0].set_frame_on({.b = false}));
}

// set_frame_on: has no default value

  