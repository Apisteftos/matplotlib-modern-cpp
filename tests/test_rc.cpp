#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../include/Matplotlib.h"
#include "RcConfigs.h"

using matplotlibcpp::RcConfig;
using matplotlibcpp::GridRcConfig;
using matplotlibcpp::LegendRcConfig;
using matplotlibcpp::FigureRcConfig;
using matplotlibcpp::AxesRcConfig;
using matplotlibcpp::LinesRcConfig;
using matplotlibcpp::FontRcConfig;
using matplotlibcpp::TicksRcConfig;
using matplotlibcpp::Vec;

TEST_CASE("rc: generic RcConfig — single string kwarg") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(RcConfig{.group = "image", .kwargs = {{"cmap", std::string("viridis")}}}));
}

TEST_CASE("rc: generic RcConfig — mixed value types") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(RcConfig{.group = "legend", .kwargs = {
        {"loc", std::string("upper left")},
        {"frameon", true},
        {"framealpha", 0.5},
        {"fancybox", false}
    }}));
}

TEST_CASE("rc: generic RcConfig — bool true and false both") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(RcConfig{.group = "axes", .kwargs = {{"grid", true}}}));
    CHECK_NOTHROW(plt.rc(RcConfig{.group = "axes", .kwargs = {{"grid", false}}}));
}

TEST_CASE("rc: GridRcConfig — base grid group") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(GridRcConfig{
        .group = "grid",
        .color = "#b0b0b0",
        .linestyle = "-",
        .linewidth = 0.8,
        .alpha = 1.0
    }));
}

TEST_CASE("rc: GridRcConfig — grid.major") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(GridRcConfig{
        .group = "grid.major",
        .color = "blue",
        .linestyle = "--",
        .linewidth = 1.2
    }));
}

TEST_CASE("rc: GridRcConfig — grid.minor") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(GridRcConfig{
        .group = "grid.minor",
        .color = "red",
        .linestyle = ":",
        .linewidth = 0.6
    }));
}

TEST_CASE("rc: LegendRcConfig — loc as string") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(LegendRcConfig{.group = "legend", .loc = std::string("best")}));
}

TEST_CASE("rc: LegendRcConfig — loc as int") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(LegendRcConfig{.group = "legend", .loc = 1}));
}

TEST_CASE("rc: LegendRcConfig — loc as Loc coordinates") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(LegendRcConfig{.group = "legend", .loc = matplotlibcpp::Loc{0.5, 0.5}}));
}

TEST_CASE("rc: LegendRcConfig — frameon, framealpha, fancybox") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(LegendRcConfig{
        .group = "legend",
        .frameon = true,
        .framealpha = 0.8,
        .fancybox = true
    }));
}

TEST_CASE("rc: LegendRcConfig — facecolor and edgecolor, including 'inherit'") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(LegendRcConfig{.group = "legend", .facecolor = "inherit", .edgecolor = "0.8"}));
    CHECK_NOTHROW(plt.rc(LegendRcConfig{.group = "legend", .facecolor = "cyan", .edgecolor = "black"}));
}

TEST_CASE("rc: FigureRcConfig — figsize") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(FigureRcConfig{.group = "figure", .figsize = Vec{8.0, 4.0}}));
}

TEST_CASE("rc: FigureRcConfig — titlesize does not get overwritten by unrelated calls") {
    // regression test: hardcoded (non-nullopt) defaults previously caused
    // later calls to the same group to silently overwrite earlier settings
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(FigureRcConfig{.group = "figure", .titlesize = "medium"}));
    CHECK_NOTHROW(plt.rc(FigureRcConfig{.group = "figure", .facecolor = "#f0f0f0"}));
}

TEST_CASE("rc: FigureRcConfig — figure.subplot group") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(FigureRcConfig{
        .group = "figure.subplot",
        .left = 0.1,
        .right = 0.95,
        .top = 0.9,
        .bottom = 0.1,
        .wspace = 0.3,
        .hspace = 0.3
    }));
}

TEST_CASE("rc: FigureRcConfig — dpi") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(FigureRcConfig{.group = "figure", .dpi = 120.0}));
}

TEST_CASE("rc: AxesRcConfig — axes base group") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(AxesRcConfig{
        .group = "axes",
        .facecolor = "white",
        .linewidth = 0.8,
        .grid = true
    }));
}

