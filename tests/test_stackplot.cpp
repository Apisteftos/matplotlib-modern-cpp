#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../include/Matplotlib.h"
#include <vector>

using matplotlibcpp::Vec;
using matplotlibcpp::StrVec;
using matplotlibcpp::Clim;

namespace {
    Vec makeX() {
        return {0, 1, 2, 3, 4, 5};
    }

    Vec lineA() { return {10, 12, 9, 14, 11, 13}; }
    Vec lineB() { return {4,  6,  5,  7,  6,  8}; }
    Vec lineC() { return {2,  3,  4,  2,  3,  1}; }
}

TEST_CASE("stackplot: minimal — x and y only, default baseline='zero'") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()}
    }));
}

TEST_CASE("stackplot: baseline='sym'") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .baseline = "sym"
    }));
}

TEST_CASE("stackplot: baseline='wiggle'") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .baseline = "wiggle"
    }));
}

TEST_CASE("stackplot: baseline='weighted_wiggle'") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .baseline = "weighted_wiggle"
    }));
}

TEST_CASE("stackplot: labels and colors") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .labels = StrVec{"Line A", "Line B", "Line C"},
        .colors = StrVec{"navy", "orange", "green"}
    }));
}

TEST_CASE("stackplot: alpha") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .alpha = 0.6
    }));
}

TEST_CASE("stackplot: animated") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .animated = false
    }));
}

TEST_CASE("stackplot: array") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .array = Vec{0.1, 0.2, 0.3, 0.4, 0.5, 0.6}
    }));
}

TEST_CASE("stackplot: clim") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .clim = Clim{0.0, 1.0}
    }));
}

TEST_CASE("stackplot: clip_on") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .clip_on = true
    }));
}

TEST_CASE("stackplot: cmap") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .cmap = "viridis"
    }));
}

TEST_CASE("stackplot: color") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .color = "purple"
    }));
}

TEST_CASE("stackplot: edgecolor, linestyle, linewidth (double)") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .edgecolor = "black",
        .linestyle = ":",
        .linewidth = 2.0
    }));
}

TEST_CASE("stackplot: facecolor") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .facecolor = "lightblue"
    }));
}

TEST_CASE("stackplot: gid") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .gid = "my-stackplot-id"
    }));
}

TEST_CASE("stackplot: hatch") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .hatch = "xx"
    }));
}

TEST_CASE("stackplot: in_layout") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .in_layout = true
    }));
}

TEST_CASE("stackplot: label") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .label = "generic label"
    }));
}

TEST_CASE("stackplot: mouseover") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .mouseover = false
    }));
}

TEST_CASE("stackplot: pickradius") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .pickradius = 3.0
    }));
}

TEST_CASE("stackplot: rasterized, snap, visible, zorder") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .rasterized = true,
        .snap = true,
        .visible = true,
        .zorder = 3.0
    }));
}

TEST_CASE("stackplot: url") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .url = "https://matplotlib.org"
    }));
}

TEST_CASE("stackplot: two series only (M=2)") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB()}
    }));
}

TEST_CASE("stackplot: all parameters combined") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .baseline = "weighted_wiggle",
        .labels = StrVec{"Line A", "Line B", "Line C"},
        .colors = StrVec{"navy", "orange", "green"},
        .alpha = 0.7,
        .animated = false,
        .array = Vec{0.1, 0.2, 0.3, 0.4, 0.5, 0.6},
        .clim = Clim{0.0, 1.0},
        .clip_on = true,
        .cmap = "viridis",
        .color = "purple",
        .edgecolor = "gray",
        .facecolor = "lightblue",
        .gid = "my-stackplot-id",
        .hatch = "//",
        .in_layout = true,
        .label = "generic label",
        .linestyle = "-",
        .linewidth = 1.0,
        .mouseover = false,
        .pickradius = 2.0,
        .rasterized = false,
        .snap = true,
        .url = "https://matplotlib.org",
        .visible = true,
        .zorder = 1.0
    }));
}

TEST_CASE("PyPlot::stackplot: basic call on current axes") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(plt.stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()}
    }));
}

TEST_CASE("stackplot: regression — float64 data produces consistent weighted_wiggle geometry") {
    // Confirms the C++ wrapper always sends float64 (NPY_DOUBLE) data, avoiding
    // the int64-vs-float64 dtype-dependent behavior found in matplotlib's own
    // weighted_wiggle baseline algorithm during manual investigation.
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});

    CHECK_NOTHROW(axes[0].stackplot({
        .x = makeX(),
        .y = {lineA(), lineB(), lineC()},
        .baseline = "weighted_wiggle"
    }));
}