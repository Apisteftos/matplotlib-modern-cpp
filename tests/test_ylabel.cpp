#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../include/Matplotlib.h"
#include <vector>

using matplotlibcpp::Position;
using matplotlibcpp::SketchParams;

TEST_CASE("Axes::set_ylabel: minimal — just ylabel text") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({.ylabel = "Amplitude"}));
}

TEST_CASE("Axes::set_ylabel: labelpad and loc") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Voltage (V)",
        .labelpad = 8.0,
        .loc = "top"
    }));
}

TEST_CASE("Axes::set_ylabel: color, alpha, visible") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Power (W)",
        .alpha = 0.8,
        .color = "darkgreen",
        .visible = true
    }));
}

TEST_CASE("Axes::set_ylabel: fontsize as double and string") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({.ylabel = "Numeric", .fontsize = 13.0}));
    CHECK_NOTHROW(axes[0].set_ylabel({.ylabel = "Keyword", .fontsize = std::string("small")}));
}

TEST_CASE("Axes::set_ylabel: fontweight int and string, fontstyle, fontvariant, fontfamily") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Styled",
        .fontfamily = "monospace",
        .fontstyle = "oblique",
        .fontvariant = "small-caps",
        .fontweight = 300
        
    }));
}

TEST_CASE("Axes::set_ylabel: fontstretch as string and int") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({.ylabel = "Condensed", .fontstretch = std::string("condensed")}));
    CHECK_NOTHROW(axes[0].set_ylabel({.ylabel = "Stretch400", .fontstretch = 400}));
}

TEST_CASE("Axes::set_ylabel: linespacing") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({.ylabel = "Spacing", .linespacing = 1.3}));
}

TEST_CASE("Axes::set_ylabel: rotation as double and string") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({.ylabel = "Rotated 90", .rotation = 90.0}));
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Rotated horiz",
        .rotation = std::string("horizontal"),
        .rotation_mode = "anchor"
    }));
}

TEST_CASE("Axes::set_ylabel: animated, antialiased, in_layout, mouseover, snap, rasterized") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Flags",
        .animated = false,
        .antialiased = true,
        .in_layout = true,
        .mouseover = false,
        .rasterized = false,
        .snap = true
    }));
}

TEST_CASE("Axes::set_ylabel: clip_on and parse_math as bool") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Clip and math",
        .clip_on = false,
        .parse_math = true
    }));
}

TEST_CASE("Axes::set_ylabel: language, math_fontfamily, multialignment") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Multi\nline",
        .language = "de",
        .math_fontfamily = "stix",
        .multialignment = "right"
    }));
}

TEST_CASE("Axes::set_ylabel: position as Position struct") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Positioned",
        .position = Position{-0.1, 0.5}
    }));
}

TEST_CASE("Axes::set_ylabel: sketch_params") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Sketchy",
        .sketch_params = SketchParams{3.0, 80.0, 5.0}
    }));
}

TEST_CASE("Axes::set_ylabel: text, transform_rotates_text, url, verticalalignment, wrap") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Extra props",
        .text = "override",
        .transform_rotates_text = false,
        .url = "https://example.com",
        .verticalalignment = "center",
        .wrap = true
    }));
}

TEST_CASE("Axes::set_ylabel: x, y, zorder") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Coords",
        .x = -0.15,
        .y = 0.5,
        .zorder = 6.0
    }));
}

TEST_CASE("Axes::set_ylabel: generic Text 'label' kwarg does not collide with ylabel text") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Amplitude",
        .label = "some unrelated legend label"
    }));
}

// loc and horizontalalignment should not be applied together
TEST_CASE("Axes::set_ylabel: all parameters combined without loc") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Full config",
        .labelpad = 6.0,
        .alpha = 0.85,
        .animated = false,
        .antialiased = true,
        .clip_on = true,
        .color = "purple",
        .fontfamily = "sans-serif",
        .fontsize = 13.0,
        .fontstretch = std::string("normal"),
        .fontstyle = "normal",
        .fontvariant = "normal",
        .fontweight = 600,
        .gid = "my-custom-xlabel-id",
        .horizontalalignment = "center",
        .in_layout = true,
        .language = "en",
        .linespacing = 1.1,
        .math_fontfamily = "cm",
        .mouseover = false,
        .multialignment = "center",
        .parse_math = true,
        .position = Position{-0.12, 0.5},
        .rasterized = false,
        .rotation = 90.0,
        .rotation_mode = "default",
        .sketch_params = SketchParams{1.0, 128.0, 16.0},
        .snap = true,
        .transform_rotates_text = false,
        .url = "https://matplotlib.org",
        .verticalalignment = "center",
        .visible = true,
        .wrap = false,
        .x = -0.1,
        .y = 0.5,
        .zorder = 5.0
    }));
}

TEST_CASE("Axes::set_ylabel: all parameters combined, using loc instead of x/y/horizontalalignment") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].set_ylabel({
        .ylabel = "Full config via loc",
        .labelpad = 6.0,
        .loc = "top",
        .alpha = 0.85,
        .animated = false,
        .antialiased = true,
        .clip_on = true,
        .color = "purple",
        .fontfamily = "sans-serif",
        .fontsize = 13.0,
        .fontstretch = std::string("normal"),
        .fontstyle = "normal",
        .fontvariant = "normal",
        .fontweight = 600,
        .gid = "my-custom-xlabel-id",
        .in_layout = true,
        .language = "en",
        .linespacing = 1.1,
        .math_fontfamily = "cm",
        .mouseover = false,
        .multialignment = "center",
        .parse_math = true,
        .rasterized = false,
        .rotation = 90.0,
        .rotation_mode = "default",
        .sketch_params = SketchParams{1.0, 128.0, 16.0},
        .snap = true,
        .transform_rotates_text = false,
        .url = "https://matplotlib.org",
        .verticalalignment = "center",
        .visible = true,
        .wrap = false,
        .zorder = 5.0
    }));
}


TEST_CASE("PyPlot::ylabel: basic call on current axes") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.ylabel({.ylabel = "Amplitude"}));
}

TEST_CASE("PyPlot::ylabel: with fontsize and fontweight") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.ylabel({
        .ylabel = "Amplitude",
        .fontsize = 12.0,
        .fontweight = std::string("bold")
    }));
}