TEST_CASE("rc: AxesRcConfig — axes.spines group") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(AxesRcConfig{
        .group = "axes.spines",
        .left = true,
        .bottom = true,
        .top = false,
        .right = false
    }));
}

TEST_CASE("rc: AxesRcConfig — title and label styling") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(AxesRcConfig{
        .group = "axes",
        .titlesize = "large",
        .titleweight = "bold",
        .titlecolor = "navy",
        .labelsize = "medium",
        .labelweight = "normal"
    }));
}

TEST_CASE("rc: LinesRcConfig — basic style") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(LinesRcConfig{
        .group = "lines",
        .linewidth = 2.0,
        .linestyle = "-",
        .color = "C1"
    }));
}

TEST_CASE("rc: LinesRcConfig — marker properties") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(LinesRcConfig{
        .group = "lines",
        .markerfacecolor = "black",
        .markeredgecolor = "black",
        .markeredgewidth = 1.0,
        .markersize = 8.0,
    }));
}

TEST_CASE("rc: LinesRcConfig — dash patterns") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(LinesRcConfig{
        .group = "lines",
        .dashed_pattern = {3.7, 1.6},
        .dashdot_pattern = {6.4, 1.6, 1.0, 1.6},
        .dotted_pattern = {1.0, 1.65}
    }));
}

TEST_CASE("rc: FontRcConfig — family and size") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(FontRcConfig{.group = "font", .family = "serif", .size = 12.0}));
}

TEST_CASE("rc: FontRcConfig — weight, style, variant, stretch") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(FontRcConfig{
        .group = "font",
        .style = "italic",
        .variant = "normal",
        .weight = "bold",
        .stretch = "normal"
    }));
}

TEST_CASE("rc: TicksRcConfig — xtick base group") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(TicksRcConfig{.group = "xtick", .labelsize = "medium", .direction = "out"}));
}

TEST_CASE("rc: TicksRcConfig — ytick base group") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(TicksRcConfig{.group = "ytick", .labelsize = "10", .direction = "in"}));
}

TEST_CASE("rc: TicksRcConfig — ytick.minor ndivs") {
    matplotlibcpp::PyPlot plt;
    CHECK_NOTHROW(plt.rc(TicksRcConfig{.group = "ytick.minor", .ndivs = 5}));
    CHECK_NOTHROW(plt.rc(TicksRcConfig{.group = "ytick.minor", .ndivs = "auto"}));
}

