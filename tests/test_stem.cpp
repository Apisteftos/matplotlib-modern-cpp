#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../include/Matplotlib.h"
#include <vector>

using matplotlibcpp::Vec;

TEST_CASE("stem: basic call with explicit locs and heads") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    Vec locs  = {0, 1, 2, 3, 4};
    Vec heads = {3, 7, 2, 9, 5};

    CHECK_NOTHROW(axes[0, 0].stem({.locs = locs, .heads = heads}));
}

TEST_CASE("stem: locs omitted, auto-generated as 0..N-1") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    Vec heads = {3, 7, 2, 9, 5};

    CHECK_NOTHROW(axes[0, 0].stem({.heads = heads}));
}

TEST_CASE("stem: custom linefmt, markerfmt, basefmt") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    Vec locs  = {0, 1, 2, 3};
    Vec heads = {1, 4, 2, 6};

    CHECK_NOTHROW(axes[0, 0].stem({
        .locs = locs,
        .heads = heads,
        .linefmt = "g-",
        .markerfmt = "gD",
        .basefmt = "k-"
    }));
}

TEST_CASE("stem: custom bottom baseline") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    Vec locs  = {0, 1, 2};
    Vec heads = {-1, 2, -3};

    CHECK_NOTHROW(axes[0, 0].stem({.locs = locs, .heads = heads, .bottom = -2.0}));
}

TEST_CASE("stem: horizontal orientation") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    Vec locs  = {0, 1, 2};
    Vec heads = {1, 2, 3};

    CHECK_NOTHROW(axes[0, 0].stem({.locs = locs, .heads = heads, .orientation = "horizontal"}));
}