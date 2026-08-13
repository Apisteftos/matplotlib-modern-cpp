#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../include/Matplotlib.h"
#include <vector>

TEST_CASE("PyPlot::suptitle: minimal — just t") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({.t = "My Figure Title"}));
}

TEST_CASE("PyPlot::suptitle: default fontsize ('large') and fontweight ('normal') construct correctly") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    // Regression test: FontSizeValue previously used std::vector<std::string>
    // instead of std::string, so the "large" default failed to construct.
    CHECK_NOTHROW(plt.suptitle({.t = "Default styling"}));
}

TEST_CASE("PyPlot::suptitle: custom ha, va") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({.t = "Left aligned", .horizontalalignment = "left", .verticalalignment = "bottom"}));
}

TEST_CASE("PyPlot::suptitle: explicit fontsize (numeric and string)") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({.t = "Numeric", .fontsize = 18.0}));
    CHECK_NOTHROW(plt.suptitle({.t = "Keyword", .fontsize = std::string("xx-large")}));
}

TEST_CASE("PyPlot::suptitle: explicit fontweight (int and string)") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({.t = "Bold string", .fontweight = std::string("bold")}));
    CHECK_NOTHROW(plt.suptitle({.t = "Bold int", .fontweight = 700}));
}

TEST_CASE("PyPlot::suptitle: fontstretch, fontstyle, fontvariant, fontfamily") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({
        .t = "Font styled",
        .fontfamily = "serif",
        .fontstretch = std::string("expanded"),
        .fontstyle = "italic",
        .fontvariant = "small-caps"
    }));
}

TEST_CASE("PyPlot::suptitle: color and alpha") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({.t = "Styled Title", .alpha = 0.8, .color = "navy"}));
}

TEST_CASE("PyPlot::suptitle: linespacing and multialignment") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({
        .t = "Multi\nline title",
        .linespacing = 1.4,
        .multialignment = "center"
    }));
}

TEST_CASE("PyPlot::suptitle: rotation as double and string") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({.t = "Tilted", .rotation = 5.0}));
    CHECK_NOTHROW(plt.suptitle({
        .t = "Vertical",
        .rotation = std::string("vertical"),
        .rotation_mode = "anchor"
    }));
}

TEST_CASE("PyPlot::suptitle: position via x, y") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({.t = "Custom position", .x = 0.1, .y = 0.99}));
}

TEST_CASE("PyPlot::suptitle: position field (Position struct)") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({
        .t = "Positioned",
        .position = matplotlibcpp::Position{0.5, 0.95}
    }));
}

TEST_CASE("PyPlot::suptitle: sketch_params") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({
        .t = "Sketchy title",
        .sketch_params = matplotlibcpp::SketchParams{2.5, 90.0, 10.0}
    }));
}

TEST_CASE("PyPlot::suptitle: boolean flags — animated, antialiased, in_layout, mouseover, snap, rasterized, visible, wrap") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({
        .t = "Flags",
        .animated = false,
        .antialiased = true,
        .in_layout = true,
        .mouseover = false,
        .rasterized = false,
        .snap = true,
        .visible = true,
        .wrap = false
    }));
}

TEST_CASE("PyPlot::suptitle: clip_on and parse_math as bool") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({.t = "Clip/math", .clip_on = true, .parse_math = false}));
}

TEST_CASE("PyPlot::suptitle: language, math_fontfamily") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({
        .t = "Localized",
        .language = "fr",
        .math_fontfamily = "stixsans"
    }));
}

TEST_CASE("PyPlot::suptitle: text, transform_rotates_text, url, verticalalignment, check for t and text collisions") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({
        .t = "Extra props",
        .text = "override",
        .transform_rotates_text = true,
        .url = "https://matplotlib.org",
        .verticalalignment = "top"
    }));
}

TEST_CASE("PyPlot::suptitle: t the super title text") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({
        .t = "Extra props",
        .horizontalalignment = "center",
        .transform_rotates_text = true,
        .url = "https://matplotlib.org"
    }));
}

TEST_CASE("PyPlot::suptitle: text the text to display") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({
        .horizontalalignment = "center",
        .text = "Text to display",
        .transform_rotates_text = true,
        .url = "https://matplotlib.org"
    }));
}

TEST_CASE("PyPlot::suptitle: zorder") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({.t = "Layered", .zorder = 12.0}));
}

TEST_CASE("PyPlot::suptitle: generic 'label' kwarg does not collide") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({.t = "My Title", .label = "unrelated legend label"}));
}

TEST_CASE("PyPlot::suptitle: all parameters combined witout the text parameter") {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(plt.suptitle({
        .t = "Full config",
        .alpha = 0.9,
        .animated = false,
        .antialiased = true,
        .clip_on = true,
        .color = "black",
        .fontfamily = "sans-serif",
        .fontsize = std::string("large"),
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
        .position = matplotlibcpp::Position{0.5, 0.95},
        .rasterized = false,
        .rotation = 0.0,
        .rotation_mode = "default",
        .sketch_params = matplotlibcpp::SketchParams{1.0, 128.0, 16.0},
        .snap = true,
        .transform_rotates_text = false,
        .url = "https://matplotlib.org",
        .verticalalignment = "top",
        .visible = true,
        .wrap = false,
        .x = 0.5,
        .y = 0.95,
        .zorder = 5.0
    }));
}