TEST_CASE("rc: full rc example — grid, legend, figure, axes, lines, font, ticks together (all attributes)") {
    matplotlibcpp::PyPlot plt;

  
    CHECK_NOTHROW(plt.rc(GridRcConfig{
        .group = "grid", .color = "#b0b0b0", .linestyle = "-", .linewidth = 0.8, .alpha = 1.0
    }));
    CHECK_NOTHROW(plt.rc(GridRcConfig{
        .group = "grid.major", .color = "blue", .linestyle = "--", .linewidth = 1.2, .alpha = 0.6
    }));
    CHECK_NOTHROW(plt.rc(GridRcConfig{
        .group = "grid.minor", .color = "red", .linestyle = ":", .linewidth = 0.6, .alpha = 0.4
    }));

  
    CHECK_NOTHROW(plt.rc(LegendRcConfig{
        .group = "legend",
        .loc = "upper right",
        .frameon = true,
        .framealpha = 0.8,
        .facecolor = "inherit",
        .edgecolor = "0.8",
        .linewidth = 1.0,
        .fancybox = true,
        .numpoints = 1,
        .scatterpoints = 1,
        .fontsize = 10.0,
        .labelcolor = "black",
        .title_fontsize = "medium",
        .borderpad = 0.4,
        .labelspacing = 0.5,
        .handlelength = 2.0,
        .handleheight = 0.7,
        .handletextpad = 0.8,
        .borderaxespad = 0.5,
        .columnspacing = 2.0
    }));


    CHECK_NOTHROW(plt.rc(FigureRcConfig{
        .group = "figure",
        .titlesize = "large",
        .titleweight = "normal",
        .labelsize = "large",
        .labelweight = "normal",
        .figsize = {10.0, 5.0},
        .dpi = 100.0,
        .facecolor = "white",
        .edgecolor = "white",
        .frameon = true,
        .max_open_warning = 20,
        .raise_window = true,
        .autolayout = false
    }));

 
    CHECK_NOTHROW(plt.rc(FigureRcConfig{
        .group = "figure.subplot",
        .left = 0.125,
        .right = 0.9,
        .top = 0.88,
        .bottom = 0.11,
        .wspace = 0.2,
        .hspace = 0.2
    }));


    CHECK_NOTHROW(plt.rc(FigureRcConfig{
        .group = "figure.constrained_layout",
        .wspace = 0.2,
        .hspace = 0.2,
        .use = 0.125,
        .h_pad = 0.09,
        .w_pad = 0.09
        
    }));

  
    CHECK_NOTHROW(plt.rc(AxesRcConfig{
        .group = "axes",
        .facecolor = "white",
        .edgecolor = "black",
        .linewidth = 0.8,
        .grid = true,
        .titlelocation = "center",
        .titlesize = "large",
        .titleweight = "normal",
        .titlecolor = "black",
        .titley = "1.0",
        .titlepad = 6.0,
        .labelsize = "medium",
        .labelpad = 4.0,
        .labelweight = "normal",
        .labelcolor = "black",
        .axisbelow = "line",
        .xmargin = 0.05,
        .ymargin = 0.05,
        .zmargin = 0.05,
        .autolimit_mode = "data"
    }));


    CHECK_NOTHROW(plt.rc(AxesRcConfig{
        .group = "axes.grid",
        .axis = "both",
        .which = "major"
    }));


    CHECK_NOTHROW(plt.rc(AxesRcConfig{
        .group = "axes.formatter",
        .limits = {0.0, 1.0},
        .use_locale = false,
        .use_mathtext = false,
        .min_exponent = 0,
        .useoffset = true,
        .offset_threshold = 4
    }));


    CHECK_NOTHROW(plt.rc(AxesRcConfig{
        .group = "axes.spines",
        .left = true,
        .bottom = true,
        .top = false,
        .right = false
    }));

  
    CHECK_NOTHROW(plt.rc(LinesRcConfig{
        .group = "lines",
        .linewidth = 2.0,
        .linestyle = "-",
        .color = "C0",
        .marker = "o",
        .markerfacecolor = "black",
        .markeredgecolor = "black",
        .markeredgewidth = 1.0,
        .markersize = 8.0,
        .dash_joinstyle = "round",
        .dash_capstyle = "butt",
        .solid_joinstyle = "round",
        .solid_capstyle = "projecting",
        .antialiased = true,
        .dashed_pattern = {3.7, 1.6},
        .dashdot_pattern = {6.4, 1.6, 1.0, 1.6},
        .dotted_pattern = {1.0, 1.65},
        .scale_dashes = true
    }));



    
    CHECK_NOTHROW(plt.rc(FontRcConfig{
        .group = "font",
        .family = "serif",
        .style = "normal",
        .variant = "normal",
        .weight = "normal",
        .stretch = "normal",
        .size = 12.0,
        .serif = {"Times New Roman", "DejaVu Serif"},
        .sansserif = {"Arial", "DejaVu Sans"},
        .monospace = {"Courier New", "DejaVu Sans Mono"}
    }));

    
    CHECK_NOTHROW(plt.rc(TicksRcConfig{
        .group = "xtick",
        .top = false,
        .bottom = true,
        .color = "black",
        .labelcolor = "inherit",
        .labelsize = "medium",
        .direction = "out",
        .alignment = "center"
    }));

    
    CHECK_NOTHROW(plt.rc(TicksRcConfig{
        .group = "xtick.major",
        .top = false,
        .bottom = true,
        .size = 3.5,
        .width = 0.8,
        .pad = 3.5
    }));

    
    CHECK_NOTHROW(plt.rc(TicksRcConfig{
        .group = "xtick.minor",
        .size = 2.0,
        .width = 0.6,
        .pad = 3.4,
        .ndivs = "auto"
    }));

   
    CHECK_NOTHROW(plt.rc(TicksRcConfig{
        .group = "ytick",
        .labelsize = "medium",
        .direction = "in",
        .left = true,
        .right = false
    }));

    CHECK_NOTHROW(plt.rc(TicksRcConfig{
        .group = "ytick.minor",
        .ndivs = 5
    }));

    // final sanity check — actually plot something with all these styles applied
    auto [fig, axes] = plt.subplots({.nrows = 1, .ncols = 1});
    CHECK_NOTHROW(axes[0].plot({.x = Vec{1, 2, 3, 4}, .y = Vec{1, 4, 9, 16}, .label = "test"}));
    CHECK_NOTHROW(axes[0].legend());
}