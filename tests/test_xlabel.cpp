#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../include/Matplotlib.h"
#include <vector>

using matplotlibcpp::Position;
using matplotlibcpp::SketchParams;

TEST_CASE("Axes::set_xlabel: minimal — just xlabel text") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({.xlabel = "Time (seconds)"}));
}

TEST_CASE("Axes::set_xlabel: labelpad and loc") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Time (seconds)",
        .labelpad = 12.0,
        .loc = "right"
    }));
}

TEST_CASE("Axes::set_xlabel: color, alpha, visible") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Amplitude",
        .alpha = 0.75,
        .color = "crimson",
        .visible = true
    }));
}

TEST_CASE("Axes::set_xlabel: fontsize as double") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Frequency (Hz)",
        .fontsize = 16.0
    }));
}

TEST_CASE("Axes::set_xlabel: fontsize as string keyword") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Frequency (Hz)",
        .fontsize = std::string("x-large")
    }));
}

TEST_CASE("Axes::set_xlabel: fontweight as string, fontstyle, fontvariant, fontfamily") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Power (W)",
        .fontfamily = "sans-serif",
        .fontstyle = "italic",
        .fontvariant = "small-caps",
        .fontweight = std::string("bold")
    }));
}

TEST_CASE("Axes::set_xlabel: fontweight as int") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Power (W)",
        .fontweight = 700
    }));
}

TEST_CASE("Axes::set_xlabel: fontstretch as string and int") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Stretch string",
        .fontstretch = std::string("expanded")
    }));
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Stretch int",
        .fontstretch = 500
    }));
}

TEST_CASE("Axes::set_xlabel: linespacing as double and string") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Linespacing double",
        .linespacing = 1.5
    }));
}

TEST_CASE("Axes::set_xlabel: rotation as double and string") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Rotated 45",
        .rotation = 45.0
    }));
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Rotated vertical",
        .rotation = std::string("vertical"),
        .rotation_mode = "anchor"
    }));
}

TEST_CASE("Axes::set_xlabel: animated, antialiased, in_layout, mouseover, snap, rasterized") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Boolean flags",
        .animated = false,
        .antialiased = true,
        .in_layout = true,
        .mouseover = false,
        .rasterized = false,
        .snap = true
    }));
}

TEST_CASE("Axes::set_xlabel: clip_on and parse_math as bool") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Clip and math",
        .clip_on = true,
        .parse_math = false
    }));
}

TEST_CASE("Axes::set_xlabel: language, math_fontfamily, multialignment") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Multiline\nlabel",
        .language = "en",
        .math_fontfamily = "cm",
        .multialignment = "center"
    }));
}

TEST_CASE("Axes::set_xlabel: position as Position struct") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Positioned",
        .position = Position{0.5, -0.1}
    }));
}

TEST_CASE("Axes::set_xlabel: sketch_params") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Sketchy",
        .sketch_params = SketchParams{2.0, 100.0, 8.0}
    }));
}

TEST_CASE("Axes::set_xlabel: text, transform_rotates_text, url, verticalalignment, wrap") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Extra text props",
        .text = "override text",
        .transform_rotates_text = true,
        .url = "https://example.com",
        .verticalalignment = "bottom",
        .wrap = true
    }));
}

TEST_CASE("Axes::set_xlabel: x, y, zorder") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Explicit coords",
        .x = 0.5,
        .y = -0.15,
        .zorder = 10.0
    }));
}

TEST_CASE("Axes::set_xlabel: generic Text 'label' kwarg does not collide with xlabel text") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Time (seconds)",
        .label = "some unrelated legend label"
    }));
}

TEST_CASE("Axes::set_xlabel: all parameters combined without loc") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Full config",
        .labelpad = 10.0,
        .alpha = 0.9,
        .animated = false,
        .antialiased = true,
        .clip_on = true,
        .color = "navy",
        .fontfamily = "serif",
        .fontsize = 14.0,
        .fontstretch = std::string("normal"),
        .fontstyle = "normal",
        .fontvariant = "normal",
        .fontweight = std::string("bold"),
        .gid = "my-custom-xlabel-id",
        .horizontalalignment = "center",
        .in_layout = true,
        .language = "en",
        .linespacing = 1.2,
        .math_fontfamily = "dejavusans",
        .mouseover = false,
        .multialignment = "center",
        .parse_math = true,
        .position = Position{0.5, -0.12},
        .rasterized = false,
        .rotation = 0.0,
        .rotation_mode = "default",
        .sketch_params = SketchParams{1.0, 128.0, 16.0},
        .snap = true,
        .transform_rotates_text = false,
        .url = "https://matplotlib.org",
        .verticalalignment = "top",
        .visible = true,
        .wrap = false,
        .zorder = 5.0
    }));
}


TEST_CASE("Axes::set_xlabel: all parameters combined with loc and without horizontalalignment") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_xlabel({
        .xlabel = "Full config",
        .labelpad = 10.0,
        .loc = "center",
        .alpha = 0.9,
        .animated = false,
        .antialiased = true,
        .clip_on = true,
        .color = "navy",
        .fontfamily = "serif",
        .fontsize = 14.0,
        .fontstretch = std::string("normal"),
        .fontstyle = "normal",
        .fontvariant = "normal",
        .fontweight = std::string("bold"),
        .gid = "my-custom-xlabel-id",
        .in_layout = true,
        .language = "en",
        .linespacing = 1.2,
        .math_fontfamily = "dejavusans",
        .mouseover = false,
        .multialignment = "center",
        .parse_math = true,
        .position = Position{0.5, -0.12},
        .rasterized = false,
        .rotation = 0.0,
        .rotation_mode = "default",
        .sketch_params = SketchParams{1.0, 128.0, 16.0},
        .snap = true,
        .transform_rotates_text = false,
        .url = "https://matplotlib.org",
        .verticalalignment = "top",
        .visible = true,
        .wrap = false,
        .zorder = 5.0
    }));
}


TEST_CASE("PyPlot::xlabel: basic call on current axes") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.xlabel({.xlabel = "Time (seconds)"}));
}

TEST_CASE("PyPlot::xlabel: with fontsize and fontweight") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.xlabel({
        .xlabel = "Time (seconds)",
        .fontsize = 12.0,
        .fontweight = std::string("bold")
    }));
}